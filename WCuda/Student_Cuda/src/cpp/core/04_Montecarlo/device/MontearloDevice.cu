#include "Indice2D.h"
#include "Indice1D.h"
#include <curand_kernel.h>
#include <stdio.h>
#include <reductionADD.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarlo(curandState* ptrDevGeneratorGM, int* ptrDevNxTotalGM, int nbDartByThread);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
static __device__ void reductionIntraThread(int* tabSM, curandState* ptrDevGeneratorGM, int nbDartByThread);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void montecarlo(curandState* ptrDevGeneratorGM, int* ptrDevNTotalGM, int nbDartByThread)
    {
    extern __shared__ int tabSM[];
    //Reduction intra-thread
    reductionIntraThread(tabSM, ptrDevGeneratorGM, nbDartByThread);
    __syncthreads();
    //Reduction interblock
    reductionADD<int>(tabSM, ptrDevNTotalGM);

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reductionIntraThread(int* tabSM, curandState* ptrDevGeneratorGM, int nbDartByThread)
    {
    const int TID = Indice1D::tid();
    //TODO pattern entrelacement

    const int TID_LOCAL = Indice1D::tidLocal();
    curandState localGenerator = ptrDevGeneratorGM[TID];
    int x = 0;
    float xAlea;
    float yAlea;
    for (int i = 1; i <= nbDartByThread; i++)
	{
	xAlea = curand_uniform(&localGenerator);
	yAlea = curand_uniform(&localGenerator);
	x += (int) (1.f / (1.f + xAlea * xAlea) >= yAlea);
	}
    ptrDevGeneratorGM[TID] = localGenerator;
    tabSM[TID_LOCAL] = x;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


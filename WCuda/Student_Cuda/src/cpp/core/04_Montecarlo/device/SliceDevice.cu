#include "Indice2D.h"
#include "Indice1D.h"
#include "cudaTools.h"
#include "reductionADD.h"


#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarlo(float* ptrTabDev, int nb);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ float fpi(float x);
static __device__ void reductionIntraThread(float* tabSM, int nb);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void montecarlo(float* ptrTabDev, int nbSlice)
    {
    extern __shared__ float tabSM[];
    //Reduction intra-thread
    reductionIntraThread(tabSM, nbSlice);
    __syncthreads();
    //Reduction interblock
    reductionADD<float>(tabSM, ptrTabDev);

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reductionIntraThread(float* tabSM, int nbSlice)
    {
    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();

    //TODO pattern entrelacement

    const int TID_LOCAL = Indice1D::tidLocal();
    const float DX = 1.0f / (float) nbSlice;
    float sumThread = 0;

    int s = TID;
    while (s < nbSlice)
	{
	float x = s * DX;
	sumThread += fpi(x);
	s += NB_THREAD;
	}

    tabSM[TID_LOCAL] = 4 * sumThread * DX;
    }

__device__ float fpi(float x)
    {
    return 1 / (1.0 + x * x);
    }
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


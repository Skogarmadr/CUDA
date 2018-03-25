#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"
#include "RayTracingMath.h"

#include "IndiceTools_GPU.h"
#include "Sphere.h"

#include "length_cm.h"

using namespace gpu;

// Attention : 	Choix du nom est important!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ void uploadGPU(Sphere* tabValue);

__global__ void raytracing_GM(Sphere* ptrDevTabSphere, int nbSphere, uchar4* ptrDevPixels, uint w, uint h, float t);
__global__ void raytracing_CM(uchar4* ptrDevPixels, uint w, uint h, float t);

__device__ void work(Sphere* ptrDevTabSphere, int nbSphere, uchar4* ptrDevPixels, uint w, uint h, float t);

// Déclaration Constante globale
__constant__ Sphere TAB_CM[LENGTH_CM];
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
/**
 * call once by the host
 *
 */
__global__ void raytracing_GM(Sphere* ptrDevTabSphere, int nbSphere, uchar4* ptrDevPixels, uint w, uint h, float t)
    {
    work(ptrDevTabSphere, nbSphere, ptrDevPixels, w, h, t);
    }

__global__ void raytracing_CM(uchar4* ptrDevPixels, uint w, uint h, float t)
    {
    work(TAB_CM, LENGTH_CM, ptrDevPixels, w, h, t);
    }

__host__ void uploadGPU(Sphere * tabSphere)
    {
    size_t size = LENGTH_CM * sizeof(Sphere);
    int offset = 0;
    HANDLE_ERROR(cudaMemcpyToSymbol(TAB_CM, tabSphere, size, offset, cudaMemcpyHostToDevice));
    }

__device__ void work(Sphere* ptrDevTabSphere, int nbSphere, uchar4* ptrDevPixels, uint w, uint h, float t)
    {
    RayTracingMath rayTracingMath = RayTracingMath(nbSphere, ptrDevTabSphere);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    int i, j;
    int W = w * h;

    int s = TID;
    while (s < W)
	{
	IndiceTools::toIJ(s, w, &i, &j);

	rayTracingMath.colorIJ(&s[ptrDevPixels], i, j, t);

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


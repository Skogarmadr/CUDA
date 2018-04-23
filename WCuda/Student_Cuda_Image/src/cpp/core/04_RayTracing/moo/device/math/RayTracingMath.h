#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"

#include "Sphere.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RayTracingMath(Sphere* ptrDevTabSphere, uint nbSphere)
	    {
	    this->nbSphere = nbSphere;
	    this->ptrDevTabSphere = ptrDevTabSphere;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	          virtual ~RayTracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, float i, float j, float t)
	    {
	    float dz, minDz, distance;
	    float2 hCarre;
	    int minIndex = -1;
	    float minDistance = 3.4028235E38f;
	    for (uint index = 0; index < nbSphere; index++)
		{
		Sphere s = ptrDevTabSphere[index];
		hCarre = s.hCarre(i);
		if (s.isEnDessous(hCarre))
		    {
		    dz = s.dz(hCarre);
		    distance = s.distance(dz);
		    if (distance < minDistance)
			{
			minDistance = distance;
			minDz = dz;
			minIndex = index;
			}
		    }
		}
	    if (minIndex != -1)
		{
		Sphere s = ptrDevTabSphere[minIndex];
		ColorTools::HSB_TO_RVB(s.hue(t), 1.f, s.brightness(minDz), ptrColor);
		}
	    else // Si le point n'est pas sous une sphere => noir
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		ptrColor->w = 255;
		}
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	uint nbSphere;
	Sphere* ptrDevTabSphere;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

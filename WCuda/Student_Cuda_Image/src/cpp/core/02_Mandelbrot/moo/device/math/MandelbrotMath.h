#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ MandelbrotMath(int n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	MandelbrotMath
	// 	calibreur
	// 	IntervalF

	__device__
		    virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColor, float x, float y)
	    {
	    float z = f(x, y);

	    if (z == this->n)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else
		{
		calibreur.calibrer(&z);	//reference
		float hue = z;
		ColorTools::HSB_TO_RVB(hue, ptrColor);
		}

	    ptrColor->w = 255; //opaque
	    }

    private:

	__device__
	float f(float x, float y)
	    {
	    float a = 0;
	    float b = 0;
	    float aCopy;
	    float k = 0;

	    do
		{
		aCopy = a;
		a = (a * a - b * b) + x;
		b = 2.0f * aCopy * b + y;
		k += 1;
		}
	    while (a * a + b * b < 4.0f && k < this->n);

	    return k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	int n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

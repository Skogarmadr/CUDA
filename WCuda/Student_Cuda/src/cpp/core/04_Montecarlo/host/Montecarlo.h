#pragma once

#include "cudaTools.h"
#include "Grid.h"
#include <curand_kernel.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Montecarlo
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * update w by v1+v2
	 */
	Montecarlo(const Grid& grid, int nbDartTotal);

	virtual ~Montecarlo(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void run();
	float getResult();
	int getNbDartUnderCurve();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	dim3 dg;
	dim3 db;
	int nbDartTotal;
	int nbDartByThread;

	// Inputs/Outputs
	float result;

	// Tools
	size_t sizeOctetGM;
	size_t sizeOctetSM;
	size_t sizeOctetGeneratorGM;


	int* ptrDevGMResult;
	curandState* tabDevGeneratorGM;
	int nbDartUnderCurve;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

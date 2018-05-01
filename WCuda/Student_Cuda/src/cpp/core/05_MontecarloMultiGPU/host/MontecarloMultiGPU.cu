#include "Montecarlo.h"

#include <iostream>
#include "MontecarloMultiGPU.h"
#include "Montecarlo.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void montecarlo(curandState* ptrDevGenerator, int* ptrDevNbTotalGM, int nbDartByThread); // déclarer dans un autre fichier, kernel coté device
extern __global__ void createGenerator (curandState* tabDevGenerator, int deviceId);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

MontecarloMultiGPU::MontecarloMultiGPU(const Grid& grid, int nbDartTotal) :
	grid(grid)
    {

    this->result = 0.0;
    this->nbDartTotal = INT_MAX;
    this->nbDartByDevice = nbDartTotal / Device::getDeviceCount();

    }

//Chaque fois qu il y a un malloc dans un concstructeur(forcément fait dans le consctructeur, il faut un free
MontecarloMultiGPU::~MontecarloMultiGPU(void)
    {

    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void MontecarloMultiGPU::run()
    {
    int nbDevice = Device::getDeviceCount();
    long sum;

#pragma omp parallel for reduction(+:sum)
    for (int deviceId = 0; deviceId < nbDevice; deviceId++)
	{
	Device::setDevice(deviceId);
	Montecarlo montecarlo(grid, nbDartByDevice);
	montecarlo.run();
	sum += montecarlo.getNbDartUnderCurve();
	//cout << sum << endl;
	//cout << nbDartTotal << endl;

	}
	result = 4.0 * sum / nbDartTotal;
    }

float MontecarloMultiGPU::getResult()
    {
    return this->result;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

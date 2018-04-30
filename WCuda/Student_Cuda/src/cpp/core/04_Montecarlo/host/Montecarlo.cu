#include "Montecarlo.h"

#include <iostream>

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

Montecarlo::Montecarlo(const Grid& grid, int nbDartTotal)
    {

    this->result = 0.0;
    this->nbDartUnderCurve = 0;
    // Grid
	{
	this->dg = grid.dg;
	this->db = grid.db;
	}
    this->sizeOctetGM = sizeof(int); // octet
    this->sizeOctetSM = sizeof(int) * this->db.x;
    this->sizeOctetGeneratorGM = grid.threadCounts() * sizeof(curandState);
    // MM
	{

	// MM (malloc Device)
	    {
	    //Initialization à zéro
	    Device::malloc(&ptrDevGMResult, sizeOctetGM);
	    Device::memclear(ptrDevGMResult, sizeOctetGM);

	    Device::malloc(&tabDevGeneratorGM, sizeOctetGeneratorGM);
	    Device::memclear(tabDevGeneratorGM, sizeOctetGeneratorGM);
	    }

	Device::lastCudaError("Montecarlo MM (end allocation)"); // temp debug, facultatif
	}
	const int DEVICE_ID = Device::getDeviceId();
	createGenerator<<<dg,db>>>(tabDevGeneratorGM, DEVICE_ID);
	this->nbDartByThread = nbDartTotal / grid.threadCounts();
	this->nbDartTotal = grid.threadCounts() * nbDartByThread;

    }

//Chaque fois qu il y a un malloc dans un concstructeur(forcément fait dans le consctructeur, il faut un free
Montecarlo::~Montecarlo(void)
    {
//MM (device free)
	{
	Device::free(ptrDevGMResult);
	Device::free(tabDevGeneratorGM);
	Device::lastCudaError("Montecarlo MM (end deallocation)"); // temp debug, facultatif
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Montecarlo::run()
    {
    Device::lastCudaError("Montecarlo (before)"); // temp debug
    montecarlo<<<dg,db, sizeOctetSM>>>(tabDevGeneratorGM, ptrDevGMResult, nbDartByThread); // appel d'un kernel -> assynchrone
    Device::lastCudaError("Montecarlo (after)"); // temp debug

    Device::synchronize(); // Temp,debug, only for printf in  GPU, synchronisation explicit
    int resultDevice = 0;
// MM (Device -> Host)
	{

	Device::memcpyDToH(&resultDevice, ptrDevGMResult, sizeOctetGM); // barriere synchronisation implicite
	}
	this->nbDartUnderCurve = resultDevice;
	this->result = 4.0 * resultDevice / nbDartTotal;
    }

float Montecarlo::getResult()
    {
    return this->result;
    }

int Montecarlo::getNbDartUnderCurve()
    {
return this->nbDartUnderCurve;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

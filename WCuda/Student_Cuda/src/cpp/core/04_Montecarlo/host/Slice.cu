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

extern __global__ void montecarlo(float* ptrTabDev, int nbMontecarlo); // déclarer dans un autre fichier, kernel coté device

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

Montecarlo::Montecarlo(const Grid& grid, int nbMontecarlo) :
	nbMontecarlo(nbMontecarlo)
    {

    this->result = 0.0;
    // Grid
	{
	this->dg = grid.dg;
	this->db = grid.db;
	}
    this->sizeOctetGM = sizeof(float); // octet
    this->sizeOctetSM = sizeof(float) * this->db.x;
    // MM
	{

	// MM (malloc Device)
	    {
	    //Initialization à zéro
	    Device::malloc(&ptrTabDev, sizeOctetGM);
	    Device::memclear(ptrTabDev, sizeOctetGM);
	    }

	Device::lastCudaError("Montecarlo MM (end allocation)"); // temp debug, facultatif
	}

    }

//Chaque fois qu il y a un malloc dans un concstructeur(forcément fait dans le consctructeur, il faut un free
Montecarlo::~Montecarlo(void)
    {
//MM (device free)
	{
	Device::free(ptrTabDev);
	Device::lastCudaError("Montecarlo MM (end deallocation)"); // temp debug, facultatif
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Montecarlo::run()
    {
    Device::lastCudaError("Montecarlo (before)"); // temp debug
    montecarlo<<<dg,db, sizeOctetSM>>>(ptrTabDev, nbSlice); // appel d'un kernel -> assynchrone
    Device::lastCudaError("slice (after)"); // temp debug

    Device::synchronize(); // Temp,debug, only for printf in  GPU, synchronisation explicit

// MM (Device -> Host)
	{
	Device::memcpyDToH(&result, ptrTabDev, sizeOctetGM); // barriere synchronisation implicite
	}
    }

float Slice::getResult()
    {
    return result;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

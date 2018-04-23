#include <iostream>
#include "LimitsTools.h"
#include "Grid.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "Slice.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice(void)
    {
    cout << "use" << endl;
    int nbSlice = 1000;
    bool isOk = true;

    // Partie interessante GPGPU
	{
	// Grid cuda
//	int mp = Device::getMPCount();
//	int coreMP = Device::getCoreCountMP();

//	dim3 dg = dim3(mp, 2, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
//	dim3 db = dim3(coreMP, 2, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
//	Grid grid(dg, db);

// pattern 1-1, contraintre le produit ne doit pas dépasser les 1024
//nb de thread est le produit des 6 chiffres, le produit >= n
	cout << "GPU" << endl;
	int mp = Device::getMPCount();
	int coreMP = Device::getCoreCountMP();

	cout << "grid" << endl;

	dim3 dg = dim3(128, 1, 1);
	dim3 db = dim3(8, 1, 1);

	Grid grid(dg, db);

	cout << "slice" << endl;

	Slice slice(grid, nbSlice);

	cout << "befoire slice run" << endl;

	slice.run();

	cout << "after slice run" << endl;

	printf("result %f", slice.getResult());

	}

    cout << "use end" << endl;
    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


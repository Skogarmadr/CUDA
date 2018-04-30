#include <iostream>
#include "LimitsTools.h"
#include "Grid.h"
#include "Device.h"
#include "Chrono.h"
#include "limits.h"
#include "MathTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "MontecarloMultiGPU.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarloMultiGPU(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarloMultiGPU(void)
    {
    cout << "start" << endl;
    bool isOk = true;
    float result;
    long nbDartTot = INT_MAX;

    cout << "GPU" << endl;
    cout << "grid" << endl;

    dim3 dg = dim3(16, 1, 1);
    dim3 db = dim3(1024, 1, 1);

    Grid grid(dg, db);

    cout << "MontecarloMultiGPU" << endl;

    Chrono chrono = Chrono("Time:");

    MontecarloMultiGPU montecarlo(grid, nbDartTot);

    cout << "before MontecarloMultiGPU run" << endl;
    chrono.start();
    montecarlo.run();
    chrono.stop();
    cout << "after MontecarloMultiGPU run" << endl;
    result = montecarlo.getResult();
    chrono.print();
    printf("\nresult = %f", result);

    cout << "\n end" << endl;
    return isOk;

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


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

#include "Montecarlo.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo(void)
    {
    cout << "start" << endl;
    bool isOk = true;
    float result;
    long nbDartTot = INT_MAX;

    cout << "GPU" << endl;
    cout << "grid" << endl;

    dim3 dg = dim3(512, 1, 1);
    dim3 db = dim3(512, 1, 1);

    Grid grid(dg, db);

    cout << "Montecarlo" << endl;

    Chrono chrono = Chrono("Time:");

    Montecarlo montecarlo(grid, nbDartTot);

    cout << "befoire montecarlo run" << endl;
    chrono.start();
    montecarlo.run();
    chrono.stop();
    cout << "after montecarlo run" << endl;
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


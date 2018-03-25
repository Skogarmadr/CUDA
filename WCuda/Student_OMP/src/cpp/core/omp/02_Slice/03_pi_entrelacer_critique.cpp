#include <omp.h>
#include "OmpTools.h"
#include "../02_Slice/00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerCritical_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerCritical(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerCritical_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerCritical, n, "Pi OMP Entrelacer critical");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

double piOMPEntrelacerCritical(int n)
    {
    const int NB_THREADS = OmpTools::setAndGetNaturalGranularity(); //Ca veut dire que le système va mettre autant de thread que de coeur logique
    const double DX = 1 / (double) n;
    int somme = 0;
    double sumThread = 0;
   //Penser parallel
   #pragma omp parallel
   	{
   	//Recuperer TIP, utiliser classe OmpTools


   	int idThread = OmpTools::getTid();
   	const int threadID = OmpTools::getTid();
   	int s = threadID;

   	double xs;

   	double xi;
   	while (s < n)
   	    {
   	    xs = s * DX;
   	    sumThread += fpi(xs);
   	    s += NB_THREADS;
   	    }
   	}
#pragma omp critical
   	{
   	somme+= sumThread;
   	}
       return somme * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


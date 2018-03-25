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

bool isPiOMPEntrelacerPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerPromotionTab(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerPromotionTab, n, "Pi OMP Entrelacer promotionTab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern cuda : excellent!
 */
double piOMPEntrelacerPromotionTab(int n)
    {

    const int NB_THREADS = OmpTools::setAndGetNaturalGranularity(); //Ca veut dire que le système va mettre autant de thread que de coeur logique
    const double DX = 1 / (double) n;
    double tabSumThread[NB_THREADS]; //Toujours préfixe par le nom du conteneur  // Reduction intra Thread additive avec la technique de promotion de tableau
    // La promotion de tableau est pour éviter des les concurrences
//Penser parallel
#pragma omp parallel
	{
	//Recuperer TIP, utiliser classe OmpTools

	double sumThread = 0;
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
	tabSumThread[threadID] = sumThread;
	}
	//Reduction sequentielle du tableau promu prom::Gratuit!
	int somme = 0;
    for (int i = 1; i <= NB_THREADS; i++)
	{
	somme += tabSumThread[i];
	}

    return somme * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


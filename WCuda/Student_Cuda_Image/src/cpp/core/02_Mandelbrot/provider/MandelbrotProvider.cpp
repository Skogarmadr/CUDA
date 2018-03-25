#include "MandelbrotProvider.h"
#include "Mandelbrot.h"

#include "MathTools.h"
#include "Grid.h"

#include "DomaineMath_GPU.h"

using gpu::DomaineMath;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

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
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* MandelbrotProvider::createAnimable()
    {
    DomaineMath domaineMath = DomaineMath(-2.1, -1.3, 0.8, 1.3);

    // Animation;
    float dt = 1;

    // Dimension
    int dw = 16 * 80;
    int dh = 16 * 60;

    // grid cuda
    //int mp=Device::getMPCount();
    //int coreMP=Device::getCoreCountMP();

    dim3 dg = dim3(500, 1, 1);  		// à définir à la main pour "optimiser les performances, enfin trouver le meilleur dg db
    dim3 db = dim3(49, 1, 1);   	// à définir à la main pour "optimiser les performances, enfin trouver le meilleur dg db
    Grid grid(dg, db);

    return new Mandelbrot(grid, dw, dh, dt, domaineMath);
    }

/**
 * Override
 */
Image_I* MandelbrotProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

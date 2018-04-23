#include <iostream>

#include "SceneCubeCreator.h"

//#include "VagueProvider.h"
//#include "DamierProvider.h"

//#include "VagueGrayProvider.h"
//#include "DamierRGBAFloatProvider.h"
//#include "DamierHSBAFloatProvider.h"
//#include "DamierHueFloatProvider.h"

#include "MandelbrotProvider.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

SceneCubeCreator::SceneCubeCreator()
    {
    createImages();
    createScene();
    }

SceneCubeCreator::~SceneCubeCreator()
    {
    delete ptrImage1;
    delete ptrImage2;
    delete ptrImage3;
    delete ptrImage4;
    delete ptrImage5;
    delete ptrImage6;

    delete ptrScene;
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

SceneCube* SceneCubeCreator::getScene()
    {
    return ptrScene;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void SceneCubeCreator::createImages()
    {
    ptrImage1 = MandelbrotProvider().createImageGL();
    ptrImage2 = MandelbrotProvider().createImageGL();
    ptrImage3 = MandelbrotProvider().createImageGL();
    ptrImage4 = MandelbrotProvider().createImageGL();
    ptrImage5 = MandelbrotProvider().createImageGL();
    ptrImage6 = MandelbrotProvider().createImageGL();
    }

void SceneCubeCreator::createScene()
    {
    ptrScene = new SceneCube(ptrImage1, ptrImage2, ptrImage3, ptrImage4, ptrImage5, ptrImage6);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


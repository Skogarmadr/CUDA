#pragma once

#include <iostream>

#include "Forme_A.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class Cercle: public Forme_A
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	Cercle(string name, double rayon);

	virtual ~Cercle();

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	/**
	 * Override
	 */
	virtual double aire(void);

	/**
	 * Override
	 */

	//Sans virutal permet d'éviter d'ovverider
	double perimetre();

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	double rayon;



    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

#ifndef OBSERVER_I_H_
#define OBSERVER_I_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

template<class T>
class Observer_I
    {

    public:

	virtual void onUpdate(T* ptrObservable)=0;

	virtual ~Observer_I()
	    {
	    // Nothing
	    }

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
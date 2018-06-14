#ifndef _TRAIT_H_
#define _TRAIT_H_
#include <typeinfo>
#include <string>
#include <iterator>
#include <iostream>
#include <exception>
#include "Point.h"
#include "StringTokenIterator.h"


namespace MeshLib
{

//!  Trait class. 
/*!
  This class define trait for Edge, Halfedge, Vertex and Face.
*/
class Trait 
{
public:
	//!  Constructor.
	Trait(){ m_next = NULL; };
	//!  Destructor.
	virtual ~Trait(){ };

	//!  Get trait string.
    /*!      
      \return string of this trait.
    */
	std::string & string() { return m_string;};
	//!  Read trait (virtual).
	virtual void read() {};
	//!  Write trait (virtual).
	virtual void write(){};

	//!  Get next trait.
    /*!      
      \return next trait.
    */
	Trait * & next() { return m_next; };

	//!  Add a new trait.
    /*!      
      \param t a new trait to be added.
    */
	void add( Trait * t )
	{
		Trait *  pt = this;
		while( pt->next() != NULL ) pt = pt->next();
		pt->next() = t;
	};

	//!  Clear trait (static).
    /*!      
      \param tT the trait to be clear.
    */
	static void clear( Trait * & pT );
	
	static void updateTraitString(std::string &traitString, std::string &traitName, std::string &traitValue);
	static std::string getTraitValue(std::string &traitString, std::string &traitName);
	static Point getUV(std::string s);
	static Point getConformal(std::string s);
	static void updateUV(std::string &traitString, Point p);

protected:
	//!  Trait string.
	std::string m_string;   //string
	//!  Trait next trait.
	Trait * m_next;

};

//!  Get matched trait.
/*!      
  \param v the object to be checked if the type is the same as expect.
*/
template <typename T, typename V>
T * pTrait( V * v )
{
	Trait * pt = v->trait();
	while( pt != NULL )
	{
		T *t = dynamic_cast<T*> (pt);
		if (t)
			return t;
		//if( typeid(*pt) == typeid(T) )
		//	return (T*)pt;
		pt = pt->next();
	}
	return NULL;
}

//!  Get matched trait (None NULL return).
/*!      
  \param v the object to be checked if the type is the same as expect.
*/
template <typename T, typename V>
T & trait( V * v )
{
	Trait * pt = v->trait();
	while( pt != NULL )
	{
		T *t = dynamic_cast<T*>(pt);
		if(t)
			return *t;
		//if( typeid(*pt) == typeid(T) )
		//	return *((T*)pt);
		pt = pt->next();
	}
	throw std::bad_cast();
	return *((T*)v->trait());
}

//!  Add a new trait.
/*!      
  \param v the object to be added trait.
  \param t the temp trait to be added.
*/
template <typename T, typename V>
void add_trait( V * v, T * t )
{
	t->next() = v->trait();
	v->trait() = ( Trait* ) t;
}

//!  Delet trait.
/*!      
  \param v the object to be delete trait.
  \param t the temp trait to be add
*/
template <typename T, typename V>
void del_trait( V * v, T* t )
{
	if( t == NULL ) return;

	Trait * pT = v->trait();
	while( pT != NULL )
	{
		//TRACE("%s ", pT->GetRuntimeClass()->m_ClassName );
		pT = pT->next();
	}
	//TRACE("\n");

	if( v->trait() == NULL ) return;

	//TRACE("\nTemplate %s \n", t->GetRuntimeClass()->m_ClassName );

	Trait * pt = v->trait();

	if( pt == t )
	{
		v->trait() = pt->next();
		delete (T*)pt;
		pt = NULL;
		return;
	}

	while( pt->next() != NULL )
	{
		if( pt->next() == t ) break;
		pt = pt->next();
	}

	if( pt->next() == NULL ) return;

	Trait * pnt = pt->next();
	pt->next() = pnt->next();
	delete (T*)pnt;
	pnt = NULL;
}

//!  Clear all trait(s).
/*!      
  \param tT the trait list to be clear.
*/
//recursively clean all the trait in the trait list pT
// void clear_trait( Trait * & pT ) {

// }


} //end of meshlib
#endif

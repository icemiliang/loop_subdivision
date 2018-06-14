#ifndef _MESHLIB_EDGE_H_
#define _MESHLIB_EDGE_H_

#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>
#include "Vertex.h"

namespace MeshLib{

class HalfEdge;
class Vertex;
class Trait;

//!  EdgeKey class. 
/*!
  This class define edgekey to simplify edge operation.
*/
class EdgeKey
{

	friend class Edge;
public:

	//!  Constructor 1.
	EdgeKey( ){ m_s = 0; m_t = 0 ; };
	//!  Constructor 2 to make sure source ID < target ID.
	/*!
	  \param s an int which is edge source vertex ID.
	  \param t an int which is edge target vertex ID.
	*/
	EdgeKey( int s, int t ){ if( s < t ){ m_s = s; m_t = t; } else { m_s = t; m_t = s; } ;};
	//!  Destructor.
	~EdgeKey(){};

	//!  == operator.
    /*!      
      \param key a EdgeKey to compare with this edgekey.
      \return the boolean result of the == comparison of two edgekeys.
    */
	bool operator == ( const EdgeKey & key ) const { return m_s == key.m_s  && m_t == key.m_t; };
	//!  < operator.
    /*!      
      \param key a EdgeKey to compare with this edgekey.
      \return the boolean result of the < comparison of two edgekeys.
    */
	bool operator <  ( const EdgeKey & key ) const { return (m_s < key.m_s) || ( m_s == key.m_s && m_t < key.m_t ); };
	//!  != operator.
    /*!      
      \param key a EdgeKey to compare with this edgekey.
      \return the boolean result of the != comparison of two edgekeys.
    */
	bool operator != ( const EdgeKey & key ) const { return m_s != key.m_s  ||   m_t != key.m_t; };
	//!  <= operator.
    /*!      
      \param key a EdgeKey to compare with this edgekey.
      \return the boolean result of the <= comparison of two edgekeys.
    */
	bool operator <= ( const EdgeKey & key ) const { return *this < key || * this == key ;  };

	int s(){ return m_s;};
	int t(){ return m_t;};
	
private:

	//!  Edgekey source ID.
	int m_s;
	//!  Edgekey target ID.
	int m_t;

};


class Edge
{
public:
	Vertex * conjunction(Edge * e);
	double length();
	bool include_vertex(Vertex * v)
	{
		//updated by kewu zhang on April 1
		if(key.m_s == v->id () || key.m_t == v->id ())
			return true;
		return false;
	};
	Vertex * other_vertex(Vertex *v);
	//this function returns the two point
	//it is assumed that  this edge do have cross point with the given condition
	//va = esource()+b0(etarget-esource)/(etarget-esource).norm();
	//vb = esource()+b1(etarget-esource)/(etarget-esource).norm();
	void crosspoint(Point p, double radius, double &b0, double & b1);
	bool on_sphere(Point p, double radius);
	bool coface(Edge * e);
	bool coface(Vertex * v);
	Edge(){ m_halfedge[0] = NULL; m_halfedge[1] = NULL; m_trait = NULL; key.m_s = 0; key.m_t = 0; };
	Edge(int s, int e){ 		m_halfedge[0] = NULL;
		m_halfedge[1] = NULL;
		m_trait = NULL; 
		key = EdgeKey(s, e);
	};
	~Edge(){ };
	
	HalfEdge * & halfedge( int i ) { assert( 0<=i && i < 2 ); return m_halfedge[i];};
	Trait    * & trait()    { return m_trait;};
	bool		 boundary() { return (m_halfedge[0] == NULL && m_halfedge[1] != NULL ) || (m_halfedge[0] != NULL && m_halfedge[1] == NULL ); };
	std::string & string()  { return m_string;};

	HalfEdge * & other( HalfEdge * he ) { return (he != m_halfedge[0] )?m_halfedge[0]:m_halfedge[1]; };

    bool operator== (const Edge & e) const
    {
        return key == e.key;
    };

	EdgeKey & ekey(  ) 
    {
		return key;
    };

    bool operator< (const Edge & e) const
    {
        return key < e.key;
    };

	int & vertex( int id ) { assert( id >= 0 && id < 2 ); return id==0? key.m_s : key.m_t; };

	void get_vertices(Vertex *&v1, Vertex *&v2);

	Vertex * & vertexForSub() { return m_vertexForSub; };

private:

	HalfEdge  * m_halfedge[2];
	EdgeKey key;
	std::string m_string;   //string
	Trait	  * m_trait;
	Vertex * m_vertexForSub;
};



}//name space MeshLib

#endif //_MESHLIB_EDGE_H_ defined

#ifndef _MESHLIB_HALFEDGE_H_
#define _MESHLIB_HALFEDGE_H_

#include <iostream>
#include <string>
#include <math.h>
#include "Edge.h"

namespace MeshLib{

class Vertex;
class Edge;
class Face;
class Trait;

//!  HalfEdge class. 
/*!
  This class defines halfedge.
*/
class HalfEdge{
public:

	//!  Constructor.
	HalfEdge(){ m_edge = NULL; m_vertex = NULL; m_prev = NULL; m_next = NULL; m_face = NULL; m_trait = NULL;};
	//!  Destructor.
	~HalfEdge(){ };

	//!  Get halfedge edge.
    /*!      
      \return the edge which is associated with this halfedge.
    */
	Edge     * & edge()    { return m_edge;   };
	//!  Get halfedge vertex.
    /*!      
      \return a vertex which is associated with this halfedge.
    */
	Vertex   * & vertex()  { return m_vertex; };
	//!  Get halfedge target vertex.
    /*!      
      \return target vertex which is associated with this halfedge.
    */
	Vertex   * & target()  { return m_vertex; };
	//!  Get halfedge source vertex.
    /*!      
      \return source vertex which is associated with this halfedge.
    */
	Vertex   * & source()  { return m_prev->vertex();};
	//!  Get halfedge prev halfedge.
    /*!      
      \return the halfedge which is the prev halfedge of this halfedge.
    */
	HalfEdge * & he_prev() { return m_prev;};
	//!  Get halfedge next halfedge.
    /*!      
      \return the halfedge which is the next halfedge of this halfedge.
    */
	HalfEdge * & he_next() { return m_next;};

	//HalfEdge * & he_sym()  { return m_sym;};

	//!  Get halfedge symmetric halfedge.
    /*!      
      \return the halfedge which is the symmetric halfedge of this halfedge.
    */
	HalfEdge * & he_sym()  { return m_edge->other( this ); };
	//!  Get halfedge face.
    /*!      
      \return the face which is associated with this halfedge.
    */
	Face     * & face()    { return m_face;};
	//!  Get halfedge trait.
    /*!      
      \return trait(s) of this halfedge.
    */
	Trait	 * & trait()   { return m_trait;};

	//!  Halfedge ccw rotate about target vertex.
    /*!      
      \return the halfedge which is get from this halfedge ccw rotation about the target vertex..
    */
	HalfEdge *   ccw_rotate_about_target();
	//!  Halfedge clw rotate about target vertex.
    /*!      
      \return the halfedge which is get from this halfedge clw rotation about the target vertex..
    */
	HalfEdge *   clw_rotate_about_target();

	//!  Halfedge ccw rotate about source vertex.
    /*!      
      \return the halfedge which is get from this halfedge ccw rotation about the source vertex..
    */
	HalfEdge *   ccw_rotate_about_source();
	//!  Halfedge ccw rotate about source vertex.
    /*!      
      \return the halfedge which is get from this halfedge ccw rotation about the source vertex..
    */
	HalfEdge *   clw_rotate_about_source();

	//!  Get halfedge trait.
    /*!      
      \return trait(s) of this halfedge.
    */
	std::string & string(){ return m_string; };

private:

	//!  Halfedge edge.
	Edge     *     m_edge;
	//!  Halfedge face.
	Face     *     m_face;
	//!  Halfedge Vertex (target).
	Vertex   *     m_vertex;		//target vertex
	//!  Halfedge prev halfedge.
	HalfEdge *	   m_prev;
	//!  Halfedge next halfedge.
	HalfEdge *     m_next;
	//HalfEdge *     m_sym;
	//!  Halfedge string.
	std::string    m_string;
	//!  Halfedge trait.
	Trait	 *	   m_trait;

};

//!  HalfEdgeKey class. 
/*!
  This class define halfedgekey to simplify halfedge operation.
*/
class HalfEdgeKey
{

public:

	//!  Constructor 1.
	HalfEdgeKey(){ m_s = 0; m_t = 0; };
	//!  Constructor 2.
	/*!
	  \param s an int which is halfedge source vertex ID.
	  \param t an int which is halfedge target vertex ID.
	*/
	HalfEdgeKey( int s, int t ){ m_s = s; m_t = t; };
	//!  Destructor.
	~HalfEdgeKey(){};

	//!  == operator.
    /*!      
      \param key a HalfEdgeKey to compare with this halfedgekey.
      \return the boolean result of the == comparison of two halfedgekeys.
    */
	bool operator == ( const HalfEdgeKey & key ) const { return m_s == key.m_s  && m_t == key.m_t; };
	//!  < operator.
    /*!      
      \param key a HalfEdgeKey to compare with this halfedgekey.
      \return the boolean result of the == comparison of two halfedgekeys.
    */
	bool operator < ( const  HalfEdgeKey & key ) const { return (m_s < key.m_s) || ( m_s == key.m_s && m_t < key.m_t ); };
	//!  != operator.
    /*!      
      \param key a HalfEdgeKey to compare with this halfedgekey.
      \return the boolean result of the == comparison of two halfedgekeys.
    */
	bool operator != ( const HalfEdgeKey & key ) const { return m_s != key.m_s  ||   m_t != key.m_t; };
	//!  <= operator.
    /*!      
      \param key a HalfEdgeKey to compare with this halfedgekey.
      \return the boolean result of the == comparison of two halfedgekeys.
    */
	bool operator <= ( const HalfEdgeKey & key ) const { return *this < key || * this == key ;  };

private:

	//!  Edgekey source ID.
	int m_s;
	//!  Edgekey target ID.
	int m_t;

};

//!  lthalfedgekey. 
/*!
  This struct defines < operation of two halfkeys.
*/
struct lthalfedgekey
{
  //!  () operator to get < operation.
    /*!      
      \param s1 a HalfEdgeKey to be compared with another.
	  \param s2 a HalfEdgeKey to be compared with another.
      \return the boolean result of the < comparison of two halfedgekeys.
    */
  bool operator()(const HalfEdgeKey s1, const HalfEdgeKey s2) const
  {
    return s1<s2;
  }
};



}//name space MeshLib

#endif //_MESHLIB_HALFEDGE_H_ defined

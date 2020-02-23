#ifndef _MESHLIB_FACE_H_
#define _MESHLIB_FACE_H_

#include <iostream>
#include <string>
#include <math.h>
#include "Point.h"

namespace MeshLib{


class HalfEdge;
class Trait;
class Edge;
class Vertex;

//!  Face class. 
/*!
  This class defines triangle faces.
*/

class Face
{
public:

	Point norm();
	bool include_edge(Edge * e);
	bool include_vertex(Vertex * v);

	//!  Constructor.
	Face(){ m_halfedge = NULL; m_trait=NULL; };
	//!  Destructor.
	~Face(){ };
	
	//!  Get face halfedge.
    /*!      
      \return A halfedge belongs to this face.      
    */
	HalfEdge    * & halfedge() { return m_halfedge; };

	//!  Get face trait.
    /*!      
      \return trait(s) of this face.      
    */
	Trait		* & trait()    { return m_trait;};
	//!  Get face id
    /*!      
      \return id of this face.      
    */
	int		      & id()       { return m_id; };
	//!  Get face id.
    /*!      
      \return id of this face .     
    */
	const int       id() const { return m_id; };

	//!  Get face string.
    /*!      
      \return string of this face .     
    */
	std::string &   string()   { return m_string;};

	//!  == operator defination.
    /*!
	  \param f a Face to compare with this face.
      \return the boolean result of the comparison of two faces.
    */
    bool operator== (const Face & f) const
    {
        return m_id == f.id();
    };

	//!  < operator defination.
    /*!
	  \param f a Face to compare with this face.
      \return the boolean result of the < comparison of two faces.
    */
    bool operator< (const Face & f) const
    {
        return f.id() >= m_id; 
    };

private:
	//!  Face ID.
	int			  m_id;
	//!  Face halfedge
	HalfEdge    * m_halfedge;
	//!  Face string
	std::string   m_string;   //string
	//!  Face trait
	Trait	    * m_trait;
	
};

//!  Output a face.
/*!
  \param co a ostream to hold output information as a return value.
  \param f a Face to be output.
  \return the ostream which contains the face output information.
*/ 
std::ostream & operator << ( std::ostream & co, const Face & f);

}//name space MeshLib

#endif //_MESHLIB_FACE_H_ defined

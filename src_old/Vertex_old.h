#ifndef _MESHLIB_VERTEX_H_
#define _MESHLIB_VERTEX_H_

#include <iostream>
#include <string>
#include <math.h>
#include "Point.h"

namespace MeshLib{

class HalfEdge;
class Trait;

//!  Vertex class. 
/*!
  This class defines vertex.
*/
class Vertex{

public:

	//!  Constructor.
	Vertex(){ m_halfedge = NULL; m_boundary = false; m_trait = NULL; };
	//!  Destructor.
	~Vertex(){};

	Vertex * & vertexForSub() { return  m_vertexForSub; };



	//!  Get vertex point.
    /*!      
      \return A point belongs to this vertex.
    */
	Point & point() { return  m_point; };
	//!  Get vertex normal.
    /*!      
      \return normal of this vertex.
    */
	Point & normal(){ return  m_normal;};
	
	//!  Get vertex most ccw out halfedge.
    /*!      
      \return the halfedge which is most ccw outgoing from this vertex.
    */
	HalfEdge *  most_ccw_out_halfedge();
	//!  Get vertex most clw out halfedge.
    /*!      
      \return the halfedge which is most clw outgoing from this vertex.
    */
	HalfEdge *  most_clw_out_halfedge();
	//!  Get vertex most ccw in halfedge.
    /*!      
      \return the halfedge which is most ccw incoming from this vertex.
    */
	HalfEdge *  most_ccw_in_halfedge();
	//!  Get vertex most clw in halfedge.
    /*!      
      \return the halfedge which is most clw incoming from this vertex.
    */
	HalfEdge *  most_clw_in_halfedge();

	//!  Get vertex halfedge.
    /*!      
      \return the halfedge whose target (source) vertex is this vertex. // Error found Liang Mi 9/26/2015 should be target but was source before
    */
	HalfEdge * & halfedge()		{ return m_halfedge; };
	//!  Get vertex trait.
    /*!      
      \return trait(s) of this vertex.
    */
	Trait *    & trait()		{ return m_trait; };

	//!  Get vertex id.
    /*!      
      \return the id of this vertex.
    */
	int & id() { return m_id; };
	//!  Get vertex id.
    /*!      
      \return the id of this vertex.
    */
	const int   id() const  { return m_id; };

	//!  Get vertex boundary status.
    /*!      
      \return the boolean of this vertex boundary status.
    */
	bool  & boundary() { return m_boundary; };

	//!  Get vertex string.
    /*!      
      \return the string {string} of this vertex.
    */
	std::string & string() { return m_string;};


	//!  == operator.
    /*!      
      \param v a Vertex to compare with this vertex.
      \return the boolean result of the comparison of two vertices.
    */
    bool operator== (const Vertex & v) const
    {
        return m_id == v.id();
    };

    
	//!  < operator.
    /*!      
      \param v a Vertex to compare with this vertex.
      \return the boolean result of the < comparison of two vertices.
    */
	bool operator< (const Vertex & v) const
    {
        return v.id() >= m_id; 
    };


private:
	//!  Vertex id.
	int	  m_id;

	//!  Vertex point.
	Point m_point;
	//!  Vertex normal.
	Point m_normal;

	//!  Vertex halfedge.
	HalfEdge * m_halfedge;
	//!  Boundary Vertex marker.
	bool       m_boundary;

	//!  Vertex string.
	std::string  m_string;
	//!  Vertex trait.
	Trait	   * m_trait;

	Vertex * m_vertexForSub;

};

//!  Output a vertex.
/*!
  \param co a ostream to hold output information as a return value.
  \param v a Vertex to be output.
  \return the ostream which contains the vertex output information.
*/ 
std::ostream & operator << ( std::ostream & co, const Vertex & v);

}//name space MeshLib

#endif //_MESHLIB_VERTEX_H_ defined

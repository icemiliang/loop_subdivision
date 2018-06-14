#ifndef _EDIT_TRAIT_H_
#define _EDIT_TRAIT_H_

#include <string>
#include <iterator>
#include "Trait.h"
#include "Parser.h"

namespace MeshLib
{


#define v_edit_halfedge( v ) trait<EditVertexTrait,Vertex>(v).hlist()


class EditVertexTrait : public Trait	//corner angle
{
public:
	   //!  Constructor.
	EditVertexTrait(){ m_hlist = new List<HalfEdge>;};
		//!  Destructor.
	~EditVertexTrait(){ delete m_hlist;};
	void read()  {};
	void write() {};
	//!  Return the value of m_area.
    /*!      
      \Return the value of m_area.  
    */
	List<HalfEdge>*  hlist()   { return m_hlist; };
private:
	List<HalfEdge> * m_hlist;

};


} //namespace 
#endif

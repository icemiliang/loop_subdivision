#ifndef _MESHLIB_ITERATORS_H_
#define _MESHLIB_ITERATORS_H_

#include <iostream>
#include <map>
#include <math.h>
#include "Solid.h"
#include "Avltree.h"

#include "TopologyException.h"

namespace MeshLib{


class Vertex;
class HalfEdge;
class Edge;
class Face;
class Solid;


//sequencial iterators

//v->out halfedge


class VertexOutHalfedgeIterator
{
public:
	VertexOutHalfedgeIterator( Solid::tSolid  solid, Solid::tVertex  & v )
	{ m_solid = solid; m_vertex = v; m_halfedge = solid->vertexMostClwOutHalfEdge(v); };

	~VertexOutHalfedgeIterator(){};
	void operator++()
	{
		if( m_halfedge == NULL ) throw TopologyException("iterators"); 
		if( m_halfedge == m_solid->vertexMostCcwOutHalfEdge(m_vertex) ) 
			 m_halfedge = NULL;
		 else
	 		m_halfedge = m_solid->vertexNextCcwOutHalfEdge(m_halfedge); };

		Solid::tHalfEdge value() { return m_halfedge; };
		bool end(){ return m_halfedge == NULL; };
		Solid::tHalfEdge operator*() { return value(); };

private:
	Solid::tSolid    m_solid;
	Solid::tVertex   m_vertex;
	Solid::tHalfEdge m_halfedge;
};

//v->in halfedge
class VertexInHalfedgeIterator
{
public:
	VertexInHalfedgeIterator( Solid::tSolid  solid, Solid::tVertex & v )
	{ m_solid = solid; m_vertex = v; m_halfedge = solid->vertexMostClwInHalfEdge(v); };

	~VertexInHalfedgeIterator(){};
	void operator++()
	{
		if( m_halfedge == NULL ) throw TopologyException("iterators"); 
		 if( m_halfedge == m_solid->vertexMostCcwInHalfEdge(m_vertex) ) 
			 m_halfedge = NULL; 
		else
			m_halfedge = m_solid->vertexNextCcwInHalfEdge(m_halfedge); 
	};

	 Solid::tHalfEdge value() { return m_halfedge; };
	 bool end(){ return m_halfedge == NULL; };
	 Solid::tHalfEdge operator*() { return value(); };

private:
	Solid::tSolid    m_solid;
	Solid::tVertex   m_vertex;
	Solid::tHalfEdge m_halfedge;
};


//v -> v

class VertexVertexIterator
{
public:

	VertexVertexIterator( Solid::tVertex  v )
	{ 
		m_vertex = v; 
		m_halfedge = m_vertex->most_clw_out_halfedge();
	};

	~VertexVertexIterator(){};

	void operator++()
	{
		if( m_halfedge == NULL ) throw TopologyException("iterators"); 
		
		if( !m_vertex->boundary() )
		{
			if( m_halfedge != m_vertex->most_ccw_out_halfedge() )
			{
				m_halfedge = m_halfedge->ccw_rotate_about_source();
			}
			else
			{
				m_halfedge = NULL;
			}
			return;
		}

		if( m_vertex->boundary() )
		{
			if( m_halfedge == m_vertex->most_ccw_in_halfedge() )
			{
				m_halfedge = NULL;
				return;
			}

			HalfEdge * he = m_halfedge->ccw_rotate_about_source();

			if( he == NULL )
			{
				m_halfedge = m_vertex->most_ccw_in_halfedge();
			}
			else
			{
				m_halfedge = he;
			}
		}

		return;
	};


	 Solid::tVertex value() 
	 { 
		 if( !m_vertex->boundary() )
		 {
			 return m_halfedge->target(); 
		 }

		 if( m_halfedge != m_vertex->most_ccw_in_halfedge() )
		 {
			 return m_halfedge->target();
		 }

		 if( m_halfedge == m_vertex->most_ccw_in_halfedge() )
		 {
			 return m_halfedge->source();
		 }
		 return NULL;
	 };

	 Solid::tVertex operator*() { return value(); };

	 bool end(){ return m_halfedge == NULL; };

	 void reset()	{ m_halfedge = m_vertex->most_clw_out_halfedge(); };

private:
	Solid::tVertex   m_vertex;
	Solid::tHalfEdge m_halfedge;
};


//v -> edge

class VertexEdgeIterator
{
public:

	VertexEdgeIterator( Solid::tVertex  v )
	{ 
		m_vertex = v; 
		m_halfedge = m_vertex->most_clw_out_halfedge();
	};

	~VertexEdgeIterator(){};

	void operator++()
	{
		if( m_halfedge == NULL ) throw TopologyException("iterators");; 
		
		if( !m_vertex->boundary() )
		{
			if( m_halfedge != m_vertex->most_ccw_out_halfedge() )
			{
				m_halfedge = m_halfedge->ccw_rotate_about_source();
			}
			else
			{
				m_halfedge = NULL;
			}
			return;
		}

		if( m_vertex->boundary() )
		{
			if( m_halfedge == m_vertex->most_ccw_in_halfedge() )
			{
				m_halfedge = NULL;
				return;
			}

			HalfEdge * he = m_halfedge->ccw_rotate_about_source();

			if( he == NULL )
			{
				m_halfedge = m_vertex->most_ccw_in_halfedge();
			}
			else
			{
				m_halfedge = he;
			}
		}

		return;
	};


	 Solid::tEdge value() 
	 { 
		 if( m_halfedge == NULL ) throw TopologyException("iterators");
		 return m_halfedge->edge();
	 };

	 Solid::tEdge operator*() { return value(); };

	 bool end(){ return m_halfedge == NULL; };

	 void reset()	{ m_halfedge = m_vertex->most_clw_out_halfedge(); };

private:
	Solid::tVertex   m_vertex;
	Solid::tHalfEdge m_halfedge;
};



// v->face
class VertexFaceIterator
{
public:
	VertexFaceIterator( Solid::tVertex & v )
	{ 
		m_vertex = v; 
		m_halfedge = m_vertex->most_clw_out_halfedge(); 
	};

	~VertexFaceIterator(){};

	void operator++()
	{
		if( m_halfedge == NULL ) throw TopologyException("iterators");  

		if( m_halfedge == m_vertex->most_ccw_out_halfedge() ) 
		{
			m_halfedge = NULL;
			return;
		}
		m_halfedge = m_halfedge->ccw_rotate_about_source();
	};

	 Solid::tFace value() { return m_halfedge->face(); };
	 Solid::tFace operator*() { return value(); };
	 bool end(){ return m_halfedge == NULL; };
	 void reset()	{ m_halfedge = m_vertex->most_clw_out_halfedge(); };

private:
	Solid::tVertex   m_vertex;
	Solid::tHalfEdge m_halfedge;
};

// f -> halfedge
class FaceHalfedgeIterator
{
public:

	FaceHalfedgeIterator( Solid::tFace & f )
	{ 
		m_face = f; 
		m_halfedge = f->halfedge(); 
	};

	~FaceHalfedgeIterator(){};

	void operator++()
	{
		if( m_halfedge == NULL ) throw TopologyException("iterators");
		m_halfedge = m_halfedge->he_next();

		if( m_halfedge == m_face->halfedge() )
		{
			 m_halfedge = NULL;
			return;
		};
	}

	Solid::tHalfEdge value() { return m_halfedge; };
	Solid::tHalfEdge operator*() { return value(); };

	bool end(){ return m_halfedge == NULL; };

private:
	Solid::tFace     m_face;
	Solid::tHalfEdge m_halfedge;
};


// f -> edge
class FaceEdgeIterator
{
public:

	FaceEdgeIterator( Solid::tFace & f )
	{ 
		m_face = f; 
		m_halfedge = f->halfedge(); 
	};

	~FaceEdgeIterator(){};

	void operator++()
	{
		if( m_halfedge == NULL ) throw TopologyException("iterators");
		m_halfedge = m_halfedge->he_next();

		if( m_halfedge == m_face->halfedge() )
		{
			 m_halfedge = NULL;
			return;
		};
	}

	Solid::tEdge value() { return m_halfedge->edge(); };
	Solid::tEdge operator*() { return value(); };

	bool end(){ return m_halfedge == NULL; };

private:
	Solid::tFace     m_face;
	Solid::tHalfEdge m_halfedge;
};


// f -> vertex
class FaceVertexIterator
{
public:

	FaceVertexIterator( Solid::tFace & f )
	{ 
		m_face = f; 
		m_halfedge = f->halfedge(); 
	};

	~FaceVertexIterator(){};

	void operator++()
	{
		if( m_halfedge == NULL ) throw TopologyException("iterators");
		m_halfedge = m_halfedge->he_next();

		if( m_halfedge == m_face->halfedge() )
		{
			 m_halfedge = NULL;
			return;
		};
	}

	Solid::tVertex value() { return m_halfedge->target(); };
	Solid::tVertex operator*() { return value(); };

	bool end(){ return m_halfedge == NULL; };

private:
	Solid::tFace     m_face;
	Solid::tHalfEdge m_halfedge;
};


// solid vertices
class SolidVertexIterator
{
public:
	SolidVertexIterator( Solid::tSolid solid ): m_solid(solid), m_iter( solid->m_verts )
	{
	}

	Solid::tVertex value() { return *m_iter; };

	void operator++() { ++ m_iter; };

	bool end() { return m_iter.end(); }

	Solid::tVertex operator*(){ return value(); };

	void reset() { m_iter.reset(); };

private:
	Solid::tSolid m_solid;
	AVL::TreeIterator<Vertex> m_iter;
};

// solid faces
class SolidFaceIterator
{
public:
	SolidFaceIterator( Solid::tSolid solid ): m_solid(solid), m_iter( solid->m_faces )
	{
	}

	Solid::tFace value() { return *m_iter; };

	void operator++() { ++ m_iter; };

	bool end() { return m_iter.end(); }

	Solid::tFace operator*(){ return value(); };

	void reset() { m_iter.reset(); };

private:
	Solid::tSolid m_solid;
	AVL::TreeIterator<Face> m_iter;
};

// solid edges
class SolidEdgeIterator
{
public:
	SolidEdgeIterator( Solid::tSolid solid ): m_solid(solid), m_iter( solid->m_edges )
	{
	}

	Solid::tEdge value() { return *m_iter; };

	void operator++() { ++ m_iter; };

	bool end() { return m_iter.end(); }

	Solid::tEdge operator*(){ return value(); };

	void reset() { m_iter.reset(); };

private:
	Solid::tSolid m_solid;
	AVL::TreeIterator<Edge> m_iter;
};

// solid halfedges
class SolidHalfEdgeIterator
{
public:
	SolidHalfEdgeIterator( Solid::tSolid solid ): m_solid(solid), m_iter( solid->m_edges ), m_id(0)
	{
	}

	Solid::tHalfEdge value() { Solid::tEdge e = *m_iter; return e->halfedge(m_id); };

	void operator++() 
	{ 
		++m_id;

		switch( m_id )
		{
		case 1:
			{
				Solid::tEdge e = *m_iter;
				if( e->halfedge(m_id) == NULL )
				{
					m_id = 0;
					++ m_iter;
				}
			}
			break;
		case 2:
			m_id = 0;
			++m_iter;
			break;
		}
	};

	bool end() { return m_iter.end(); }

	Solid::tHalfEdge operator*(){ return value(); };

	void reset() { m_iter.reset(); m_id = 0; };

private:
	Solid::tHalfEdge m_he;
	Solid::tSolid	 m_solid;
	AVL::TreeIterator<Edge> m_iter;
	int  m_id;
};


} //solid 

#endif

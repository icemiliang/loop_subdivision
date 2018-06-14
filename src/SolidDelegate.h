#ifndef _MESHLIB_SOLID_DELEGATE_H_
#define _MESHLIB_SOLID_DELEGATE_H_

#include "Solid.h"

namespace MeshLib{


class SolidDelegate 
{
	public:
		SolidDelegate() {  };
		~SolidDelegate(){ };

		Vertex *	edgeSplit(Solid *pS, Edge *edge);
		Vertex *	createVertex( Solid * pS,   int id  );
		Face   *	createFace( Solid * pS, int * v, int id ); 

		//added by kewu zhang for adaptive subdivision

		void removeFace( Solid * pS, Face * f);
		void removeEdge (Solid * pS, Edge * e);
		void removeVertex (Solid * pS, Vertex * v);

		void removeFace2( Solid *pS, Face *f);
		void removeHalfedge( Solid *pS, HalfEdge *he);

		void collapseEdge(Solid *pS, Edge * e);
		bool collapsable(Solid *pS, Edge * e);

		void destroyVertex(Solid *pS, Vertex * v);
		void destroyHalfEdge(Solid * pS, HalfEdge * he);
		void destroyEdge(Solid *pS, Edge * e);
		void destroyFace(Solid *pS, Face * f);


		void collapseEdgeVertex( Solid *pS, Edge *edge, Vertex * vertex );
};		

}//meshlib 
#endif

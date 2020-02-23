#ifndef _MESHLIB_MESH_DELEGATE_H_
#define _MESHLIB_MESH_DELEGATE_H_

#include "Mesh.h"

namespace MeshLib{


class MeshDelegate 
{
	public:
		MeshDelegate() {  };
		~MeshDelegate(){ };

		// Vertex *	edgeSplit(Mesh *pS, Edge *edge);
		Vertex *	createVertex( Mesh * pS,   int id  );
		Face   *	createFace( Mesh * pS, Vertex * v[], int id ); 

		//added by kewu zhang for adaptive subdivision

		// void removeFace( Mesh * pS, Face * f);
		// void removeEdge (Mesh * pS, Edge * e);
		// void removeVertex (Mesh * pS, Vertex * v);

		// void removeFace2( Mesh *pS, Face *f);
		// void removeHalfedge( Mesh *pS, HalfEdge *he);

		// void collapseEdge(Mesh *pS, Edge * e);
		// bool collapsable(Mesh *pS, Edge * e);

		// void destroyVertex(Mesh *pS, Vertex * v);
		// void destroyHalfEdge(Mesh * pS, HalfEdge * he);
		// void destroyEdge(Mesh *pS, Edge * e);
		// void destroyFace(Mesh *pS, Face * f);


		// void collapseEdgeVertex( Mesh *pS, Edge *edge, Vertex * vertex );
};		

}//meshlib 
#endif

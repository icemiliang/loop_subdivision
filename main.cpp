// loop-subdivision
//
// Author   : Mi, Liang (Arizona State University)
// Email    : icemiliang@gmail.com
// Date     : June 13th 2018

#include <fstream>
#include <vector>
#include <cmath>

#include "OBJFileReader.h"
#include "Solid.h"
#include "Iterators.h"
#include "SolidDelegate.h"
 
using namespace MeshLib;

float calculateAlpha(int n){
	float alpha;
	if (n > 3){
		float center = (0.375f + (0.25f * cos((2.0f * 3.1415926f) / (float)n)));
		alpha = (0.625f - (center * center)) / (float)n;
	}
	else {
		alpha = 3.0f / 16.0f;
	}
	return alpha;
}

int main(int argc, char *argv[])
{
	std::cout << "--> Reading mesh..." << std::endl;
	// Read in the obj file
	Solid mesh; // old mesh
	OBJFileReader of;
	std::ifstream in(argv[1]);
	of.readToSolid(&mesh, in);

	Solid mesh2; // new mesh
	int vid = 0;
	int fid = 0;
	SolidDelegate solidHelper;

	std::cout << "--> Creating new vertices..." << std::endl;

	// scan all vertices and update its coordinates
	for ( SolidVertexIterator viter(&mesh); !viter.end(); ++viter){
		Vertex *v = *viter;
		Vertex *vNew = solidHelper.createVertex(&mesh2, ++vid);

		// Crease
		// boundary
		if (v->boundary()){
			//vNew->point() = v->point(); // simplest way
			std::vector <Point > plist;
			HalfEdge *he = v->halfedge();

			if (he->edge()->boundary()){
				// find second most clw neighbour
				do {
					he = he->clw_rotate_about_target();
				} while (he->clw_rotate_about_target());
				if (he == he->edge()->halfedge(0)){
					he = he->edge()->halfedge(1);
				}
				else if (he == he->edge()->halfedge(1)){
					he = he->edge()->halfedge(0);
				}

				//find most clw neighbour
				he = he->clw_rotate_about_source();

				// assign new value
				vNew->point() = v->point()*3/4 + (v->halfedge()->source()->point() + he->target()->point())/8;
			}
			else{
				// find most ccw neighbour
				do { 
					he = he->ccw_rotate_about_target();
					plist.push_back(he->source()->point()); 
				} while (!he->edge()->boundary());
				vNew->point() = v->point() * 3.0f / 4.0f + plist.back() / 8.0f;

				// find second most clw neighbour
				do { 
					he = he->clw_rotate_about_target();
					plist.push_back(he->source()->point()); 
				} while (he->clw_rotate_about_target());
				if (he == he->edge()->halfedge(0)){
					he = he->edge()->halfedge(1);
				}
				else if (he == he->edge()->halfedge(1)){
					he = he->edge()->halfedge(0);
				}

				//find most clw neighbour
				he = he->clw_rotate_about_source();

				// update new value
				vNew->point() = vNew->point() + he->target()->point() / 8.0f;
			}
		}
		else{
			// examine all neighboring vertices
			std::vector <Point > plist;
			HalfEdge *he = v->halfedge();

			int n = 0;

			// clw rotate
			do {
				plist.push_back(he->source()->point()); // save point
				he = he->clw_rotate_about_target();
				n++;
			} while (he != v->halfedge());

			float alpha = calculateAlpha(n);

			Point temp = { 0.0f, 0.0f, 0.0f };
			for (int i = 0; i < n; i++){
				temp += plist.back();
				plist.pop_back();
			}
			// assign value
			vNew->point() = v->point() *(1 - n*alpha) + temp.operator*(alpha);
		}
		
		v->vertexForSub() = vNew; // added a new trait in vertex.h
	}

	// scan all edges and create vertex on each edge
	SolidEdgeIterator eiter(&mesh);
	for (; !eiter.end(); ++eiter){
		Edge *e = *eiter;
		Vertex *ev1 = mesh.idVertex(e->vertex(0));
		Vertex *ev2 = mesh.idVertex(e->vertex(1));
		Vertex *vNew = solidHelper.createVertex(&mesh2, ++vid);

		// Crease
		// Boundary
		if (e->boundary()){
			vNew->point() = (ev1->point() + ev2->point()) / 2.0f;
		}
		// else
		else{
			vNew->point() = (ev1->point() + ev2->point()) * 3.0f / 8.0f;
			Vertex *vt1 = e->halfedge(0)->he_next()->target();
			Vertex *vt2 = e->halfedge(1)->he_next()->target();
			vNew->point() = vNew->point() + (vt1->point() + vt2->point()) / 8.0f;
		}

		e->vertexForSub() = vNew; // added a new trait in edge.h
	} 

	// Create new faces
	std::cout << "--> Creating new faces..." << std::endl;
	SolidFaceIterator fiter(&mesh);
	for(; !fiter.end(); ++fiter){
		Face *f = *fiter;
		HalfEdge * fhe[3];
		fhe[0] = f->halfedge();
		fhe[1] = fhe[0]->he_next();
		fhe[2] = fhe[1]->he_next();

		Vertex * v[3];
		int vIndex[3];

		// create the central small triangle
		for (int i = 0; i < 3; i++){
			v[i] = fhe[i]->edge()->vertexForSub(); vIndex[i] = v[i]->id();
		}
		solidHelper.createFace(&mesh2, vIndex, vid);

		// create small triangles in three corners
		for (int i = 0; i < 3; i++){
			v[0] = fhe[i]->source(); vIndex[0] = v[0]->id();
			v[1] = fhe[i]->edge()->vertexForSub(); vIndex[1] = v[1]->id();
			v[2] = fhe[(i+2)%3]->edge()->vertexForSub(); vIndex[2] = v[2]->id();
			solidHelper.createFace(&mesh2, vIndex, ++fid);
		}
	}

	mesh2.labelBoundaryEdges(); 

	// Write out the resultant obj file
	std::cout << "--> Writing new mesh..." << std::endl;
	int vObjID = 1;
	std::map<int, int> vidToObjID;

	std::ofstream os(argv[2]);

	SolidVertexIterator iter2(&mesh2);
	for(; !iter2.end(); ++iter2)
	{
		Vertex *v = *iter2;
		Point p = v->point();
		os << "v " << p[0] << " " << p[1] << " " << p[2] << std::endl;
		vidToObjID[v->id()] = vObjID++;
	}
	os << "# " << (unsigned int)mesh2.numVertices() << " vertices" << std::endl;
	float u = 0.0, v = 0.0;
	for(iter2.reset(); !iter2.end(); ++iter2)
	{
		Vertex *vv = *iter2;
		std::string key( "uv" );
		std::string s = Trait::getTraitValue (vv->string(), key );
		if( s.length() > 0 )
		{
			sscanf( s.c_str (), "%f %f", &u, &v );
		}
		os << "vt " << u << " " << v << std::endl;
	}
	os << "# " << (unsigned int)mesh2.numVertices() << " texture coordinates" << std::endl;
	SolidFaceIterator fiter2(&mesh2);
	for(; !fiter2.end(); ++fiter2)
	{
		Face *f = *fiter2;
		FaceVertexIterator viter(f);
		os << "f " ;
		for(; !viter.end(); ++viter)
		{
			Vertex *v = *viter;
			os << vidToObjID[v->id()] << "/" << vidToObjID[v->id()] << " ";
		}
		os << std::endl;
	}
	os.close();
	std::cout << "--> Complete." << std::endl;
	return 0;
}

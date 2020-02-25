// loop-subdivision
//
// Author   : Mi, Liang (Arizona State University)
// Email    : icemiliang@gmail.com
// Date     : Feb 22nd 2020
// License  : MIT

#include "LOOP.h"
#include <assert.h>
#include <math.h>
#include <float.h>
#include <iostream>
#include <sstream>

using namespace MeshLib;


LOOP::LOOP(Mesh * mesh1, Mesh *mesh2) {
	m_mesh1 = mesh1;
	m_mesh2 = mesh2;
}

LOOP::~LOOP(){}


float LOOP::calculateAlpha(int n){
	float alpha;
	if (n > 3){
		float center = (0.375f + (0.25f * cos(6.2831853f / (float)n))); // 2.0f * 3.1415926f
		alpha = (0.625f - (center * center)) / (float)n;
	}
	else {
		alpha = 0.1875f; // 3.0f / 16.0f;
	}
	return alpha;
}

void LOOP::subdivide() {
	// scan all vertices and update its coordinates
	int vid = 0;
	for (MeshVertexIterator viter(m_mesh1); !viter.end(); ++viter){
		Vertex *v = *viter;
		Vertex *vNew = m_mesh2->create_vertex(++vid);

		// Crease
		if (v->boundary()) {
			//vNew->point() = v->point(); // Linear, blow is quadratic

			std::vector <Point > plist;
			
			// find most clw neighbor
			HalfEdge *a = v->halfedge();
			while (a->clw_rotate_about_target()) {
				a = a->clw_rotate_about_target();
			} 
			a = a->he_next();

			// find most ccw neighbor
			HalfEdge *b = v->halfedge();
			while (b->ccw_rotate_about_target()) {
				b = b->clw_rotate_about_target();
			} 

			// assign new value
			vNew->point() = v->point() * 0.75f + (b->source()->point() + a->target()->point()) * 0.125f;

		}
		else {
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

			Point temp = {0.0f, 0.0f, 0.0f};
			for (int i = 0; i < n; i++){
				temp += plist.back();
				plist.pop_back();
			}
			// assign value
			vNew->point() = v->point() * (1 - n * alpha) + temp * alpha;
		}
		v_v(v) = vNew;
	}

	// scan all edges and create vertex on each edge
	for (MeshEdgeIterator eiter(m_mesh1); !eiter.end(); ++eiter){
		Edge *e = *eiter;
		Vertex *ev1 = e->halfedge(0)->source();
		Vertex *ev2 = e->halfedge(0)->target();
		Vertex *vNew = m_mesh2->create_vertex(++vid);

		// Crease
		if (e->boundary()){
			vNew->point() = (ev1->point() + ev2->point()) * 0.5f;
		}
		else{
			vNew->point() = (ev1->point() + ev2->point()) * 0.375f;
			Vertex *vt1 = e->halfedge(0)->he_next()->target();
			Vertex *vt2 = e->halfedge(1)->he_next()->target();
			vNew->point() = vNew->point() + (vt1->point() + vt2->point()) * 0.125f;
		}

		e_v(e) = vNew;
	} 

	// Create new faces
	int fid = 0;
	for (MeshFaceIterator fiter(m_mesh1); !fiter.end(); ++fiter){
		Face *f = *fiter;
		HalfEdge * fhe[3];
		fhe[0] = f->halfedge();
		fhe[1] = fhe[0]->he_next();
		fhe[2] = fhe[1]->he_next();

		Vertex * v[3];
	
		// create the central small triangle
		for (int i = 0; i < 3; i++){
			v[i] = e_v(fhe[i]->edge());
		}
		m_mesh2->create_face(v, ++fid);

		// create small triangles in three corners
		for (int i = 0; i < 3; i++){
			v[0] = v_v(fhe[i]->source());
			v[1] = e_v(fhe[i]->edge());
			v[2] = e_v(fhe[(i + 2 ) % 3]->edge());
			m_mesh2->create_face(v, ++fid);
		}
	}

	m_mesh2->refine_halfedge_structure(); 
}

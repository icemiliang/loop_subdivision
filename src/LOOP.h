#ifndef _LOOP_H_
#define _LOOP_H_

#include <vector>
#include <list>

#include "Mesh.h"
#include "Iterators.h"


namespace MeshLib {

class LOOP {
public:
	LOOP(Mesh *mesh);
	~LOOP();

	float calculateAlpha(int n);

	void subdivide();

protected:
	Mesh *m_mesh;
	std::vector<Vertex*> m_fix_vertices;
};

}

#endif

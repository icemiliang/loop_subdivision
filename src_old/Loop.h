#ifndef _LOOP_H_
#define _LOOP_H_

#include <vector>
#include <list>

#include "Mesh.h"
#include "Iterators.h"


namespace MeshLib {

class Loop {
public:
	Loop(Mesh *mesh);
	~Loop();

	float calculateAlpha(int n);

protected:
	Mesh *m_mesh;
	std::vector<Vertex*> m_fix_vertices;
};

}

#endif

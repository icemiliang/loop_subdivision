// loop-subdivision
//
// Author   : Mi, Liang (Arizona State University)
// Email    : icemiliang@gmail.com
// Date     : Feb 22nd 2020
// License  : MIT

#ifndef _LOOP_H_
#define _LOOP_H_

#include <vector>
#include <list>

#include "Mesh.h"
#include "Iterators.h"
#include "FormTrait.h"


namespace MeshLib {

class LOOP {
public:
	LOOP(Mesh *mesh1, Mesh *mesh2);
	~LOOP();

	void subdivide();

protected:
	float calculateAlpha(int n);

	Mesh *m_mesh1;
	Mesh *m_mesh2;
};

}

#endif

// loop-subdivision
//
// Author   : Mi, Liang (Arizona State University)
// Email    : icemiliang@gmail.com
// Date     : June 13th 2018

// #include <fstream>
// #include <vector>
// #include <cmath>

#include "Mesh.h"
#include "Iterators.h"
#include "LOOP.h"
#include <iostream>
#include "FormTrait.h"
 
using namespace MeshLib;


int main(int argc, char *argv[]) {
	std::cout << "--> Reading mesh..." << std::endl;
	Mesh mesh;
	mesh.read_obj(argv[1]);

	FormTrait traits(&mesh);

	std::cout << "--> Subdviding mesh..." << std::endl;
	LOOP loop(&mesh);
    loop.subdivide();

	std::cout << "--> Writing mesh..." << std::endl;
	mesh.write_obj(argv[2]);
	return 0;
}

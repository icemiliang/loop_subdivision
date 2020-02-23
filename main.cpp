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
#include "FormTrait.h"
#include "LOOP.h"
#include <iostream>
 
using namespace MeshLib;


int main(int argc, char *argv[]) {
    std::cout << "--> Reading mesh..." << std::endl;
    Mesh mesh1;
    mesh1.read_obj(argv[1]);

    

    Mesh mesh2;

	FormTrait traits(&mesh1);

    std::cout << "--> Subdviding mesh..." << std::endl;
    LOOP loop(&mesh1, &mesh2);
    loop.subdivide();

    std::cout << "--> Writing mesh..." << std::endl;
    mesh2.write_obj(argv[2]);
	return 0;
}

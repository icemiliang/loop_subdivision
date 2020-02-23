// loop-subdivision
//
// Author   : Mi, Liang (Arizona State University)
// Email    : icemiliang@gmail.com
// Date     : Feb 22nd 2020
// License  : MIT

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
    FormTrait traits(&mesh1); // add temporary variables

    std::cout << "--> Subdviding mesh..." << std::endl;
    Mesh mesh2;
    LOOP loop(&mesh1, &mesh2);
    loop.subdivide();

    std::cout << "--> Writing mesh..." << std::endl;
    mesh2.write_obj(argv[2]);
    return 0;
}

// loop-subdivision
//
// Author   : Mi, Liang
// Email    : icemiliang@gmail.com
// Date     : Jul 25th 2021
// License  : MIT

#include <string.h>

#include "Mesh.h"
#include "Iterators.h"
#include "FormTrait.h"
#include "LOOP.h"
#include <iostream>
 
using namespace MeshLib;

int main(int argc, char *argv[]) {

    int k = 1;
    // recursive division
    if (strcmp(argv[1], "-r") == 0) {        
        k = atoi(argv[2]);
    }

    std::cout << "--> Reading mesh..." << std::endl;
    Mesh *oldMesh = new Mesh();
    oldMesh->read_obj(argv[1 + (k > 1)*2]);

    for (int i = 0; i < k; ++i) {
        std::cout << "--> Subdviding mesh..." << std::endl;
        FormTrait traits(oldMesh); // add temporary variables
        Mesh *newMesh = new Mesh();
        LOOP loop(oldMesh, newMesh);
        loop.subdivide();
        
        std::string outname = (std::string)argv[2 + (k > 1)*2];
        if (outname.length() > 4 and outname.substr(outname.length()-4) == ".obj") {
            outname = outname.substr(0, outname.length()-4) + "_" + std::to_string(i+1) + ".obj";
        } else {
            outname = outname + ((k == 1)? ".obj" : outname + "_" + std::to_string(i+1) + ".obj");
        }
        std::cout << "--> Writing mesh to " + outname + "..." << std::endl;
        newMesh->write_obj(outname.c_str());
        *oldMesh = *newMesh;
    }
    
	return 0;
}

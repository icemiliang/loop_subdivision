//TopologyException

#include <iostream>
#include <string.h>

#include "TopologyException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace MeshLib;

TopologyException::TopologyException()
{
	msg = "failed to satisfy the manifold constraints";
}
TopologyException::TopologyException(const char *strg)
{
	msg = strg;
}

TopologyException::~TopologyException(){}


void
TopologyException::what()
{
	std::cout << msg << std::endl;
}

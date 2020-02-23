#include "Loop.h"
#include <assert.h>
#include <math.h>
#include <float.h>
#include <iostream>
#include <sstream>


using namespace MeshLib;

Loop::Loop(Mesh * mesh) {
	m_mesh = mesh;
}

Loop::~Loop(){}


float Loop::calculateAlpha(int n){
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
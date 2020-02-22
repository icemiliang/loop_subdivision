cmake_minimum_required(VERSION 3.1)
project(LSCM)
set(CMAKE_CXX_STANDARD 11)

include_directories(src)

set(SOURCES src/Edge.cpp src/Face.cpp src/FException.cpp src/HalfEdge.cpp src/OBJFileReader.cpp src/Parser.cpp src/Point.cpp src/Solid.cpp src/SolidDelegate.cpp src/StringTokenizer.cpp src/TopologyException.cpp src/Trait.cpp src/Vertex.cpp)

add_executable(main main.cpp ${SOURCES})

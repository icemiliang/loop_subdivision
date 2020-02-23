cmake_minimum_required(VERSION 3.1)
project(LSCM)
set(CMAKE_CXX_STANDARD 11)

include_directories(src)

set(SOURCES src/Edge.cpp src/Face.cpp src/FormTrait.cpp src/LOOP.cpp
            src/HalfEdge.cpp src/Mesh.cpp src/Vertex.cpp)

add_executable(main main.cpp ${SOURCES})

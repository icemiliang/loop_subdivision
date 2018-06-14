# loop-subdivision
#
# Author   : Mi, Liang (Arizona State University)
# Email    : icemiliang@gmail.com
# Date     : June 13th 2018

# Load the configuration file
include ../config.mk

# List of the source files
objs = Edge.o Face.o FException.o HalfEdge.o OBJFileReader.o Parser.o Point.o Solid.o \
       SolidDelegate.o StringTokenizer.o TopologyException.o Trait.o Vertex.o 
src=$(patsubst %.o,%.cpp,$(objs))

# Makefile rules
all: $(objs) libmesh++.a

depend:
	$(CXX) $(E_INC) -MM $(src) >Makefile.dep

include Makefile.dep

libmesh++.a: $(objs)
	rm -f libmesh++.a
	ar rs libmesh++.a $^

%.o: %.cpp
	$(CXX) $(CFLAGS) $(E_INC) -c $<


clean:
	rm -f $(objs)
	rm -f libmesh++.a

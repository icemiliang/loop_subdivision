# loop-subdivision makefile
#
# Author   : Mi, Liang (Arizona State University)
# Email    : icemiliang@gmail.com
# Date     : June 13th 2018

# Tell make that these are phony targets
.PHONY: all clean

include config.mk

all: objs subdiv

objs:
	$(MAKE) -C src

subdiv: subdiv.cpp
	$(CXX) $(CFLAGS) $(E_INC) $(E_LIB) -o subdiv subdiv.cpp -lmesh++

clean:
	$(MAKE) -C src clean
	rm -f subdiv

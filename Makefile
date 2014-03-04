CC?=g++
CFLAGS=-c -Wall -std=gnu++0x -fPIC
LDFLAGS=
LIBFLAGS=-shared
LIBSOURCES=caller.cpp metaclass.cpp metaobject.cpp
TSTSOURCES=main.cpp
LIBOBJECTS=$(LIBSOURCES:.cpp=.o)
TSTOBJECTS=$(TSTSOURCES:.cpp=.o)
TSTLIBS=-lstdc++
LIB=libmeta.so
TST=meta-test
INSTALL_PATH?=/usr/local
INSTALL_LIBS_DIR=$(INSTALL_PATH)/lib
INSTALL_HEADERS_DIR=$(INSTALL_PATH)/include/meta

all: $(LIBSOURCES) $(LIB)
	
$(LIB): $(LIBOBJECTS) 
	$(CC) $(LDFLAGS) $(LIBFLAGS) $(LIBOBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
tests: $(LIBSOURCES) $(TSTSOURCES) $(TST)
	
$(TST): $(LIBOBJECTS) $(TSTOBJECTS) 
	$(CC) $(LDFLAGS) $(LIBOBJECTS) $(TSTOBJECTS) $(TSTLIBS) -o $@
	
install: all $(INSTALL_HEADERS_DIR)
	cp $(LIB) $(INSTALL_LIBS_DIR)
	cp *.hpp $(INSTALL_HEADERS_DIR)
	
$(INSTALL_HEADERS_DIR):
	mkdir $(INSTALL_HEADERS_DIR)
	
clean:
	rm -f $(LIB) $(TST) *.o

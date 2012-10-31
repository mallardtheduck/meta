CC=g++
CFLAGS=-c -Wall -std=gnu++0x
LDFLAGS=
LIBSOURCES=caller.cpp metaclass.cpp metaobject.cpp
TSTSOURCES=main.cpp
LIBOBJECTS=$(LIBSOURCES:.cpp=.o)
TSTOBJECTS=$(TSTSOURCES:.cpp=.o)
LIB=libmeta.a
TST=meta-test
INSTALL_PATH?=/usr/local
INSTALL_LIBS_DIR=$(INSTALL_PATH)/lib
INSTALL_HEADERS_DIR=$(INSTALL_PATH)/include/meta

all: $(LIBSOURCES) $(LIB)
	
$(LIB): $(LIBOBJECTS) 
	ar rcs $@ $^

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
tests: $(LIBSOURCES) $(TSTSOURCES) $(TST)
	
$(TST): $(LIBOBJECTS) $(TSTOBJECTS) 
	$(CC) $(LDFLAGS) $(LIBOBJECTS) $(TSTOBJECTS) -o $@
	
install: all $(INSTALL_HEADERS_DIR)
	cp $(LIB) $(INSTALL_LIBS_DIR)
	cp *.hpp $(INSTALL_HEADERS_DIR)
	
$(INSTALL_HEADERS_DIR):
	mkdir $(INSTALL_HEADERS_DIR)
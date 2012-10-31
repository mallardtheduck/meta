CC=g++
CFLAGS=-c -Wall -std=gnu++0x
LDFLAGS=
LIBSOURCES=caller.cpp metaclass.cpp metaobject.cpp
TSTSOURCES=main.cpp
LIBOBJECTS=$(LIBSOURCES:.cpp=.o)
TSTOBJECTS=$(TSTSOURCES:.cpp=.o)
LIB=libmeta.a
TST=meta-test

all: $(LIBSOURCES) $(LIB)
	
$(LIB): $(LIBOBJECTS) 
	ar rcs $@ $^

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
tests: $(LIBSOURCES) $(TSTSOURCES) $(TST)
	
$(TST): $(LIBOBJECTS) $(TSTOBJECTS) 
	$(CC) $(LDFLAGS) $(LIBOBJECTS) $(TSTOBJECTS) -o $@
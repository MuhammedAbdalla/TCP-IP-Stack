# GLTHREADDIR=gluethread
# GRAPHDIR=graph
# TESTDIR=test


# OBJECTS=obj_glthread obj_graph
# LIBS=lib_glthread lib_graph

# all: objects libs

# objects: $(OBJECTS)
# libs: $(LIBS)
# 	sudo ldconfig

# lib_glthread:
# 	gcc objs/glthread.o -shared -o libs/libglthread.so
# 	sudo cp libs/libglthread.so /usr/lib/

# lib_graph:
# 	gcc objs/graph.o -shared -o libs/libgraph.so
# 	sudo cp libs/libgraph.so /usr/lib/

# obj_glthread:
# 	gcc -c -fPIC $(GLTHREADDIR)/glthread.c -o objs/glthread.o -I.

# obj_graph:
# 	gcc -c -fPIC $(GRAPHDIR)/graph.c -o objs/graph.o -I.

# test_graph: all
# 	sudo ldconfig
# 	gcc -c test/test_graph.c -o objs/test_graph.o -I.
# 	gcc objs/test_graph.o -o exe -Llibs -lglthread -lgraph -I.


CC=gcc
CFLAGS=-g
EXE_FOLDER=run
build: test_glthread.exe test_utils.exe test_graph.exe

OBJS=objs/glthread.o objs/net.o objs/graph.o

## shortcuts
t_graph: test_graph.exe
t_glthread: test_glthread.exe
t_utils: test_utils.exe

## compile with the c src and test files in exe compile step
test_graph.exe: objs/glthread.o objs/net.o objs/graph.o objs/test_graph.o
	$(CC) $(CFLAGS) $^ -o $(EXE_FOLDER)/$@

test_glthread.exe: objs/glthread.o objs/test_glthread.o
	$(CC) $(CFLAGS) $^ -o $(EXE_FOLDER)/$@

test_utils.exe: objs/utils.o objs/test_utils.o
	$(CC) $(CFLAGS) $^ -o $(EXE_FOLDER)/$@

## obj test file compile step
objs/test_graph.o: tests/test_graph.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I.

objs/test_glthread.o: tests/test_glthread.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I.

objs/test_utils.o: tests/test_utils.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I.

## obj src file compile step
objs/glthread.o: gluethread/glthread.c
	$(CC) $(CFLAGS) -c -I gluethread $^ -o $@

objs/graph.o: graph/graph.c
	$(CC) $(CFLAGS) -c -I. $^ -o $@

objs/net.o: net/net.c 
	$(CC) $(CFLAGS) -c -I. $^ -o $@

objs/utils.o: utils/utils.c
	$(CC) $(CFLAGS) -c -I. $^ -o $@

clean:
	rm -f libs/*
	rm -f objs/*
	rm *exe
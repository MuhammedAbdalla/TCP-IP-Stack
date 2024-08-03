CC=gcc
CFLAGS=-g
OBJS_FOLDER=objs
EXE_FOLDER=run


build_tests: all
	$(MAKE) -C tests/ objs
	$(MAKE) -C tests/ exes

all: glthread.o graph.o net.o utils.o

## obj src file compile step
glthread.o: gluethread/glthread.c
	$(CC) $(CFLAGS) -c -I gluethread $^ -o $(OBJS_FOLDER)/$@

graph.o: graph/graph.c
	$(CC) $(CFLAGS) -c -I. $^ -o $(OBJS_FOLDER)/$@

net.o: net/net.c 
	$(CC) $(CFLAGS) -c -I. $^ -o $(OBJS_FOLDER)/$@

utils.o: utils/utils.c
	$(CC) $(CFLAGS) -c -I. $^ -o $(OBJS_FOLDER)/$@


# clean up .o and .exe files
clean:
	rm -f libs/*
	rm -f objs/*
	rm -f run/*
	rm -f *exe
# compile the test src file and src file into exes

TOPDIR=..
OBJS_FOLDER=$(TOPDIR)/objs
EXE_FOLDER=$(TOPDIR)/run

CC=gcc
CFLAGS=-g

.PHONY: objs exes

objs: test_glthread.o test_graph.o test_utils.o
exes: test_glthread.exe test_utils.exe test_graph.exe

## shortcuts
t_graph: test_graph.exe
t_glthread: test_glthread.exe
t_utils: test_utils.exe

## compile with the c src and test files in exe compile step
test_graph.exe: $(OBJS_FOLDER)/glthread.o $(OBJS_FOLDER)/net.o $(OBJS_FOLDER)/graph.o $(OBJS_FOLDER)/test_graph.o
	$(CC) $(CFLAGS) $^ -o $(EXE_FOLDER)/$@

test_glthread.exe: $(OBJS_FOLDER)/glthread.o $(OBJS_FOLDER)/test_glthread.o
	$(CC) $(CFLAGS) $^ -o $(EXE_FOLDER)/$@

test_utils.exe: $(OBJS_FOLDER)/utils.o $(OBJS_FOLDER)/test_utils.o
	$(CC) $(CFLAGS) $^ -o $(EXE_FOLDER)/$@


## obj test file compile step
test_glthread.o: test_glthread.c
	$(CC) $(CFLAGS) -c $^ -o $(OBJS_FOLDER)/$@ -I$(TOPDIR)/.

test_graph.o: test_graph.c
	$(CC) $(CFLAGS) -c $^ -o $(OBJS_FOLDER)/$@ -I$(TOPDIR)/.

test_utils.o: test_utils.c
	$(CC) $(CFLAGS) -c $^ -o $(OBJS_FOLDER)/$@ -I$(TOPDIR)/.


clean:
	rm -f *.o








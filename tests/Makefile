TOPDIR=..
GLTHREADDIR=$(TOPDIR)/gluethread
GRAPHDIR=$(TOPDIR)/graph
TESTDIR=$(TOPDIR)/test

test_graph: print-pwd test_graph.o graph.o
	gcc -o test_graph test_graph.o graph.o

print-pwd:
	@echo "current directory"
	@pwd

test_graph.o: test_graph.c
	gcc -c test_graph.c -I$(TOPDIR)







.PHONY: clean
GENERATES = prog prog-* *.so *.a README
TRASH = *.o *~ o.* *.txt
CFLAGS = -fPIC

all:	prog prog-a prog-so README

prog:	const.o fun.o prog.o

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so:	fun.o const.o
	gcc -shared $^ -o $@

prog-a:	prog.o liboutput_static.a
	gcc -L. $< -loutput_static -o $@

prog-so:	prog.o liboutput.so
	gcc -L. $< -loutput -o $@

README:	prog
	./$< 2> $@

fun.o:	outlib.h

test:	test_no_param test_1_param test_3_param

test_no_param:	prog prog-a prog-so
	./prog > tnp.txt 2>> tnp.txt
	./prog-a > tnp-a.txt 2>> tnp-a.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so > tnp-so.txt 2>> tnp-so.txt
	cmp tnp.txt tnp-a.txt
	cmp tnp.txt tnp-so.txt
	cmp tnp-a.txt tnp-so.txt

test_1_param:	prog prog-a prog-so
	./prog hello > t1p.txt 2>> t1p.txt
	./prog-a hello > t1p-a.txt 2>> t1p-a.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so hello > t1p-so.txt 2>> t1p-so.txt
	cmp t1p.txt t1p-a.txt
	cmp t1p.txt t1p-so.txt
	cmp t1p-a.txt t1p-so.txt

test_3_param:	prog prog-a prog-so
	./prog hello, beautiful world > t3p.txt 2>> t3p.txt
	./prog-a hello, beautiful world > t3p-a.txt 2>> t3p-a.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so hello, beautiful world > t3p-so.txt 2>> t3p-so.txt
	cmp t3p.txt t3p-a.txt
	cmp t3p.txt t3p-so.txt
	cmp t3p-a.txt t3p-so.txt


clean:
	rm -f $(TRASH) $(GENERATES)

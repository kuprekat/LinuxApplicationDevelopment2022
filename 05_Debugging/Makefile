GENERATES = range test?.txt
CFLAGS+= -O0 -g

prog: range

test: prog
	gdb -x test1.gdb --args ./range | grep @@@ > test1.txt
	cmp test1.txt test1_correct.txt
	
	gdb -x test2.gdb --args ./range | grep @@@ > test2.txt
	cmp test2.txt test2_correct.txt

clean:
	rm -rf $(GENERATES)

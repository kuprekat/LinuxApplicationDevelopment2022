GENERATES = move *.so *.txt

move:	move.c
	gcc $< -o $@

my_lib.so:	my_lib.c
	gcc $< -shared -ldl -o $@



test:	move my_lib.so
	cat move.c > infile.txt
	cat move.c > PROTECT_infile.txt
	./test.sh


clean:
	rm -f $(GENERATES)

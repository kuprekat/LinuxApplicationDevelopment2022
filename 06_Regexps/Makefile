GENERATES = esub *.txt

esub:	esub.c
	gcc $< -o $@


test:	esub
	./tests.sh


clean:
	rm -f $(GENERATES)

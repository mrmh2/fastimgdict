CFLAGS=-std=c99

bin/fid: src/fastimgdict.c
	gcc $(CFLAGS) src/fastimgdict.c -o bin/fid -lpng

clean:
	rm -f bin/fid

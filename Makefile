CFLAGS=-O3 -std=c++11

bin/fid: src/fastimgdict.c
	g++ $(CFLAGS) src/fastimgdict.c -o bin/fid -lpng

clean:
	rm -f bin/fid

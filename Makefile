bin/fid: src/fastimgdict.c
	gcc src/fastimgdict.c -o bin/fid -lpng

clean:
	rm -f bin/fid

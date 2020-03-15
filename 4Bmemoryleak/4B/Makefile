prog: main3E.o image.o sink.o source.o PNMreader.o PNMwriter.o filter.o
	g++ -o proj3E main3E.o image.o sink.o source.o PNMreader.o PNMwriter.o filter.o

main3C.o: main3E.C filter.h image.h source.h sink.h PNMreader.h PNMwriter.h
	g++ -c -I. main3E.C

image.o: image.C image.h
	g++ -c -I. image.C

sink.o: sink.h
	g++ -c -I. sink.C

source.o: source.C source.h
	g++ -c -I. source.C

PNMreader.o: PNMreader.C PNMreader.h
	g++ -c -I. PNMreader.C

PNMwriter.o: PNMwriter.C PNMwriter.h
	g++ -c -I. PNMwriter.C

filter.o: filter.C filter.h
	g++ -c -I. filter.C

clean:
	rm *.o proj3E


# g++ main3C.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C

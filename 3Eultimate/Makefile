prog: main3E.o image.o sink.o source.o PNMreader.o PNMwriter.o filter.o
	g++ -o 3Eultimate main3E.o image.o sink.o source.o PNMreader.o PNMwriter.o filter.o

main3C.o: main3E.cpp filter.h image.h source.h sink.h PNMreader.h PNMwriter.h
	g++ -c -I. main3E.cpp

image.o: image.cpp image.h
	g++ -c -I. image.cpp

sink.o: sink.h
	g++ -c -I. sink.cpp

source.o: source.cpp source.h
	g++ -c -I. source.cpp

PNMreader.o: PNMreader.cpp PNMreader.h
	g++ -c -I. PNMreader.cpp

PNMwriter.o: PNMwriter.cpp PNMwriter.h
	g++ -c -I. PNMwriter.cpp

filter.o: filter.cpp filter.h
	g++ -c -I. filter.cpp

clean:
	rm *.o 3Eultimate
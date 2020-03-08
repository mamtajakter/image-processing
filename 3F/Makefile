SRC=main3F.cpp image.cpp sink.cpp source.cpp PNMreader.cpp PNMwriter.cpp filter.cpp logging.cpp
OBJ=$(SRC:.cpp=.o)

prog: $(OBJ)
	g++ $(OBJ) -o 3Eultimate

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o 3Eultimate

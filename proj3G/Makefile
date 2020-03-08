SRC=main3G.cpp image.cpp sink.cpp source.cpp PNMreader.cpp PNMwriter.cpp filter.cpp logging.cpp
OBJ=$(SRC:.cpp=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3G

.cpp.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o proj3G
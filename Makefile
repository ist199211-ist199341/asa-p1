CFLAGS = -std=c++11 -O3 -Wall

all: 
	g++ $(CFLAGS) file.cpp -o file -lm

clean:
	rm -f *.o 

run:
	./file




LIBS =  `pkg-config --libs opencv`
CFLAGS = `pkg-config --cflags opencv`

all: foo.e
foo.e: main.o BlobPipe.o #Pipeline.o
	g++ -g -o foo.e main.o BlobPipe.o $(LIBS) $(CFLAGS)
main.o: main.cpp
	g++ -g -c main.cpp $(LIBS) $(CFLAGS)
BlobPipe.o: BlobPipe.cpp
	g++ -g -c BlobPipe.cpp $(LIBS) $(CFLAGS)
#Pipeline.o: Pipeline.cpp
#	g++ -g -c Pipeline.cpp $(LIBS) $(CFLAGS)	
clean:
	rm *.o *.e

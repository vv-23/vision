LIBS =  `pkg-config --libs opencv`
CFLAGS = `pkg-config --cflags opencv`

all: foo.e
foo.e: main.o CubePipeline.o objectDetect.o
	g++ -g -o foo.e main.o objectDetect.o CubePipeline.o $(LIBS) $(CFLAGS)
main.o: main.cpp
	g++ -g -c main.cpp $(LIBS) $(CFLAGS)
CubePipeline.o: CubePipeline.cpp
	g++ -g -c CubePipeline.cpp $(LIBS) $(CFLAGS)
objectDetect.o: objectDetect.cpp
	g++ -g -c objectDetect.cpp $(LIBS) $(CFLAGS)
clean:
	rm *.o

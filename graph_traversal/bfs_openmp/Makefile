CC=g++-4.9
CFLAGS=-c -pedantic -std=c++11 -g -fopenmp
LDFLAGS=-fopenmp
SOURCES=bfs_openmp.cpp Graph.cpp Vertex.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bfs_openmp

#target: dependencies
#[tab] system command

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I./

run:
	echo "Run"
	export OMP_NUM_THREADS=4
	./$(EXECUTABLE) > $(EXECUTABLE)_output.txt

clean:
	rm *.o $(EXECUTABLE) *_output.txt

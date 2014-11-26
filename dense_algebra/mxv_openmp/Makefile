CC=g++-4.9
CFLAGS=-c -Wall -fopenmp
LDFLAGS=-fopenmp
SOURCES=matvec_openmp.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=$(SOURCES:.cpp=)

#target: dependencies
#[tab] system command

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	echo "Run with 1 thread."
	export OMP_NUM_THREADS=1
	./$(EXECUTABLE) > $(EXECUTABLE)_output.txt
	
	echo "Run with 2 threads."
	export OMP_NUM_THREADS=2
	./$(EXECUTABLE) >> $(EXECUTABLE)_output.txt
	
	echo "Run with 4 threads."
	export OMP_NUM_THREADS=4
	./$(EXECUTABLE) >> $(EXECUTABLE)_output.txt
	
	echo "Run with 8 threads."
	export OMP_NUM_THREADS=8
	./$(EXECUTABLE) >> $(EXECUTABLE)_output.txt

clean:
	rm *.o $(EXECUTABLE) *_output.txt
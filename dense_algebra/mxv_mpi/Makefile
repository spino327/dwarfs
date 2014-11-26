CC=mpic++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=matvec_mpi.cpp
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
	mpirun -np 4 ./$(EXECUTABLE) > $(EXECUTABLE)_output.txt

clean:
	rm *.o $(EXECUTABLE) *_output.txt
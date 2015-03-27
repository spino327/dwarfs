CC=clang++
CFLAGS=-c -pedantic -Wc++11-extensions -std=c++11 -g
LDFLAGS=
SOURCES=dfs_serial.cpp Graph.cpp Vertex.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=dfs_serial

#target: dependencies
#[tab] system command

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I./

run:
	echo "Run"
	./$(EXECUTABLE) > $(EXECUTABLE)_output.txt

clean:
	rm *.o $(EXECUTABLE) *_output.txt
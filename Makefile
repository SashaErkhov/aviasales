CC=g++
CFLAGS=-c -pedantic-errors -g -std=c++17
LDFLAGS=
SOURCES=aviasales.cpp Array.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=aviasales.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

test : test.o Array.o
	$(CC) $(LDFLAGS) Array.o test.o -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	del $(OBJECTS) $(EXECUTABLE) test.o test.exe

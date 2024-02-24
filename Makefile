CC=g++
CFLAGS=-c -pedantic-errors -g -std=c++17
LDFLAGS=
SOURCES=aviasales.cpp Array.cpp DataTime.cpp AviaTickets.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=aviasales.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

test : test.o Array.o
	$(CC) $(LDFLAGS) Array.o test.o -o $@

testDT : testDataTime.o DataTime.o Array.o
	$(CC) $(LDFLAGS) DataTime.o testDataTime.o Array.o -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	del $(OBJECTS) $(EXECUTABLE) test.o test.exe DataTime.o testDataTime.o Array.o testDT.exe

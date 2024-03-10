CC=g++
CFLAGS=-c -pedantic-errors -gdwarf-4 -std=c++17
LDFLAGS=
SOURCES=aviasales.cpp Array.cpp DataTime.cpp AviaTickets.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=aviasales.exe

all: test $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

test:
	Project2 < ../../Project2/input1.txt > out1.txt
	Project2 < ../../Project2/input2.txt > out2.txt
	Project2 < ../../Project2/input3.txt > out3.txt
	Project2 < ../../Project2/input4.txt > out4.txt
	Project2 < ../../Project2/input5.txt > out5.txt
	Project2 < ../../Project2/input6.txt > out6.txt
	echo -------------------------
	Project2 < ../../Project2/input7.txt > out7.txt
	Project2 < ../../Project2/input8.txt > ../../Project2/out8.txt
	Project2 < ../../Project2/input9.txt > ../../Project2/out9.txt
	Project2 < ../../Project2/input10.txt > ../../Project2/out10.txt
	Project2 < ../../Project2/input11.txt > ../../Project2/out11.txt
	Project2 < ../../Project2/input12.txt > ../../Project2/out12.txt
	Project2 < ../../Project2/input13.txt > ../../Project2/out13.txt
	Project2 < ../../Project2/input13.txt > ../../Project2/out14.txt
	Project2 < ../../Project2/input13.txt > ../../Project2/out15.txt
	# Project2 < ../../Project2/input13.txt > ../../Project2/out16.txt


testJust : test.o Array.o
	$(CC) $(LDFLAGS) Array.o test.o -o $@
	testJust

testDT : testDataTime.o DataTime.o Array.o
	$(CC) $(LDFLAGS) DataTime.o testDataTime.o Array.o -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	del $(OBJECTS) $(EXECUTABLE) test.o test.exe DataTime.o testDataTime.o Array.o testDT.exe testJust.exe

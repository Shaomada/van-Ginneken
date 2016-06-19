CC=g++ -std=c++11 -Wall -Wpedantic -Werror
SOURCES=main.C tree.C candidates.C
EXECUTABLE=van_Ginneken.out

all: $(EXECUTABLE)

$(EXECUTABLE):  $(SOURCES) *.H
	$(CC) -o $@ $(SOURCES)

clean:
	rm -f $(EXECUTABLE)
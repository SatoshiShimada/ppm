
CC=g++
CFLAGS=`pkg-config --cflags opencv` -lm
LIBS=`pkg-config --libs opencv`

SRC=main.cpp
EXEFILE=sample

default: $(SRC)
	$(CC) $(SRC) -o $(EXEFILE) $(CFLAGS) $(LIBS)

run: $(EXEFILE)
	./$(EXEFILE)

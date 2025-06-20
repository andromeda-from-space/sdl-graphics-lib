COMPILER = g++
CFLAGS = -Wall -g
LFLAGS = -lSDL2
PROG1 = sdl-test
OBJ1 = sdl-basics

all: $(PROG1)

$(PROG1): $(PROG1).cpp $(OBJ1).o
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(OBJ1).o: $(OBJ1).cpp $(OBJ1).h
	$(COMPILER) $(CFLAGS) -c $<

clean:
	rm -f $(PROG1) *.o *~ \#*
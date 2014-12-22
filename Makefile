CC=g++
GDB=gdb
CFLAGS=-std=c++11 -I/usr/local/include -pipe -Wall -Wextra -pedantic -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wdouble-promotion -Wold-style-cast -g
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLEW -lGLU
SRC=$(notdir $(wildcard src/*.cpp)) $(notdir $(wildcard src/*/*.cpp))
OBJ=$(addprefix obj/,$(notdir $(SRC:.cpp=.o)))
BIN=bin/TheLastWar
RM=/bin/rm
CPPCHECK=/usr/bin/cppcheck

all: TheLastWar
TheLastWar: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o bin/$@

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/*/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJ) core *~

check:
	$(CPPCHECK) --enable=all --std=c++11 --language=c++ -q -rp --suppress=missingIncludeSystem src/
cstart: TheLastWar
	$(BIN)

start:
	$(BIN)

debug:
	$(GDB) $(BIN)
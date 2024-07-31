CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14
LDFLAGS = -lX11

SRC = piece.cpp bishop.cpp chessboard.cpp computer.cpp game.cpp graphicalobserver.cpp \
      human.cpp king.cpp knight.cpp observer.cpp pawn.cpp \
      player.cpp queen.cpp rook.cpp textobserver.cpp window.cpp

HEADERS = piece.h bishop.h chessboard.h computer.h game.h graphicalobserver.h \
          human.h king.h knight.h observer.h pawn.h player.h \
          queen.h rook.h textobserver.h window.h

OBJ = $(SRC:.cpp=.o)

EXEC = chess

all: $(EXEC)

$(EXEC): $(OBJ) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

clean:
	rm -f $(OBJ) $(EXEC) main.o

.PHONY: all clean

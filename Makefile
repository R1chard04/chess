# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++14

# Linker flags
LDFLAGS = -lX11

# Source files
SRC = piece.cpp bishop.cpp chessBoard.cpp computer.cpp game.cpp graphicalobserver.cpp \
      human.cpp king.cpp knight.cpp main.cc observer.cpp pawn.cpp \
      player.cpp queen.cpp rook.cpp textobserver.cpp window.cpp main.cc

# Header files
HEADERS = piece.h bishop.h chessBoard.h computer.h game.h graphicalobserver.h \
          human.h king.h knight.h observer.h pawn.h player.h \
          queen.h rook.h textobserver.h window.h

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable name
EXEC = chess

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean

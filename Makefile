# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=c99

# Raylib library path and linking options
INCLUDES = -I/opt/homebrew/include
LIBS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Source files
SRCS = $(wildcard src/*.c)

# Output executable
TARGET = build/game

# Build rule
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET) $(LIBS)

# Clean rule
clean:
	rm -f $(TARGET)

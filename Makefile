# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

# Executable name
TARGET = compiler.out

# Source files
SRCS = lex.c main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)


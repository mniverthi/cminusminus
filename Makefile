CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

CFLAGS  = -g -Wall

# the build target executable:
TARGET = mangolang

all: $(TARGET)
	$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
rm -rf *.o mangolang

token:
	$(CC) $(CFLAGS) -o token token.cpp

lexer:
	
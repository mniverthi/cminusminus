CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

CFLAGS  = -g -Wall

# the build target executable:
TARGET = mangolang

clean:
	@rm -rf *.o mangolang

token: 
	@$(CC) -c $(CFLAGS) src/token.cpp

lexer:
	@$(CC) -c $(CFLAGS) src/token.cpp src/lexer.cpp
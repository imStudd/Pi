CC = g++
SRC = pi.cpp
INCLUDES = pi.hpp
OBJ = $(SRC:.cpp=.o)
CFLAGS = -pthread -Wall -std=c++17 -O3 -lgmpxx -lgmp

pi:    $(OBJ) $(INCLUDES) 
	$(CC) -o $@ $(OBJ) $(CFLAGS)
	
%.o:	%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	rm *.o

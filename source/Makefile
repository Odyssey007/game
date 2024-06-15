CC     	= g++
FLAGS  	= -g -Wall
LFLAGS 	= -lm -lsfml-graphics -lsfml-window -lsfml-system
OBJS   	= main.o game.o
OUT    	= play_game
INCLUDE = -I../header

#SOURCE = main.cpp game.cpp
#HEADER = game.h

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(FLAGS) -o $(OUT) $(OBJS) $(LFLAGS)

main.o: main.cpp ../header/game.h
	$(CC) $(FLAGS) $(INCLUDE) -c main.cpp

game.o: game.cpp ../header/game.h
	$(CC) $(FLAGS) $(INCLUDE) -c game.cpp

clean:
	rm -f $(OBJS) $(OUT)
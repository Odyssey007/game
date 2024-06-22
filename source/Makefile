CC     	= g++
FLAGS  	= -g -Wall
LFLAGS 	= -lm -lsfml-graphics -lsfml-window -lsfml-system
OBJS   	= main.o game.o player.o enemy.o
OUT    	= play_game
INCLUDE = -I../header
#SOURCE = main.cpp game.cpp player.cpp enemy.cpp
#HEADER = game.h player.h enemy.h

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(FLAGS) -o $(OUT) $(OBJS) $(LFLAGS)

main.o: main.cpp ../header/game.h
	$(CC) $(FLAGS) $(INCLUDE) -c main.cpp

game.o: game.cpp ../header/game.h ../header/player.h 
	$(CC) $(FLAGS) $(INCLUDE) -c game.cpp

player.o: player.cpp ../header/player.h
	$(CC) $(FLAGS) $(INCLUDE) -c player.cpp

enemy.o: enemy.cpp ../header/enemy.h 
	$(CC) $(FLAGS) $(INCLUDE) -c enemy.cpp

clean:
	rm -f $(OBJS) $(OUT)
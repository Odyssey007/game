CC     	= g++
FLAGS  	= -g -Wall
LFLAGS 	= -lm -lsfml-graphics -lsfml-window -lsfml-system
OBJS   	= main.o game.o player.o enemy.o slime.o utility.o deltaTime.o animation.o collision.o ability.o
OUT    	= play_game
INCLUDE = -I../header

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(FLAGS) -o $(OUT) $(OBJS) $(LFLAGS)

%.o: source/%.cpp
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)
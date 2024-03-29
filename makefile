rlU: main.o display.o menu.o engine.o Timer.o Bullet.o Items.o BulletList.o Entity.o Player.o Meelee.o Ranged.o List.o Game.o
	g++ -o rlU main.o display.o menu.o engine.o Timer.o Bullet.o Items.o BulletList.o Entity.o Player.o Meelee.o Ranged.o List.o Game.o -fno-stack-protector -lncurses

main.o: main.cpp include/engine.hpp include/display.hpp include/Game.hpp
	g++ -c main.cpp -fno-stack-protector

display.o: include/display.cpp include/display.hpp
	g++ -c include/display.cpp -fno-stack-protector

engine.o: include/engine.cpp include/engine.hpp 
	g++ -c include/engine.cpp -fno-stack-protector

Timer.o: include/Timer.cpp include/Timer.hpp
	g++ -c include/Timer.cpp -fno-stack-protector

menu.o: include/menu.cpp include/menu.hpp
	g++ -c include/menu.cpp -fno-stack-protector

Bullet.o: include/Bullet.cpp include/Bullet.hpp
	g++ -c include/Bullet.cpp -fno-stack-protector

Items.o: include/Items.cpp include/Items.hpp
	g++ -c include/Items.cpp -fno-stack-protector

BulletList.o: include/BulletList.cpp include/BulletList.hpp
	g++ -c include/BulletList.cpp -fno-stack-protector

Entity.o: include/Entity.cpp include/Entity.hpp 
	g++ -c include/Entity.cpp -fno-stack-protector

Meelee.o: include/Meelee.cpp include/Meelee.hpp 
	g++ -c include/Meelee.cpp -fno-stack-protector

Ranged.o: include/Ranged.cpp include/Ranged.hpp 
	g++ -c include/Ranged.cpp -fno-stack-protector

List.o: include/List.cpp include/List.hpp 
	g++ -c include/List.cpp -fno-stack-protector

Player.o: include/Player.cpp include/Player.hpp 
	g++ -c include/Player.cpp -fno-stack-protector

Game.o: include/Game.cpp include/Game.hpp
	g++ -c include/Game.cpp -fno-stack-protector

CFLAGS = -Wall -g

all: rlU main.o display.o menu.o engine.o Timer.o Bullet.o Items.o BulletList.o Entity.o Player.o Meelee.o Ranged.o List.o Game.o -lncurses

valgrind:
	valgrind ./rlU

clean:
	rm *.o
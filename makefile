test: main.o display.o engine.o Entity.o Player.o Meelee.o Ranged.o Items.o List.o
	g++ -o test main.o display.o engine.o Entity.o Player.o Meelee.o Ranged.o Items.o List.o -lncurses

main.o: main.cpp include/engine.hpp include/display.hpp
	g++ -c main.cpp -fno-stack-protector

display.o: include/display.cpp include/display.hpp
	g++ -c include/display.cpp -fno-stack-protector

engine.o: include/engine.cpp include/engine.hpp 
	g++ -c include/engine.cpp -fno-stack-protector

Entity.o: include/Entity.cpp include/Entity.hpp 
	g++ -c include/Entity.cpp -fno-stack-protector

Player.o: include/Player.cpp include/Player.hpp 
	g++ -c include/Player.cpp -fno-stack-protector

Meelee.o: include/Meelee.cpp include/Meelee.hpp 
	g++ -c include/Meelee.cpp -fno-stack-protector

Ranged.o: include/Ranged.cpp include/Ranged.hpp 
	g++ -c include/Ranged.cpp -fno-stack-protector

Items.o: include/Items.cpp include/Items.hpp 
	g++ -c include/Items.cpp -fno-stack-protector

List.o: include/List.cpp include/List.hpp 
	g++ -c include/List.cpp -fno-stack-protector

clean:
	rm *.o a.out log.txt
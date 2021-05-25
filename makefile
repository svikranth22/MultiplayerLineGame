physics-app: main.o
	g++ main.o -o hex-game -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp -o main.o

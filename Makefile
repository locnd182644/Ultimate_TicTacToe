
game: extend.o graphics.o tic_tac_toe.o ultimate_tic_tac_toe.o main.o
	g++ *.o -o game

extend.o: extend.cpp
	g++ -c extend.cpp
	
graphics.o: graphics.cpp
	g++ -c graphics.cpp

tic_tac_toe.o: tic_tac_toe.cpp
	g++ -c tic_tac_toe.cpp

ultimate_tic_tac_toe.o: ultimate_tic_tac_toe.cpp
	g++ -c ultimate_tic_tac_toe.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o

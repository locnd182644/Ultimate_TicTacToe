game: mode.o handle.o graphics.o tic_tac_toe.o ultimate_tic_tac_toe.o player_infor.o main.o 
	g++ *.o -o game

mode.o: mode.cpp
	g++ -c mode.cpp

handle.o: handle.cpp
	g++ -c handle.cpp
	
graphics.o: graphics.cpp
	g++ -c graphics.cpp

tic_tac_toe.o: tic_tac_toe.cpp
	g++ -c tic_tac_toe.cpp

ultimate_tic_tac_toe.o: ultimate_tic_tac_toe.cpp
	g++ -c ultimate_tic_tac_toe.cpp

main.o: main.cpp
	g++ -c main.cpp

player_infor.o: player_infor.cpp
	g++ -c player_infor.cpp

clean:
	rm *.o
	rm game

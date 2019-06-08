This is a program trained for playing tic tac toe, trained by playing against itself trying different things at different states of the game and recording the data for each of them.
The program has a state table that records how many times the program won by taking a particular move. It has been trained over 100000 iterations.
This program was written with no knowledge of AI, it's just smart programming written for entertainment. 
For design related things see doc.txt

For training

g++ trainer.cpp game.cpp -o train
./train


For playing against program:

g++ play.cpp game.cpp play
./play

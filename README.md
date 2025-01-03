// this is how to play the game
g++ -O3 pvp.cpp -o playAI; 
./playAI 


// this will create the book and solve the game
g++ -Ofast n.cpp -o create_book; ./create_book



Looking at this: https://pcarrier.com/teeko/archives/text/


code it in go with Teeko.go or Teeko.c (using mask and current_positon isntead of black and red)
have return arrays

then have generate_book.c or solve.c
this generates the book file and also have postions encoding not only for board of 8 pieces but for 7 6 and so on
do this by 8 pieces is 1 to 75 million 7 pices is 75 million to whatever it is and so on 
This would be generated using negamax
https://pcarrier.com/teeko/archives/text/teeko-analysis-gls.foo.html

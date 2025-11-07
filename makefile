bathroom: bathroom.o
	g++ bathroom.o -o bathroom -pthread

bathroom.o: bathroom.cpp
	g++ -c bathroom.cpp -pthread
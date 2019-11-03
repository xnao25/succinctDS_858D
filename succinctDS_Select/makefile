SuccinctSelect: main.o bit_vector.o rank_support.o select_support.o
	g++ -g -o SuccinctSelect main.o bit_vector.o rank_support.o select_support.o  --std=c++11
main.o: main.cpp
	g++ -g -c main.cpp --std=c++11

select_support.o: select_support.cpp select_support.h
	g++ -g -c select_support.cpp --std=c++11

rank_support.o: rank_support.cpp rank_support.h
	g++ -g -c rank_support.cpp --std=c++11

bit_vector.o: bit_vector.cpp bit_vector.h
	g++ -g -c bit_vector.cpp --std=c++11

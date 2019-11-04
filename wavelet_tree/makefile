WVLTREE: main.o bit_vector.o rank_support.o select_support.o wavelet_tree.o
	g++ -g -o WVLTREE main.o bit_vector.o rank_support.o select_support.o wavelet_tree.o --std=c++11
main.o: main.cpp
	g++ -g -c main.cpp --std=c++11
wavelet_tree.o: wavelet_tree.cpp wavelet_tree.h
	g++ -g -c wavelet_tree.cpp --std=c++11

select_support.o: select_support.cpp select_support.h
	g++ -g -c select_support.cpp --std=c++11

rank_support.o: rank_support.cpp rank_support.h
	g++ -g -c rank_support.cpp --std=c++11

bit_vector.o: bit_vector.cpp bit_vector.h
	g++ -g -c bit_vector.cpp --std=c++11

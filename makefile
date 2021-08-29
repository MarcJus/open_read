all: prog

prog: main.cpp read_write.cpp
	g++ main.cpp read_write.cpp -o prog
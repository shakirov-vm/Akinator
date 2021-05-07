compile:
	g++ main.cpp Tree.cpp Game.cpp -o main -Wall
run:
	./main
graph:
	dot -v -Tpng –o graph.png graph.dot
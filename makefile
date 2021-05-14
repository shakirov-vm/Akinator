compile:
	g++ main.cpp Tree.cpp Game.cpp GraphDump.cpp -o main -Wall
run:
	./main
graph:
	dot -v -Tpng -oPNG.png graph.dot

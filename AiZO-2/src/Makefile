CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

COMMON_SRCS = \
	./Graph/Graph.cpp \
	./FordFulkerson/FordFulkerson.cpp \
	./Dijkstra/Dijkstra.cpp \
	./BellmanFord/BellmanFord.cpp \
	./Kruskal/Kruskal.cpp \
	./Prim/Prim.cpp \
	./Timer/Timer.cpp \
	./Queue/Queue.cpp \
	./MinHeap/MinHeap.cpp \
	./Stack/Stack.cpp

all: main tests

main: main.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o main

tests: Tests.cpp $(COMMON_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o tests

clean:
	rm -f main tests

run-main: main
	./main

run-tests: tests
	./tests

.PHONY: all clean run-main run-tests

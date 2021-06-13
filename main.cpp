#include <iostream>
#include <cstdio>
#include "BFS.h"
#include "File.h"
#include "Graph.h"


int main () {

    File file("graph.txt");
    Graph graph(file);
    BFS bfs(graph, file);
    bfs.PrintPath();

    std::getchar();

}

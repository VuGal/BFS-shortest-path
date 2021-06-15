
#include "BFS.h"


// CONSTRUCTOR/DESTRUCTOR

BFS::BFS(Graph graph, File file) {

    PrepareData(graph, file);
    ExecuteAlgorithm();

}

BFS::~BFS() {}


// PUBLIC METHODS

// prints number of walls to be destroyed, starting vertex and found path
void BFS::PrintPath() {

    if (result == Result::pathNotFound) {
        std::cout << "Sciezka pomiedzy wierzcholkiem poczatkowym a koncowym nie istnieje!\n";
        throw -1;
    }

    std::cout << "Aby dostac sie do punktu dowodzenia nalezy zburzyc " << distanceList[destinationVertex] << " scian.\n\n";

    // prints the real starting vertex (the last one is pseudo starting vertex so it needs to print the one before)
    std::cout << "Nalezy rozpoczac od wierzcholka " << foundPath[foundPath.size()-2] << ".\n\n";

    std::cout << "Odnaleziona trasa:\n";

    // foundPath needs to be printed in reverse, because of the way the vertices were added to this vector in BFS::ExecuteAlgorithm();
    // it starts from foundPath.rbegin()+1 to avoid printing pseudo starting vertex
    for (std::vector<int>::reverse_iterator it = foundPath.rbegin()+1; it != foundPath.rend()-1; ++it) {
        std::cout << *it << " -> ";
    }
    std::cout << foundPath[0] << "\n\n";

}


// PRIVATE METHODS

// initializes needed variables and performs checks
void BFS::PrepareData(Graph graph, File file) {

    adjacencyList = graph.getAdjacencyList();
    std::vector<int> startingVertices = graph.getStartingVertices();

    /*
        adds pseudo starting vertex to adjacency list
        (it's connected to all starting vertices and
         needed to find the optimal starting vertex)
    */
    adjacencyList[pseudoStartingVertex] = startingVertices;


    std::string destinationVertexString = file.GetFileLines()[1];

    if (destinationVertexString.find(' ') != std::string::npos) {
        result = Result::verticesError;
        std::cout << "Podano wiecej niz jeden wierzcholek koncowy!\n";
        throw -1;
    }

    destinationVertex = std::stoi(destinationVertexString);

    if (adjacencyList.count(destinationVertex) > 0) {
        result = Result::success;
    }
    else {
        std::cout << "Podany wierzcholek koncowy nie nalezy do grafu!\n";
    }


    // initializes all vertices data to defaults
    for (auto & [vertex, neighbors] : adjacencyList) {
        predecessorList[vertex] = -1;
        distanceList[vertex] = INT_MAX;
        isVisitedList[vertex] = 0;
    }

}

/*
    performs the modified BFS algorithm
    (creates a tree with BFS, but saves their predecessors
    and distance from the starting vertex)
*/
void BFS::ExecuteAlgorithm() {


    // initializes pseudo starting vertex
    distanceList[pseudoStartingVertex] = -1;
    isVisitedList[pseudoStartingVertex] = 1;
    toBeCheckedList.push_back(pseudoStartingVertex);


    /*
       modified BFS (increments distance with every hop;
       starting vertices have distance equal to 0 and
       pseudo starting vertex has distance equal to -1)
    */
    int currentVertex {};
    while (!toBeCheckedList.empty()) {

        currentVertex = toBeCheckedList.front();
        toBeCheckedList.pop_front();

        for (auto const &neighbor : adjacencyList[currentVertex]) {

            if (isVisitedList[neighbor] == 0) {

                isVisitedList[neighbor] = 1;
                distanceList[neighbor] = distanceList[currentVertex] + 1;
                predecessorList[neighbor] = currentVertex;
                toBeCheckedList.push_back(neighbor);

                if (neighbor == destinationVertex) {

                    result = Result::success;

                    int currentPosition {destinationVertex};
                    while (currentPosition != -1) {
                        foundPath.push_back(currentPosition);
                        currentPosition = predecessorList[currentPosition];
                    }

                    return;
                }

            }

        }

    }

    result = Result::pathNotFound;
    return;
}


#include "BFS.h"


BFS::BFS(Graph graph, File file) {

    PrepareData(graph, file);
    ExecuteAlgorithm();

}

BFS::~BFS() {}


void BFS::PrintPath() {

    if (result == Result::pathNotFound) {
        std::cout << "Sciezka pomiedzy wierzcholkiem poczatkowym a koncowym nie istnieje!\n";
        return;
    }

    std::cout << "Aby dostac sie do punktu dowodzenia nalezy zburzyc " << distanceList[destinationVertex] << " scian.\n\n";

    std::cout << "Odnaleziona trasa:\n";

    for (std::vector<int>::reverse_iterator it = foundPath.rbegin(); it != foundPath.rend()-1; ++it) {
        std::cout << *it << " -> ";
    }
    std::cout << foundPath[0] << "\n\n";

}

void BFS::PrepareData(Graph graph, File file) {

    adjacencyList = graph.getAdjacencyList();

    std::string startingVertexString = file.GetFileLines()[1];
    std::vector<int> startingVertices = graph.getStartingVertices();

    if (startingVertexString.find(' ') != std::string::npos) {
        result = Result::verticesError;
        std::cout << "Podano wiecej niz jeden wierzcholek startowy!\n";
        return;
    }

   startingVertex = std::stoi(startingVertexString);

    if (std::find(startingVertices.begin(), startingVertices.end(), startingVertex) != startingVertices.end()) {
        result = Result::success;
    }
    else {
        std::cout << "Podany wierzcholek startowy nie nalezy do zbioru S!\n";
    }


    std::string destinationVertexString = file.GetFileLines()[2];

    if (destinationVertexString.find(' ') != std::string::npos) {
        result = Result::verticesError;
        std::cout << "Podano wiecej niz jeden wierzcholek koncowy!\n";
        return;
    }

    destinationVertex = std::stoi(destinationVertexString);

    if (adjacencyList.count(destinationVertex) > 0) {
        result = Result::success;
    }
    else {
        std::cout << "Podany wierzcholek koncowy nie nalezy do grafu!\n";
    }

    for (auto & [vertex, neighbors] : adjacencyList) {
        predecessorList[vertex] = -1;
        distanceList[vertex] = INT_MAX;
        isVisitedList[vertex] = 0;
    }

}

void BFS::ExecuteAlgorithm() {

    distanceList[startingVertex] = 0;
    isVisitedList[startingVertex] = 1;
    toBeCheckedList.push_back(startingVertex);


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

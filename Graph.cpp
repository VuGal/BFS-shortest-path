
#include "Graph.h"


// CONSTRUCTOR/DESTRUCTOR

Graph::Graph(File file) {

    std::vector<std::string> fileLines = file.GetFileLines();

    for (size_t vertexData=2; vertexData < fileLines.size(); ++vertexData) {
        AddVertex(fileLines[vertexData]);
    }

    SetStartingVertices(fileLines[0]);

    CheckAdjacencyListCorrectness();

}

Graph::~Graph() {}


// PUBLIC METHODS

// getter for adjacency list which is vertices-neighbors map
std::map<int, std::vector<int>> Graph::getAdjacencyList() const {

    return adjacencyList;

}

// getter for starting vertices
std::vector<int> Graph::getStartingVertices() const {

    return startingVertices;

}


// PRIVATE METHODS

/*
    takes the file line containing the vertex info as a parameter
    and parses it (adds it to adjacencyList)
*/
void Graph::AddVertex(std::string vertexData) {

    std::vector<int> adjacentVertices {};

    std::istringstream iss(vertexData);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>{}};

    int vertexNumber = stoi(tokens[0]);

    for (size_t tokenNum = 1; tokenNum < tokens.size(); ++tokenNum) {
        adjacentVertices.push_back(stoi(tokens[tokenNum]));
    }

    adjacencyList[vertexNumber] = adjacentVertices;

}

/*
    takes the file line containing the starting vertices as a parameter
    and parses it (checks if all vertices belong to the graph, then adds
    the vertices to startingVertices)
*/
void Graph::SetStartingVertices(std::string startingVerticesLine) {

    std::istringstream iss(startingVerticesLine);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>{}};

    int tempToken;
    for (auto const &token : tokens) {
        tempToken = std::stoi(token);

        if (adjacencyList.count(tempToken) > 0) {
            startingVertices.push_back(tempToken);
        }
        else {
            std::cout << "Co najmniej jeden wierzcholek ze zbioru S nie nalezy do grafu!\n";
            throw -1;
        }
    }

}

// checks if all neighbors belong to the graph
void Graph::CheckAdjacencyListCorrectness() {

    /*
        traverses the adjacencyList only once while saving keys and values to sets,
        then checks if values (neighbors) are a subset of keys (graph vertices)
    */
    std::set<int> keys {};
    std::set<int> values {};

    for (auto const& [vertex, neighbors] : adjacencyList) {

        keys.insert(vertex);

        for (auto const &neighbor : neighbors) {
            values.insert(neighbor);
        }

    }

    if (!std::includes(keys.begin(), keys.end(), values.begin(), values.end())) {
        std::cout << "Przynajmniej jeden ze zdefiniowanych sasiadow nie nalezy do grafu!\n";
        throw -1;
    }

}

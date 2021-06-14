#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include "File.h"


class Graph {

    public:
        Graph(File file);
        virtual ~Graph();

        std::map<int, std::vector<int>> getAdjacencyList() const;
        std::vector<int> getStartingVertices() const;

    private:
        std::map<int, std::vector<int>> adjacencyList {};
        std::vector<int> startingVertices {};

        void AddVertex(std::string vertexData);
        void SetStartingVertices(std::string startingVerticesLine);
        void CheckAdjacencyListCorrectness();

};

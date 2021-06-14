#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include "File.h"
#include "Graph.h"


class BFS {

    public:
        BFS(Graph graph, File file);
        virtual ~BFS();

        void PrintPath();

    private:
        enum class Result { verticesError, pathNotFound, success };
        Result result {};
        int pseudoStartingVertex { -100 };
        int destinationVertex {};
        std::map<int, std::vector<int>> adjacencyList {};
        std::map<int, int> predecessorList {};
        std::map<int, int> distanceList {};
        std::map<int, bool> isVisitedList {};
        std::list<int> toBeCheckedList {};
        std::vector<int> foundPath {};

        void PrepareData(Graph graph, File file);
        void ExecuteAlgorithm();


};

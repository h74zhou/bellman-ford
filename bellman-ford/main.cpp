//
//  main.cpp
//  bellman-ford
//
//  Created by Herun Zhou on 2019-04-04.
//  Copyright © 2019 Herun Zhou. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int maxInt = INT_MAX;

struct Edge {
    int startVertex, endVertex, weight;
};

struct Graph {
    int numVertices, numEdges;
    vector<Edge> arrayOfEdges;
};

void bellman(Graph directedGraph, int startVertex, int arraySize) {
    // create the current/previous distance arrays and set base cases (infinity and 0) accordingly
    vector<int> currDistArray(arraySize); // space 2 * n = 2n
    vector<int> prevDistArray(arraySize);
    int numGraphVertices = directedGraph.numVertices;
    int numGraphEdges = directedGraph.numEdges;
    
    for (int k = 0; k < numGraphVertices; ++k) {
        currDistArray[k] = maxInt;
        prevDistArray[k] = 0;
    }
    
    currDistArray[startVertex] = 0; // set the source node
    
    // begin bellmanFord (Semigh Slides, Winter 2019)
    for (int i = 0; i < numGraphVertices - 1; ++i) {
        // for v in V
        for (int j = 0; j < numGraphEdges; ++j) {
            int tempU = directedGraph.arrayOfEdges[j].startVertex;
            int tempV = directedGraph.arrayOfEdges[j].endVertex;
            int tempWeight = directedGraph.arrayOfEdges[j].weight;
            
            // relax the edges
            if ((currDistArray[tempV] > currDistArray[tempU] + tempWeight) && (currDistArray[tempU] != maxInt)) {
                currDistArray[tempV] = currDistArray[tempU] + tempWeight;
                prevDistArray[tempV] = tempU;
            }
        }
    }
    
    // detect negative weight cycle
    for (int l = 0; l < numGraphEdges; ++l) {
        int tempU = directedGraph.arrayOfEdges[l].startVertex;
        int tempV = directedGraph.arrayOfEdges[l].endVertex;
        int tempWeight = directedGraph.arrayOfEdges[l].weight;
        if ((currDistArray[tempV] > currDistArray[tempU] + tempWeight) && (currDistArray[tempU] != maxInt)) {
            cout << "NEGATIVE WEIGHT CYCLE" << endl;
            return;
        }
    }
    
    // If no negative weight cycle was found, we can just print out the distances
    for (int r = 0; r < numGraphVertices; ++r) {
        cout << r << " " << currDistArray[r];
        if (r + 1 < numGraphEdges) {
            cout << endl;
        }
    }
}

int main() {
    // Declare initial variables and read Input
    Graph directedGraph;
    int numNodes, numEdges, sourceNode, nodeU, nodeV, edgeWeight;
    cin >> numNodes >> numEdges >> sourceNode;
    
    // Construct the Graph
    directedGraph.numVertices = numNodes;
    directedGraph.numEdges = numEdges;
    for (int i = 0; i < numEdges; ++i) {
        cin >> nodeU >> nodeV >> edgeWeight;
        Edge newEdge;
        newEdge.startVertex = nodeU;
        newEdge.endVertex = nodeV;
        newEdge.weight = edgeWeight;
        directedGraph.arrayOfEdges.push_back(newEdge);
    }
    bellman(directedGraph, sourceNode, directedGraph.numVertices);
    return 0;
}

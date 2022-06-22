#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdlib.h>
#include <vector>
#include <stack>
#include <list>
#include <time.h>
#include <cmath>
#include <iostream>
#include <assert.h>

#include "Constants.hpp"

struct Coord {
    float x, y, z;

    Coord()
    {
        x = float((rand() % MAPSIZEX) - abs(MAPMINX));
        y = float((rand() % MAPSIZEY) - abs(MAPMINY));
        z = float((rand() % MAPSIZEZ));
    }

    Coord(float x_new, float y_new, float z_new)
    {
        x = x_new;
        y = y_new;
        z = z_new;
    }

    void printCoord() {
        using namespace std;
        cout << "Coord (X,Y,Z) = (" << x << "," << y << "," << z << ")\n" << endl;
    }
};

struct Node {
    int node_number;
    float weight;
    bool visited;

    Coord* coord;
    Coord* cell_coord;
    Node* parent;

    std::vector<Node*> connectedNodes;  //previously node_list

    Node() // Base Constructor
    {
        node_number = 0;
        // Temp random coord

        coord = new Coord();
        weight = 0; // Temp value
        visited = false;
        parent = NULL;

        cell_coord = NULL;
    }

    Node(int node_num, Coord* new_coord) // Constructor for every other new point
    {
        node_number = node_num;
        weight = 0; // Temp value
        coord = new_coord;
        visited = false;
        parent = NULL;

        cell_coord = NULL;
    }

    ~Node()
    {
        delete coord;
        delete cell_coord;
        parent = NULL;
    }

    void printNode() {
        using namespace std;
        cout << "Node: " << node_number << endl;
        cout << "Coord(X,Y,Z) = (" << coord->x << "," << coord->y << "," << coord->z << ")\n\n";
        //if(cell_coord != NULL)
            //cout << "Cell (X,Y,Z) = (" << cell_coord->x << "," << cell_coord->y << "," << cell_coord->z << ")\n" << endl;
    }


};

class Graph {
    int num_nodes;
    std::vector <Node*> cells[NUMCELLSX][NUMCELLSY][NUMCELLSZ];
    std::vector <Node*> adj_list;
    std::stack<Node*> path;


public:
    Graph(int total_nodes, Coord* coord);
    ~Graph();

    // Utility Functions

    Coord* stepNode(Coord* coord, Coord* random_coord, float step_size);
    Node* nearestNode(Coord* random_coord);
    float findDistance(Coord* coord_src, Coord* coord_dest);

    std::vector<Node*> nearestNeighbors(Node* new_node, float r);

    // Setter Functions
    void addEdge(Node* node_src, Node* node_dest, float weight);
    void removeEdge(Node* node_src, Node* node_dest);
    void addNode(Node* node);
    void addToGraph(Node* node_src, Node* node_dest);
    void addNodeStack(Node* node);

    // Getter Functions
    //Coord* getCellCoords(Node* node);
    void setPath();

    std::vector<Node*> getAdjList();
    std::stack<Node*> getPath();

    //Debugging Functions
    void printCellPop();
    void printGraph();
    void printPath();
};

#endif

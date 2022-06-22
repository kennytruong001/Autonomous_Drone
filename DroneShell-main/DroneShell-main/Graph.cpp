#include "Graph.hpp"
using namespace std;

// Constructor

Graph::Graph(int total_nodes, Coord* coord)
{
	this->num_nodes = total_nodes + 1;
	adj_list.resize(this->num_nodes);
	//cout << adj_list.size() << endl;
	Node* first_node = new Node(0,coord);
	addNode(first_node);

	//create array of cells
	for(int i=0;i<NUMCELLSX;i++) {
		for(int j=0;j<NUMCELLSY;j++) {
			for(int k=0;k<NUMCELLSZ;k++) {
				//create cell and store in cells[i][j][k]
				std::vector<Node*> newCell;
				cells[i][j][k]=newCell;
	
			}
		}
	}
};

Graph::~Graph() {
	for (auto& iter : adj_list) {
		delete iter;
	}
}

std::vector<Node*> Graph::nearestNeighbors(Node* new_node, float r) {
	Coord* coord = new_node->coord;
	std::vector<Node*> neighbors;
	for(auto& node : adj_list) {
		if (!node) { continue; }
		if (new_node->parent == node) {
			//std::cout << "Dont need to add parent as neighbor" << endl;
			continue;
		}
		if (new_node == node) {
			//std::cout << "Cant be your own neighbor" << endl;
			continue;
		}
		//if distance between node in adj_list and node param < radius
		if(findDistance(coord,node->coord)<=r) {
			neighbors.push_back(node);
		}
	}
	//std::cout << "Neighbors are: ";
	//for (auto& node : neighbors) {
	//	if (!node) { continue; }
	//	std::cout << node->node_number << " ";
	//}
	//std::cout << "\n\n";
	return neighbors;
}

Node* Graph::nearestNode(Coord* random_coord)
{

	//NOTE: Needs to be optimized by using the nearestNeigbors function (using cells)
	Node* nearest_node = adj_list[0];
	for (auto& node : adj_list) {
		if (!node) { continue; }
		if (findDistance(random_coord, nearest_node->coord) > findDistance(random_coord, node->coord))
		{
			nearest_node = node;
		}
	}
	return nearest_node;

}

// Utility Functions

// Creates a new coordinate step size away from the selected Node
Coord* Graph::stepNode(Coord* coord, Coord* random_coord, float step_size) 
{
	//Need to handle case when coord+step_size is greater than random point
	float x_new, y_new, z_new, hypotonouse;
	z_new = ((step_size)*sqrt(2.0f)) / 2.0f;
	hypotonouse = ((step_size)*sqrt(2.0f)) / 2.0f;
	x_new = ((hypotonouse)*sqrt(2.0f)) / 2.0f;
	y_new = ((hypotonouse)*sqrt(2.0f)) / 2.0f;


	// Checks if random coordinate is at a location less than the nearest coordinate
	if (random_coord->x < coord->x) { x_new = -x_new; }
	if (random_coord->y < coord->y) { y_new = -y_new; }
	if (random_coord->z < coord->z) { z_new = -z_new; }

	Coord* newCoord = new Coord(coord->x + x_new, coord->y + y_new, coord->z + z_new);

	return newCoord;
}

float Graph::findDistance(Coord* coord_src, Coord* coord_dest)
{
	float dist_x = pow((coord_dest->x - coord_src->x), 2);
	float dist_y = pow((coord_dest->y - coord_src->y), 2);
	float dist_z = pow((coord_dest->z - coord_src->z), 2);
	
	float total_distance = sqrt((dist_x + dist_y + dist_z));
	/*std::cout << "dx: " << dist_x << " dy: " << dist_y << " dz: " << dist_z << std::endl;
	std::cout << "Total Distance: " << total_distance << std::endl;*/
	return total_distance;
}


// Setter Functions

void Graph::addEdge(Node* node_src, Node* node_dest, float weight)
{
	//update weight
	float total_weight = weight + node_src->weight;
	node_dest->weight = total_weight;
	//std::cout << "Total weight from src: " << total_weight << endl;
	//add node_dest to connectedNodes list of node_src
	adj_list[node_src->node_number]->connectedNodes[node_dest->node_number] = node_dest;
	node_dest->parent = node_src;
	//std::cout << "Parent of " << node_dest->node_number << " is " << node_src->node_number << std::endl;

}

void Graph::removeEdge(Node* node_src, Node* node_dest) {
	assert(node_src);
	assert(node_dest);
	if (node_src && node_dest) {
		adj_list[node_src->node_number]->connectedNodes[node_dest->node_number] = NULL;
		//std::cout << "Removing Edge: " << node_src->node_number << "->" << node_dest->node_number << std::endl;
	}
}

void Graph::addNode(Node* node) {
	adj_list[node->node_number] = node;		//add new node to adj list
	node->connectedNodes.resize(this->num_nodes);
	//cout << node->connectedNodes.size() << endl;
	//get cell coordinates, add cell coords to node and add node to the appropriate cell
	//Coord* cellCoord = getCellCoords(node);
	//node->cell_coord = cellCoord;

	node->printNode();

	// This is crashing us when MAPSIZE >= 1000
	//node->cell_coord->printCoord();
	//cells[(int)cellCoord->x][(int)cellCoord->y][(int)cellCoord->z].push_back(node);
}

void Graph::addToGraph(Node* node_src, Node* node_dest) {
	float cost = findDistance(node_src->coord, node_dest->coord);
	addNode(node_dest);
	addEdge(node_src, node_dest, cost);
}

void Graph::addNodeStack(Node* node) {
	path.push(node);
}

// Getter Functions

//Double check this idk if it works
/*
Coord* Graph::getCellCoords(Node* node) {
	
	float x = (int)node->coord->x / CELLSIZE;
	float y = (int)node->coord->y / CELLSIZE;
	float z = (int)node->coord->z / CELLSIZE;

	Coord* cellCoord = new Coord(x, y, z);

	return cellCoord;
	
}
*/

void Graph::setPath() {
	Node* curr = path.top()->parent;
	while (curr) {
		//std::cout << "Current Node is " << curr->node_number << endl;
		path.push(curr);
		curr = curr->parent;
	}
}

std::stack<Node*> Graph::getPath() {
	return path;
}

std::vector<Node*> Graph::getAdjList() {
	return adj_list;
}

// Debug Functions

void Graph::printGraph()
{
	cout << "Size of Graph vector: " << adj_list.size() << endl;
	cout << "Adjacency List" << endl;
	for (auto& node : adj_list)
	{
		if (!node) { continue; }
		for (auto& nodeChild : node->connectedNodes)
		{
			if (!nodeChild) { continue; }
			cout << "(" << node->node_number << ", " << nodeChild->node_number << ", " << nodeChild->weight << ") " << endl;
		}
	}
}

void Graph::printCellPop() {
	for (int i = 0; i < NUMCELLSX; i++) {
		for (int j = 0; j < NUMCELLSY; j++) {
			for (int k = 0; k < NUMCELLSZ; k++) {
				cout << "cell[" << i << "][" << j << "][" << k << "] population = " << cells[i][j][k].size() << "\n";

			}
		}
	}
}

void Graph::printPath() {
	if (path.empty()) {
		std::cout << "No path found!" << std::endl;
		return;
	}

	std::stack<Node*> temp = path;
	float total_cost = 0;
	std::cout << "Path is: ";
	while (!temp.empty()) {
		Node* current = temp.top();
		std::cout << current->node_number << " ";
		total_cost = current->weight;
		temp.pop();
	}
	std::cout << std::endl;
	std::cout << "Total cost: " << total_cost << std::endl;
}

// End Debug Functions

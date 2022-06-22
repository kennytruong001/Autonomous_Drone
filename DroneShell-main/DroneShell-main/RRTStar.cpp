#include "RRTStar.hpp"


Graph* rrtStar(Coord homeCoord, Coord endCoord) {
	//Initializes obstacles here
	Coord* ful = new Coord(18.12f, -23.37f, 25.34f);
	Coord* fur = new Coord(18.12f, 16.63f, 25.34f);
	Coord* fdl = new Coord(18.12f, -23.37f, -1.02f);
	Coord* fdr = new Coord(18.12f, 16.63f, -1.02f);
	Coord* bul = new Coord(98.12f, -23.37f, 25.34f);
	Coord* bur = new Coord(98.12f, 16.63f, 25.34f);
	Coord* bdl = new Coord(98.12f, -23.37f, -1.02f);
	Coord* bdr = new Coord(98.12f, 16.63f, -1.02f);

	//Coord* ful = new Coord(-41.63f, 16.87f, 14.52f);
	//Coord* fur = new Coord(-41.63f, 36.37f, 14.52f);
	//Coord* fdl = new Coord(-41.63f, 16.87f, -0.77f);
	//Coord* fdr = new Coord(-41.63f, 36.37f, -0.77f);
	//Coord* bul = new Coord(-22.23f, 16.87f, 14.52f);
	//Coord* bur = new Coord(-22.23f, 36.37f, 14.52f);
	//Coord* bdl = new Coord(-22.23f, 16.87f, -0.77f);
	//Coord* bdr = new Coord(-22.23f, 36.37f, -0.77f);

	    /*bul = (3965, 1774, 1574) = -22.23f, 16.87f, 14.52f
		bdl = (3965, 1774, 124) = -22.23f, 16.87f, -0.77f
		fdl = (2025, 1774, 124) = -41.63f, 16.87f, -0.77f
		ful = (2025, 1774, 1574) = -41.63f, 16.87f, 14.52f
		fur = (2025, 3724, 1574) = -41.63f, 36.37f, 14.52f
		fdr = (2025, 3724, 124) = -41.63f, 36.37f, -0.77f
		bdr = (3965, 3724, 124) = -22.23f, 36.37f, -0.77f
		bur = (3965, 3724, 1574) = -22.23f, 36.37f, 14.52f*/

	Obstacles o = Obstacles(MAPMINX, MAPMINY, MAPMINZ, MAPMAXX, MAPMAXY, MAPMAXZ);
	o.addObstacle(ful, fur, fdl, fdr, bul, bur, bdl, bdr);



	// Creating the start of graph
	Coord* startingCoord = new Coord(homeCoord.x, homeCoord.y, homeCoord.z);
	Coord* goalCoord = new Coord(endCoord.x, endCoord.y, endCoord.z);
	Graph* graph = new Graph(NUMNODES, startingCoord);

	int i = 1;
	while (i < NUMNODES) {

		Coord* random_coord = new Coord();	// Random Position
		Node* nearest_node = graph->nearestNode(random_coord); // Nearest Node from the random point

		// STILL NEED TO FINISH CHECKOBSTACLE
		if (o.collisionCheck(nearest_node->coord, random_coord)) { // If obstacle is in between two nodes return true
			std::cout << "collision here!\n";
			//nearest_node->printNode();
			//random_coord->printCoord();
			delete random_coord;
			continue;
		}

		// Creating coordinate and node step size away from the nearest coord
		Coord* step = graph->stepNode(nearest_node->coord, random_coord, STEPSIZE);
		if (graph->findDistance(nearest_node->coord, step) > graph->findDistance(nearest_node->coord, random_coord)) {
			delete step;
			delete random_coord;
			continue;
		}

		Node* new_node = new Node(i, step);
		graph->addToGraph(nearest_node, new_node);
		std::vector<Node*> neighbors = graph->nearestNeighbors(new_node, RADIUS);


		//// FOR RRT*
		for (auto& node_neighbor : neighbors) {
			//std::cout << "Node Neighbor is: " << node_neighbor->node_number << std::endl;
			//node_neighbor->coord->printCoord();
			float cost_new = graph->findDistance(new_node->coord, node_neighbor->coord);
			//std::cout << "New Cost = " << cost_new + node_neighbor->weight << std::endl;
			//std::cout << "Original Cost = " << new_node->weight << std::endl;
			if (cost_new + node_neighbor->weight < new_node->weight) {

				//std::cout << "Optimizing!" << std::endl;
				graph->removeEdge(new_node->parent, new_node);
				graph->addEdge(
					node_neighbor,
					new_node,
					cost_new
				);
			}
			//std::cout << std::endl;
		}

		delete random_coord;

		// Check if node found goal
		float nodeDistanceFromGoal = graph->findDistance(new_node->coord, goalCoord);
		if (nodeDistanceFromGoal < GOALRADIUS) {
			std::cout << "Node that found Goal: " << new_node->node_number << std::endl;
			Node* goal_node = new Node(i + 1, goalCoord);
			graph->addToGraph(new_node, goal_node);
			graph->addNodeStack(goal_node);
			graph->addNodeStack(new_node);
			graph->setPath();
			return graph;
		}
		i++;
	}
	std::cout << "Goal was not found" << std::endl;
	delete graph;
	delete goalCoord;

	// Return NULL if no path found
	return NULL;
}
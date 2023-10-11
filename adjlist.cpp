#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

#include "graph.h"

using namespace std;

//Filename constructor
Graph::Graph(char const * filename){
	ifstream file(filename);                             // open file
   	if (not file) {
        throw std::runtime_error("Cannot open file.");
   	}

   	string line;
   	int num;
   	// get first line of file
   	getline(file, line);
   	stringstream ss(line);
   	ss >> num;
   	if (not ss) {
        throw std::runtime_error("Invalid file format.");
   	}
   	// allocate new node
    head = new adjNode*[num]();
    adjNode* ptr;
    int gate = 0;
    this->N = num;
    // initialize head pointer for all vertices
    for (int i = 0; i < num; ++i)
        head[i] = nullptr;

   	//cout << "N: " << this->N << endl;

   	while (std::getline(file, line)) {
	   	stringstream ss(line);
	   	int start, end, weight;
	   	ss >> start >> end;
	    if (not ss) {
	        throw std::runtime_error("Invalid file format.");
	    }
	    ss >> weight;
	    if (not ss) {
        	weight = 1;
   		}

   		gate = 1;
   		ptr = head[start];
		while(ptr != nullptr){
			if(ptr->val == end){gate = 0;}
			ptr = ptr->next;
		}
		if(gate == 1){
		    adjNode* newNode = getAdjListNode(end, weight, head[start]);
		    head[start] = newNode;
	        if(start != end){newNode = getAdjListNode(start, weight, head[end]);}
	        // point head pointer from end to new node
	        head[end] = newNode;
	    }
	}
	file.close();
}

int ** adjacency_matrix(const char * filename, int * nodenum){

	ifstream file(filename);
   	if (not file) {
        throw std::runtime_error("Cannot open file.");
   	}

   	string line;
   	int start_ver, end_ver;
   	// get first line of file
   	getline(file, line);

   	stringstream ss(line);
   	ss >> *nodenum;
   	if (not ss) {
        throw std::runtime_error("Invalid file format.");
   	}

    int** adj_matrix = matrix(*nodenum, *nodenum);

   	while (std::getline(file, line)) {
	   	stringstream ss(line);
	   	int start, end;
	   	ss >> start >> end;
	    if (not ss) {
	        throw std::runtime_error("Invalid file format.");
	    }
	    adj_matrix[start][end] = 1;
	    adj_matrix[end][start] = 1;
	}
	file.close();

	return adj_matrix;
}

int ** matrix(int rows, int columns){

	int* field = (int*)calloc(rows*columns, sizeof(int));
    int** matrix = (int**)malloc(rows*sizeof(int*));
    for (int i=0; i<rows; ++i)
    {
        matrix[i] = field + i*columns;
    }
    return matrix;
}

void freeMatrix(int** matrix)
{
    free(*matrix);
    free(matrix);
}

int graph_props(Graph* g, int stats){
	int nodenumber = (int)g->N;
	unsigned long edgecount = 0;
	int degree = 0;
	int maxdegree = 0;

	mp_bitcnt_t prec = 1024;
    mpf_set_default_prec (prec);

	mpf_t density, averagedegree, buffer;
	mpf_init(density);
	mpf_init(averagedegree);
	mpf_init(buffer);
	mpf_set_ui(density, 0);
	mpf_set_ui(averagedegree, 0);
	mpf_set_ui(buffer, 0);
	vector<int> nodedegree;

	adjNode* ptr;

	int cycles;
	int loops = 0;

	for(int i=0; i<nodenumber; i++){
		ptr = g->head[i];
		degree = 0;
		while(ptr != nullptr){
			edgecount++;
			degree++;
			if(ptr->val == i){loops=1;}
			ptr = ptr->next;
		}
		if(degree > maxdegree){maxdegree = degree;}
		nodedegree.push_back(degree);
		mpf_add_ui(averagedegree, averagedegree, degree);
	}
	mpf_div_ui(averagedegree, averagedegree, nodenumber);
	edgecount = edgecount/2;
	mpf_set_ui(density, edgecount);
	mpf_set_ui(buffer, nodenumber);
	mpf_mul_ui(buffer, buffer, nodenumber-1);
	mpf_div_ui(buffer, buffer, 2);
	mpf_add_ui(buffer, buffer, nodenumber);
	mpf_div(density, density, buffer);

	cycles = cycle_dfs(g);
	
	if(stats == 1){
		cout << std::fixed << "Nodes: " << nodenumber << ", Edges: " << edgecount << ", avg. Degree: " << averagedegree  << ", max. Degree: " << maxdegree << ", Density: " << density << endl;

		if(cycles == 1){cout << "Contains Cycle(s).\n";}
		else{cout << "No Cycles.\n";}

		if(loops == 1){ cout << "Contains Loop(s).\n";}
		else {cout << "No Loops.\n";}
	}

	return cycles;
}

int cycle_dfs(Graph* g){
	int cycle = 0;
	adjNode* ptr;
	int nodenumber = g->N;

	int visited_nodes[nodenumber];
	for(int i=0; i<nodenumber; i++){
		visited_nodes[i] = 0;
	}

	for(int i=0; i<nodenumber; i++){

		if(visited_nodes[i] == 0){
			visited_nodes[i] = 1;
			ptr = g->head[i];

			while(ptr != nullptr){
				if(visited_nodes[ptr->val] == 0){
					dfs_visit(g, ptr->val, i, visited_nodes, &cycle);
				}
				ptr = ptr->next;
			}
		}
	}
	return cycle;
}

void dfs_visit(Graph* g, int nodeid, int predecessor, int * visited_nodes, int * cycle){

	visited_nodes[nodeid] = 1;
	adjNode* ptr;
	ptr = g->head[nodeid];

	while(ptr != nullptr && *cycle == 0){
		if(visited_nodes[ptr->val] == 0){
			dfs_visit(g, ptr->val, nodeid, visited_nodes, cycle);
		}
		else{
			if(ptr->val != predecessor && ptr->val != nodeid){
				*cycle = 1;
			}
		}
		ptr = ptr->next;
	}
}


int myrand(int range_begin, int range_end){
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(range_begin, range_end);

    return distr(gen);
}

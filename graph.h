#ifndef GRAPH_H
#define GRAPH_H


#include <fstream>
#include <gmpxx.h>
#include <chrono>
#include <vector>

struct adjNode {
	int val, cost;
	adjNode* next;
};

struct graphEdge {
	int start_ver, end_ver, weight;
};

class Graph {
	//insert new edges/nodes into adjacency list
	adjNode* getAdjListNode(int value, int weight, adjNode* head) {
		adjNode* newNode = new adjNode;
        newNode->val = value;
        newNode->cost = weight;
         
        newNode->next = head;   // point new node to current head
        return newNode;
	}
public:
    int N;  // number of nodes in the graph
    adjNode **head;                //adjacency list as array of pointers
    // Constructors
    Graph(char const * filename);
    Graph(graphEdge edges[], int n, int N)  {
        // allocate new node
        head = new adjNode*[N]();
        this->N = N;
        // initialize head pointer for all vertices
        for (int i = 0; i < N; ++i)
            head[i] = nullptr;
        // construct directed graph by adding edges to it
        for (unsigned i = 0; i < n; i++)  {
            int start_ver = edges[i].start_ver;
            int end_ver = edges[i].end_ver;
            int weight = edges[i].weight;
            // insert in the beginning
            adjNode* newNode = getAdjListNode(end_ver, weight, head[start_ver]);
            // point head pointer from start to new node
            head[start_ver] = newNode;
            newNode = getAdjListNode(start_ver, weight, head[end_ver]);
            // point head pointer from end to new node
            head[end_ver] = newNode;
        }
    }
      // Destructor
     ~Graph() {
    for (int i = 0; i < N; i++)
        delete[] head[i];
        delete[] head;
     }
};

void freeMatrix(int** matrix);
int ** matrix (int rows, int columns);
int ** adjacency_matrix(const char * filename, int * nodenum);

int myrand(int range_begin, int range_end);
std::vector<int> intersection(std::vector<int> v1, std::vector<int> v2);
int graph_props(Graph* g, int stats);
int cycle_dfs(Graph* g);
void dfs_visit(Graph* g, int nodeid, int predecessor, int * visited_nodes, int * cycle);


void homhops(Graph* h, Graph* g, int k, ::mpf_t result, int * successful_tries, int * iterations_count, int timer);
int EmbedTree_homhops(Graph* h, Graph* g, std::vector<int> &embedding, int v, int w, int p, ::mpz_t c);

void homhopsplus(Graph* h, Graph* g, int k, ::mpf_t result, int * successful_tries, int * iterations_count, int timer);
int EmbedPattern(Graph* h, Graph* g, std::vector<int> &embedding, int v, int w, ::mpz_t c);

void hops(Graph* h, Graph* g, int k, ::mpf_t result, int * successful_tries, int * iterations_count, int timer);
int EmbedTree_hops(Graph* h, Graph* g, int * embedding, int * visited_nodes, int v, int w, int p, ::mpz_t c, int k);

void sghd(const char * filename_h, const char * filename_g, int k, ::mpf_t result, int * successful_tries, int * iterations_count, int timer);

#endif
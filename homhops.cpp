#include "graph.h"

using namespace std;

void homhops(Graph* h, Graph* g, int k, mpf_t result, int * successful_tries, int * iterations_count, int timer){

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    auto ms_double = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    *successful_tries = 0;
	*iterations_count = 0;
	int nodenumber_h = h->N;
	int nodenumber_g = g->N;

	mp_bitcnt_t prec = 1024;
    mpf_set_default_prec (prec);

	mpf_set_ui(result, 0);
	mpz_t c, result2;
	mpz_init(c);
	mpz_init(result2);
	mpz_set_ui(c, nodenumber_g);
	mpz_set_ui(result2, 0);

	//Pick root in V(H)
	int root = myrand(0, nodenumber_h-1);
	int root_embedding;
	vector<int> embedding(nodenumber_h);

	int timelimit = 0;
	while(timelimit == 0){

		//Reset embedding array
		for(int j=0; j<nodenumber_h; j++){
			embedding[j] = -1;
		}

		//Initial assignment
		root_embedding = myrand(0, nodenumber_g-1);
		embedding[root] = root_embedding;

		EmbedTree_homhops(h, g, embedding, root, root_embedding, -1, c);

		//Add up results
		mpz_add(result2, result2, c);

		if(mpz_cmp_ui(c, 0) != 0){ 
			*successful_tries = *successful_tries+1;
		}
		*iterations_count = *iterations_count+1;
		mpz_set_ui(c, nodenumber_g);

		//Timer
		t2 = high_resolution_clock::now();
        auto ms_double = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
        if ( ms_double.count() >= timer ){
        	timelimit = 1;
        }
	}

	//Calculate Estimate
	mpf_set_z(result, result2);
	mpf_div_ui(result, result, *iterations_count);
}

int EmbedTree_homhops(Graph* h, Graph* g, vector<int> &embedding, int v, int w, int p, mpz_t c){
//EmbedTree_homhops(Pattern H, Graph G, Homomorphism Embedding(vector), int v in V(H), int w = embed(v), int predecessor p = parent(v), mpz_t c (result))

	mp_bitcnt_t prec = 1024;
    mpf_set_default_prec (prec);
	mpz_t c2;
	mpz_init(c2);
	mpz_set_ui(c2, 1);

	vector<int> A;
	vector<int> B;

	//Áll Neighbours of v(except predecessor) in H to A
	adjNode* ptr;
	ptr = h->head[v];
	while(ptr != nullptr){
		if(ptr->val != p){
			A.push_back(ptr->val);
		}
		ptr = ptr->next;
	}

	if ( A.size()>0 ){

		//Áll Neighbours of embed[v] in G to B
		ptr = g->head[w];
		while(ptr != nullptr){
			B.push_back(ptr->val);
			ptr = ptr->next;
		}

		//Draw Assignment for A and calculate number of possible assignments
		if( B.size() > 0 ){
			for(int i=0; i<A.size(); i++){
				embedding[A[i]] = B[myrand(0, B.size()-1)];
			}
			mpz_set_ui(c2, B.size());
			mpz_pow_ui (c2, c2, A.size());
		}
		else {
			mpz_set_ui(c2, 0);
		}
	}
	mpz_mul(c, c, c2);

	//Recursive calls for each member of A
	for(int i=0; i<A.size(); i++){
		if(mpz_cmp_ui(c, 0) == 0){
			return 0;
		}
		EmbedTree_homhops(h, g, embedding, A[i], embedding[A[i]], v, c);
	}

	return 0;
}

#include "graph.h"

using namespace std;

void homhopsplus(Graph* h, Graph* g, int k, mpf_t result, int * successful_tries, int * iterations_count, int timer){

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

		EmbedPattern(h, g, embedding, root, root_embedding, c);

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

int EmbedPattern(Graph* h, Graph* g, vector<int> &embedding, int v, int w, mpz_t c){
//EmbedPattern(Pattern H, Graph G, Homomorphism Embedding(vector), int v in V(H), int w = embed(v), int predecessor p = parent(v), mpz_t c (result))

	mp_bitcnt_t prec = 1024;
    mpf_set_default_prec (prec);
	mpz_t c2;
	mpz_init(c2);
	mpz_set_ui(c2, 1);

	vector<int> A;
	vector<int> B;
	vector<int> S;
	vector<int> R;
	vector<vector<int>> Q;
	
	//Áll Neighbours of v(except already embedded) in H to A
	adjNode* ptr;
	ptr = h->head[v];
	while(ptr != nullptr){
		if(embedding[ptr->val] == -1){
			A.push_back(ptr->val);
		}
		ptr = ptr->next;
	}

	//Find embeddings for all nodes in A successively
	for(int i=0; i<A.size(); i++){
		//All embedded Neighbours of A[i] in H to S
		ptr = h->head[A[i]];
		while(ptr != nullptr){
			if(embedding[ptr->val] != -1){
				S.push_back(ptr->val);
			}
			ptr = ptr->next;
		}

		//All Neigbours of embed[S[j]] in G to Q[j]
		for(int j=0; j<S.size(); j++){

			ptr = g->head[embedding[S[j]]];
			while(ptr != nullptr){
				R.push_back(ptr->val);
				ptr = ptr->next;
			}
			Q.push_back(R);
			R.clear();
		}
		S.clear();

		//Set Intersection S of all Q[i]'s 
		if( Q.size() > 0 ) {
			S = Q[0];
			for(int j=1; j<Q.size(); j++){
				S = intersection(S, Q[j]);
			}
		}		
		Q.clear();

		//Draw assignment for every node in S and calculate number of possible assignments
		if( S.size() > 0 ) {
			embedding[A[i]] = S[myrand(0, S.size()-1)];
			mpz_mul_ui(c2, c2, S.size());
		}
		else {mpz_set_ui(c2, 0);}
		S.clear();
	}
	mpz_mul(c, c, c2);

	//Recursive calls for each member of A with not already embedded neighbours
	for(int i=0; i<A.size(); i++){
		ptr = h->head[A[i]];
		while(ptr != nullptr){
			if(mpz_cmp_ui(c, 0) == 0){
				return 0;
			}
			if(embedding[ptr->val] == -1){
				EmbedPattern(h, g, embedding, A[i], embedding[A[i]], c);
				ptr = nullptr;
			}
			else {
				ptr = ptr->next;
			}
		}
	}

	return 0;
}

vector<int> intersection(vector<int> v1, vector<int> v2){
    vector<int> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));

    return v3;
}
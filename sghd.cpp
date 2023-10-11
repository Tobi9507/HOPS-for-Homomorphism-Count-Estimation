#include "graph.h"

using namespace std;

void sghd(const char * filename_h, const char * filename_g, int k, mpf_t result, int * successful_tries, int * iterations_count, int timer){

	string s = "results/sghd.txt";
    std::ofstream outfile (s);
    int plot_timer = 1;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();
    auto t2 = high_resolution_clock::now();
    auto ms_double = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    *successful_tries = 0;
    *iterations_count = 0;

    int nodenum_h;
 	int ** matrix_h = adjacency_matrix(filename_h, &nodenum_h);
 	int nodenum_g;
 	int ** matrix_g = adjacency_matrix(filename_g, &nodenum_g);

 	mp_bitcnt_t prec = 1024;
    mpf_set_default_prec (prec);

	mpf_set_ui(result, 0);
	mpf_t result_buf;
	mpf_init(result_buf);
	mpf_set_ui(result_buf, 0);

	int homomorphism_check, c;
	int homomorphism_count = 0;
	vector<int> A;
	vector<int> B;
	A.resize(nodenum_h);
	for(int i = 0; i<nodenum_g; i++){
		B.push_back(i);
	}

	int timelimit = 0;
	while(timelimit == 0){

		homomorphism_check = 1;

		//Draw Assignment
		for(int j = 0; j<nodenum_h; j++){
			A[j] = myrand(0, B.size()-1);
		}

		//Check for Homomorphism
		for(int j=0; j<nodenum_h; j++){
			for(int l=0; l<=j; l++){
				if(matrix_h[j][l] == 1){
					if(matrix_g[A[j]][A[l]] == 0){
						homomorphism_check = 0;
						l = j+1;
					}
				}
			}
			if(homomorphism_check == 0){
				j = nodenum_h;
			}
		}

		if(homomorphism_check == 1){
			homomorphism_count++;
			*successful_tries = *successful_tries+1;
		}
		*iterations_count = *iterations_count+1;

		//Timer
		t2 = high_resolution_clock::now();
        auto ms_double = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
        if ( ms_double.count() >= timer ){
        	timelimit = 1;
        }

        if ( ms_double.count() >= plot_timer*1000 ){
			mpf_set_ui(result, homomorphism_count);
			mpf_div_ui(result, result, *iterations_count);
			mpf_set_ui(result_buf, nodenum_g);
			mpf_pow_ui(result_buf, result_buf, nodenum_h);
			mpf_mul(result, result, result_buf);
        	outfile << result << endl;
        	plot_timer++;
        }
	}

	//Calculate Estimated Homomorphism Density
	mpf_set_ui(result, homomorphism_count);
	mpf_div_ui(result, result, *iterations_count);

	//Calculate Estimate Homomorphism Number
	mpf_set_ui(result_buf, nodenum_g);
	mpf_pow_ui(result_buf, result_buf, nodenum_h);
	mpf_mul(result, result, result_buf);

	freeMatrix(matrix_h);
	freeMatrix(matrix_g);

	outfile.close();
}

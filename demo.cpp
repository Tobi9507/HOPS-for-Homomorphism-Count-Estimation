#include <iostream>
#include <fstream>

#include "graph.h"

using namespace std;

int main( int argc, char* argv[] )
{

    //inputargs
    //flags -all -hops -homhops -homhopsplus -sghd
    //flags timer
    //exact solution + relative error on destined input
    //plots

    const char* inputs[1] = {
        "input/SNAP-DATASETS/webkb-wisc.txt",
    };

    const char* patterns[1]={
        //"input/TREEPATTERNS/tree1.txt",
        "input/ARBITRARYPATTERNS/pattern2.txt",
    };

    mp_bitcnt_t prec = 1024;
    mpf_set_default_prec (prec);
    mpf_t result;
    mpf_init(result);
    double result2;
    int result3;

    int iterations = 50000;
    int successful_tries = 0;
    int iteration_count = 0;
    int timer = 2000;
    int time_sec = timer/1000;

    Graph h(patterns[0]);
    Graph g(inputs[0]);
    int cycles_h;

    cout << "Pattern: " << patterns[0] << endl;
    cycles_h = graph_props(&h);
    cout << endl;

    cout << "Inputgraph: " << inputs[0] << endl;
    graph_props(&g);
    cout << endl;

    if(cycles_h == 0){
        homhops(&h, &g, iterations, result, &successful_tries, &iteration_count, timer);
        cout << "(homhops)     Estimate: " << std::fixed << result << " ";
        cout << ", Iterations: " << iteration_count << " ";
        cout << ", Successful Tries: " << successful_tries << " ";
        cout << ", Time[s]: " << time_sec;
        cout << endl;
    }
    else{
        cout << "(homhops)     Pattern is not a tree.\n";
    }

    homhopsplus(&h, &g, iterations, result, &successful_tries, &iteration_count, timer);
    cout << "(homhopsplus) Estimate: " << std::fixed << result << " ";
    cout << ", Iterations: " << iteration_count << " ";
    cout << ", Successful Tries: " << successful_tries << " ";
    cout << ", Time[s]: " << time_sec;
    cout << endl;

    if(cycles_h == 0){
        hops(&h, &g, iterations, result, &successful_tries, &iteration_count, timer);
        cout << "(hops)        Estimate: " << std::fixed << result << " ";
        cout << ", Iterations: " << iteration_count << " ";
        cout << ", Successful Tries: " << successful_tries << " ";
        cout << ", Time[s]: " << time_sec;
        cout << endl;
    }
    else{
        cout << "(homhops)     Pattern is not a tree.\n";
    }

    sghd(patterns[0], inputs[0], iterations, result, &successful_tries, &iteration_count, timer);
    cout << "(sghd)        Estimate: " << std::fixed << result << " ";
    cout << ", Iterations: " << iteration_count << " ";
    cout << ", Successful Tries: " << successful_tries << " ";
    cout << ", Time[s]: " << time_sec;
    cout << endl;

    return 0;
}
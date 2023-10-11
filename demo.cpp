#include <array>
#include <memory>
#include <iostream>
#include <sstream>

#include "graph.h"

using namespace std;

vector<mpf_class> read_plotsolution(vector<mpf_class> plotsolution, unsigned long error, int algorithm){

    mp_bitcnt_t prec = 1024;
    mpf_set_default_prec (prec);
    mpf_t result;
    mpf_init(result);
    vector<mpf_class> current_plot_solution;
    string line, buffer;
    string solution_path;

    if(algorithm == 0){
        solution_path = "results/homhops.txt";
    }
    if(algorithm == 1){
        solution_path = "results/homhopsplus.txt";
    }
    if(algorithm == 2){
        solution_path = "results/hops.txt";
    }
    if(algorithm == 3){
        solution_path = "results/sghd.txt";
    }

    ifstream file(solution_path.c_str());                             // open file
    if (not file) {
        throw std::runtime_error("Cannot open file.");
    }

    while (std::getline(file, line)) {
        stringstream ss(line);
        ss >> buffer;
        if (not ss) {
            throw std::runtime_error("Invalid file format.");
        }
        mpf_set_str(result, buffer.c_str(), 10);
        mpf_class result2(result);
        current_plot_solution.push_back(result2);
    }
    file.close();

    for(int i=0; i<current_plot_solution.size(); i++){
        current_plot_solution[i] /= error;
        current_plot_solution[i] -= 1;
        if(current_plot_solution[i] < 0){ current_plot_solution[i]*= -1;}
        plotsolution[i] += current_plot_solution[i];
    }

    return plotsolution;
}

int main( int argc, char* argv[] )
{

    //./demo pattern.txt input.txt [time+seconds] [repetitions] [exact] [plot]
    //exact solution + relative error on destined input
    //exact to mpz with stringread


    const char* flags[11] = {
        "-homhops",
        "-homhopsplus",
        "-hops",
        "-sghd",
        "-time",
        "-reps",
        "-exacthom",
        "-exactiso",
        "-plot",
        "-info",
        "-inputstats",
    };

    int timer = 60000;
    int reps = 1;
    int plot = 0;
    int info = 0;
    int algnum = 0;
    int stats = 0;

    unsigned long exacthom;
    unsigned long exactiso;

    //ERROR mpf_set_str(result, buffer.c_str(), 10);

    int flag = -1;
    int algorithms[4] = {0, 0, 0, 0};
    int all_algorithms = 1;
    for (int i = 3; i < argc; i++) {
        for(int j=0; j<11; j++){
            if(strcmp(argv[i], flags[j]) == 0){flag = j;}
            else{flag = -1;}
            if(flag > -1){
                if(flag >= 0  && flag <= 3){
                    algorithms[flag] = 1;
                    all_algorithms = 0;
                    algnum++;
                }
                if(flag == 4){
                    timer = atoi(argv[i+1])*1000;
                    i++;
                }
                if(flag == 5){
                    reps = atoi(argv[i+1]);
                    i++;
                }
                if(flag == 6){
                    exacthom = atoi(argv[i+1]);
                    i++;
                }
                if(flag == 7){
                    exactiso = atoi(argv[i+1]);
                    i++;
                }
                if(flag == 8){
                    plot = 1;
                }
                if(flag == 9){
                    info = 1;
                }
                if(flag == 10){
                    stats = 1;
                }
            }
        }
    }

    if(all_algorithms == 1){
        for(int i=0; i<4; i++){
            algorithms[i] = 1;
            algnum = 4;
        }
    }

    mp_bitcnt_t prec = 1024;
    mpf_set_default_prec (prec);
    mpf_t result;
    mpf_init(result);
    mpf_t result2;
    mpf_init(result2);
    mpf_class homhopsest(0);
    mpf_class homhopsallest(0);
    mpf_class hopsest(0);
    mpf_class sghdest(0);
    mpf_class homhopserr(0);
    mpf_class homhopsallerr(0);
    mpf_class hopserr(0);
    mpf_class sghderr(0);
    vector<mpf_class> solutions_homhops;
    vector<mpf_class> solutions_homhopsplus;
    vector<mpf_class> solutions_hops;
    vector<mpf_class> solutions_sghd;
    vector<mpf_class> plotsolution_homhops;
    vector<mpf_class> plotsolution_homhopsplus;
    vector<mpf_class> plotsolution_hops;
    vector<mpf_class> plotsolution_sghd;
    for(int i=0;i<timer/1000;i++){
        plotsolution_homhops.push_back(hopserr);
        plotsolution_homhopsplus.push_back(hopserr);
        plotsolution_hops.push_back(hopserr);
        plotsolution_sghd.push_back(hopserr);
    }



    mpz_class avgiter_homhops(0);
    mpz_class avgiter_homhopsplus(0);
    mpz_class avgiter_hops(0);
    mpz_class avgiter_sghd(0);

    mpf_class succtries_buffer(0);
    mpf_class succtries_homhops(0);
    mpf_class succtries_homhopsplus(0);
    mpf_class succtries_hops(0);
    mpf_class succtries_sghd(0);



    int iterations = 50000;
    int successful_tries = 0;
    int iteration_count = 0;
    
    int time_sec = timer/1000;

    Graph h(argv[1]);
    Graph g(argv[2]);
    int cycles_h=0;

    if(stats==1){cout << "Pattern: " << argv[1] << endl;}
    cycles_h = graph_props(&h, stats);
    if(stats==1){cout << endl;}

    if(stats==1){cout << "Inputgraph: " << argv[2] << endl;}
    graph_props(&g, stats);
    if(stats==1){cout << endl;}



    cout << "Calculating " << reps << " Repetition(s), each over " << timer/1000 << " Seconds for " << algnum << " Algorithm(s)." << endl;
    cout << "Calculations will approximately take " << algnum*reps*(timer/1000) << " Seconds." << endl << endl; 


    for(int i=0; i<reps; i++){
        if( algorithms[0] == 1 ){
            if(cycles_h == 0){
                homhops(&h, &g, iterations, result, &successful_tries, &iteration_count, timer);
                mpf_class result2(result);
                solutions_homhops.push_back(result2);
                homhopsest += result2;
                solutions_homhops[i] = solutions_homhops[i]/exacthom - 1;
                if(solutions_homhops[i]<0){solutions_homhops[i]*=-1;}
                homhopserr += solutions_homhops[i];
                avgiter_homhops += iteration_count;
                succtries_buffer = successful_tries;
                succtries_buffer/=iteration_count;
                succtries_homhops += succtries_buffer;

                plotsolution_homhops = read_plotsolution(plotsolution_homhops, exacthom, 0);

                if(info==1){
                    cout << "(homhops)     Estimate: " << std::fixed << result << " ";
                    cout << ", Iterations: " << iteration_count << " ";
                    cout << ", Successful Tries: " << successful_tries << " ";
                    cout << ", Time[s]: " << time_sec;
                    cout << endl;
                }
            }
            else{
                cout << "(homhops)     Pattern is not a tree.\n";
            }
        }

        if( algorithms[1] == 1 ){
            homhopsplus(&h, &g, iterations, result, &successful_tries, &iteration_count, timer);
            mpf_class result2(result);
            solutions_homhopsplus.push_back(result2);
            homhopsallest += result2;
            solutions_homhopsplus[i] = solutions_homhopsplus[i]/exacthom - 1;
            if(solutions_homhopsplus[i]<0){solutions_homhopsplus[i]*=-1;}
            homhopsallerr += solutions_homhopsplus[i];
            avgiter_homhopsplus += iteration_count;
            succtries_buffer = successful_tries;
            succtries_buffer/=iteration_count;
            succtries_homhopsplus += succtries_buffer;

            plotsolution_homhopsplus = read_plotsolution(plotsolution_homhopsplus, exacthom, 1);

            if(info==1){
                cout << "(homhopsplus) Estimate: " << std::fixed << result << " ";
                cout << ", Iterations: " << iteration_count << " ";
                cout << ", Successful Tries: " << successful_tries << " ";
                cout << ", Time[s]: " << time_sec;
                cout << endl;
            }
        }

        if( algorithms[2] == 1){
            if(cycles_h == 0){
                hops(&h, &g, iterations, result, &successful_tries, &iteration_count, timer);
                mpf_class result2(result);
                solutions_hops.push_back(result2);
                hopsest += result2;
                solutions_hops[i] = solutions_hops[i]/exactiso - 1;
                if(solutions_hops[i]<0){solutions_hops[i]*=-1;}
                hopserr += solutions_hops[i];
                avgiter_hops += iteration_count;
                succtries_buffer = successful_tries;
                succtries_buffer/=iteration_count;
                succtries_hops += succtries_buffer;

                plotsolution_hops = read_plotsolution(plotsolution_hops, exactiso, 2);

                if(info==1){
                    cout << "(hops)        Estimate: " << std::fixed << result << " ";
                    cout << ", Iterations: " << iteration_count << " ";
                    cout << ", Successful Tries: " << successful_tries << " ";
                    cout << ", Time[s]: " << time_sec;
                    cout << endl;
                }
            }
            else{
                cout << "(homhops)     Pattern is not a tree.\n";
            }
        }

        if( algorithms[3] == 1){
            if((&g)->N >=10000){cout << "(sghd)        Warning: Inputgraph may be too big to construct adjacency matrix (will cause Segmentation fault)." << endl;}
            sghd(argv[1], argv[2], iterations, result, &successful_tries, &iteration_count, timer);
            mpf_class result2(result);
            solutions_sghd.push_back(result2);
            sghdest += result2;
            solutions_sghd[i] = solutions_sghd[i]/exacthom - 1;
            if(solutions_sghd[i]<0){solutions_sghd[i]*=-1;}
            sghderr += solutions_sghd[i];
            avgiter_sghd += iteration_count;
            succtries_buffer = successful_tries;
            succtries_buffer/=iteration_count;
            succtries_sghd += succtries_buffer;

            plotsolution_sghd = read_plotsolution(plotsolution_sghd, exacthom, 3);

            if(info==1){
                cout << "(sghd)        Estimate: " << std::fixed << result << " ";
                cout << ", Iterations: " << iteration_count << " ";
                cout << ", Successful Tries: " << successful_tries << " ";
                cout << ", Time[s]: " << time_sec;
                cout << endl;
            }
        }
        if (info == 1){
            cout << endl;
        }
    }

    string s = "results/homhops.txt";
    string s1 = "results/homhopsplus.txt";
    string s2 = "results/hops.txt";
    string s3 = "results/sghd.txt";
    std::ofstream outfile (s);
    std::ofstream outfile1 (s1);
    std::ofstream outfile2 (s2);
    std::ofstream outfile3 (s3);

    if( algorithms[0] == 1){
        homhopsest /= reps;
        homhopserr /= reps;
        avgiter_homhops /= reps;
        succtries_homhops /= reps;
        for(int i=0;i<timer/1000;i++){
            plotsolution_homhops[i] /= reps;
            outfile << plotsolution_homhops[i] << endl;
        }
        cout << "(homhops)           avg. Iterations: " << avgiter_homhops << ", avg. Successful Tries: " << succtries_homhops << ", avg. Estimate: " << homhopsest << ", avg. Error: " << homhopserr << endl;
    }
    if( algorithms[1] == 1){
        homhopsallest /= reps;
        homhopsallerr /= reps;
        avgiter_homhopsplus /= reps;
        succtries_homhopsplus /= reps;
        for(int i=0;i<timer/1000;i++){
            plotsolution_homhopsplus[i] /= reps;
            outfile1 << plotsolution_homhopsplus[i] << endl;
        }
        cout << "(homhopsplus)       avg. Iterations: " << avgiter_homhopsplus << ", avg. Successful Tries: " << succtries_homhopsplus << ", avg. Estimate: " << homhopsallest << ", avg. Error: " << homhopsallerr << endl;
    }
    if( algorithms[2] == 1){
        hopsest /= reps;
        hopserr /= reps;
        avgiter_hops /= reps;
        succtries_hops /= reps;
        for(int i=0;i<timer/1000;i++){
            plotsolution_hops[i] /= reps;
            outfile2 << plotsolution_hops[i] << endl;
        }
        cout << "(hops)              avg. Iterations: " << avgiter_hops << ", avg. Successful Tries: " << succtries_hops << ", avg. Estimate: " << hopsest << ", avg. Error: " << hopserr << endl;
    }
    if( algorithms[3] == 1){
        sghdest /= reps;
        sghderr /= reps;
        avgiter_sghd /= reps;
        succtries_sghd /= reps;
        for(int i=0;i<timer/1000;i++){
            plotsolution_sghd[i] /= reps;
            outfile3 << plotsolution_sghd[i] << endl;
        }
        cout << "(sghd)              avg. Iterations: " << avgiter_sghd << ", avg. Successful Tries: " << succtries_sghd << ", avg. Estimate: " << sghdest << ", avg. Error: " << sghderr << endl;
    }

    outfile.close();
    outfile1.close();
    outfile2.close();
    outfile3.close();

    
    string c;
    string plotcommand = "python plot.py ";
    for(int i=0; i<4; i++){
        c = to_string(algorithms[i]);
        plotcommand = plotcommand + c + " ";
    }
    if(plot==1){
        std::array<char, 128> buffer;
        std::string resu;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(plotcommand.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            resu += buffer.data();
        }
    }

    return 0;
}
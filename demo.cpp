#include <array>
#include <memory>
#include <iostream>
#include <sstream>

#include "graph.h"

using namespace std;

vector<mpf_class> read_plotsolution(vector<mpf_class> plotsolution, mpf_class error, int algorithm){

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

const char * snapgraphspath[7] {
    "input/SNAP-DATASETS/webkb-wisc.txt",
    "input/SNAP-DATASETS/bio-yeast.txt",
    "input/SNAP-DATASETS/facebook_combined.txt",
    "input/SNAP-DATASETS/CA-GrQc.txt",
    "input/SNAP-DATASETS/CA-HepTh.txt",
    "input/SNAP-DATASETS/com-amazon.ungraph.txt",
    "input/SNAP-DATASETS/com-youtube.ungraph.txt",
};

const char * treepatternspath[17]{
    "input/TREEPATTERNS/tree1.txt",
    "input/TREEPATTERNS/tree2.txt",
    "input/TREEPATTERNS/tree3.txt",
    "input/TREEPATTERNS/tree4.txt",
    "input/TREEPATTERNS/tree5.txt",
    "input/TREEPATTERNS/tree6.txt",
    "input/TREEPATTERNS/tree7.txt",
    "input/TREEPATTERNS/tree8.txt",
    "input/TREEPATTERNS/tree9.txt",
    "input/TREEPATTERNS/tree10.txt",
    "input/TREEPATTERNS/tree11.txt",
    "input/TREEPATTERNS/tree12.txt",
    "input/TREEPATTERNS/tree13.txt",
    "input/TREEPATTERNS/tree14.txt",
    "input/TREEPATTERNS/tree15.txt",
    "input/TREEPATTERNS/tree16.txt",
    "input/TREEPATTERNS/tree17.txt",
};

const char* arbitrarypatternspath[29]{
    "input/ARBITRARYPATTERNS/pattern1.txt",
    "input/ARBITRARYPATTERNS/pattern2.txt",
    "input/ARBITRARYPATTERNS/pattern3.txt",
    "input/ARBITRARYPATTERNS/pattern4.txt",
    "input/ARBITRARYPATTERNS/pattern5.txt",
    "input/ARBITRARYPATTERNS/pattern6.txt",
    "input/ARBITRARYPATTERNS/pattern7.txt",
    "input/ARBITRARYPATTERNS/pattern8.txt",
    "input/ARBITRARYPATTERNS/pattern9.txt",
    "input/ARBITRARYPATTERNS/pattern10.txt",
    "input/ARBITRARYPATTERNS/pattern11.txt",
    "input/ARBITRARYPATTERNS/pattern12.txt",
    "input/ARBITRARYPATTERNS/pattern13.txt",
    "input/ARBITRARYPATTERNS/pattern14.txt",
    "input/ARBITRARYPATTERNS/pattern15.txt",
    "input/ARBITRARYPATTERNS/pattern16.txt",
    "input/ARBITRARYPATTERNS/pattern17.txt",
    "input/ARBITRARYPATTERNS/pattern18.txt",
    "input/ARBITRARYPATTERNS/pattern19.txt",
    "input/ARBITRARYPATTERNS/pattern20.txt",
    "input/ARBITRARYPATTERNS/pattern21.txt",
    "input/ARBITRARYPATTERNS/pattern22.txt",
    "input/ARBITRARYPATTERNS/pattern23.txt",
    "input/ARBITRARYPATTERNS/pattern24.txt",
    "input/ARBITRARYPATTERNS/pattern25.txt",
    "input/ARBITRARYPATTERNS/pattern26.txt",
    "input/ARBITRARYPATTERNS/pattern27.txt",
    "input/ARBITRARYPATTERNS/pattern28.txt",
    "input/ARBITRARYPATTERNS/pattern29.txt",    
};

const char * myinputpath1[4]{
"input/MY-INPUT-DATASETS/input1.txt",
"input/MY-INPUT-DATASETS/input2.txt",
"input/MY-INPUT-DATASETS/input3.txt",
"input/MY-INPUT-DATASETS/input4.txt",
};
const char * myinputpath2[4]{
"input/MY-INPUT-DATASETS/input5.txt",
"input/MY-INPUT-DATASETS/input6.txt",
"input/MY-INPUT-DATASETS/input7.txt",
"input/MY-INPUT-DATASETS/input8.txt",
};

const char * exactsolutions_iso_snap [136]{
    "86028", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "1796136", "449988", "4363910556", "14898294", "12620766", "-1", "-1", "-1",
    "4665228", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "429416", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "211042968", "14674416", "2329605912840", "648943416", "363442128", "-1", "-1", "-1",
    "12170504", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "19442542", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "39875600", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "17403104195664", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
    "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1",
};

const char * exactsolutions_iso_input [68]{
    "4378", "92102", "3885102", "12396556", 
    "3894", "92202", "3886884", "12391950", 
    "15926", "867814", "113374200", "485326886", 
    "17858", "872284", "113324778", "485372868", 
    "12264", "872472", "113555616", "485130816", 
    "63528", "8079590", "3283217964", "18906173306", 
    "63292", "8134168", "3283181350", "18900681680", 
    "56568", "8028896", "3284480424", "18905267208", 
    "247866", "74762419", "94386275190", "732356991937", 
    "220088", "73946250", "94423424864", "732505074392", 
    "249240", "75072926", "94380817146", "732165158536", 
    "839478", "672300272", "2694644724614", "28229476934034", 
    "835272", "674004024", "2694809589848", "28228665554884", 
    "945800", "679835514", "2693747209182", "28224112603546", 
    "901392", "5952257424", "77030086361952", "1085182391841024", 
    "2395664", "6091769972", "76433667340964", "1081547946663680", 
    "2431568", "5958305896", "76434259536664", "1082688568497192", 
};

const char * exactsolutions_hom_snap [136]{
    "124395", "129268", "2157760302", "13560523", "9855684", "-1", "-1", "-1",
    "1851824", "525500", "4419976118", "16306890", "14471231", "-1", "-1", "-1",
    "6834307", "1676464", "411833987670", "567639199", "243230802", "-1", "-1", "-1",
    "2517080", "1071342", "286823817114", "495825900", "176940299", "-1", "-1", "-1",
    "221948472", "17545344", "2355919960530", "741581264", "443415181", "-1", "-1", "-1",
    "32090373", "7915592", "49222919931840", "22733303385", "4658032786", "-1", "-1", "-1",
    "250252664", "24696944", "55305441088960", "23008050956", "4754854069", "-1", "-1", "-1",
    "73139727", "14859444", "67965998044966", "26189395315", "6354567596", "-1", "-1", "-1",
    "924206399", "78294696", "7095132286732738", "966947586395", "98957827373", "-1", "-1", "-1",
    "1074979041", "107451186", "8728793938671298", "1105647173859", "129365777370", "-1", "-1", "-1",
    "1192947793", "87780928", "7737794843554034", "976282199891", "98925600340", "-1", "-1", "-1",
    "6752403555", "559325596", "1187068713706003672", "47762226505833", "2831177263198", "-1", "-1", "-1",
    "34676547774", "1464883634", "1245549690361878278", "48765293299608", "2881927376949", "-1", "-1", "-1",
    "4606454283", "394416534", "1019048110820575622", "42399542409751", "2274289088366", "-1", "-1", "-1",
    "40777601777777", "161099758364", "18350545872637099644", "3774320779883297", "238226041266916", "-1", "-1", "-1",
    "11707269997019", "77079951014", "2464547391769832286", "2595052532262865", "98701490979279", "-1", "-1", "-1",
    "421641271449", "10428886834", "14281460416152238670", "2537489616461771", "95128135647344", "-1", "-1", "-1",
};

const char * exactsolutions_hom_trees_input[68] {
    "6768", "113252", "4180284", "13097360", 
    "7276", "122064", "4288092", "13344694", 
    "37972", "1295968", "131071292", "541323172", 
    "35966", "1217064", "127915360", "531445398", 
    "43194", "1494042", "137807112", "561694972", 
    "200610", "13849476", "4009259924", "21965717572", 
    "203894", "14023032", "4013605314", "21972222758", 
    "212152", "14751452", "4108198756", "22375100768", 
    "1075380", "149626633", "122766772180", "891586467981", 
    "1132090", "158640138", "125747888498", "908226157590", 
    "1079448", "150223856", "122808793046", "891558086858", 
    "6032884", "1703419352", "3848922577982", "36865844193352", 
    "6111164", "1717755778", "3851777283814", "36877657842142", 
    "5739010", "1607150100", "3757843474980", "36190417863594", 
    "46491318", "28970883072", "142287140362744", "1728374980269412", 
    "36836248", "21298733715", "123947533488332", "1553433283420775", 
    "35738518", "20639424576", "123622629778798", "1552717738335206",
};

const char * exactsolutions_hom_cycle_input[116] {
    "370", "11230", "82308", "2860540", 
    "18", "3078", "7692", "1700712", 
    "1292", "178280", "1772192", "343768170", 
    "1082", "171528", "1699912", "342644912", 
    "62", "48968", "166162", "204381148", 
    "618", "64998", "312700", "206796704", 
    "18", "15526", "22436", "122179628", 
    "0", "3552", "1176", "72167496", 
    "3360", "2624554", "35166432", "41043574146", 
    "3658", "2719324", "36549054", "41176032992", 
    "4918", "2929354", "39780300", "41446092520", 
    "240", "821570", "3733160", "24657657300", 
    "2004", "1025680", "6659164", "24849557314", 
    "194", "750074", "3436208", "24480988360", 
    "210", "778408", "3580954", "24560278930", 
    "222", "806052", "3745898", "24640585136", 
    "36", "226100", "365112", "14650188688", 
    "62", "255064", "500538", "14729677664", 
    "62", "246840", "482054", "14681607572", 
    "106", "291508", "645692", "14820921302", 
    "1540", "491884", "2602776", "15130799014", 
    "0", "58896", "26880", "8700341040", 
    "18", "80656", "66846", "8804723884", 
    "62", "123724", "224798", "8940331324", 
    "18", "89994", "79956", "8852757132", 
    "0", "21108", "4648", "5229157348", 
    "0", "21108", "4648", "5229157348", 
    "0", "7464", "1404", "3117383928", 
    "0", "1080", "0", "1821718362", 
};

    //Search for exact solution
    //Search for Pattern
    int treepattern = -1;
    int patternnumber = -1;
    int inputnumber = -1;
    int snapgraph = -1;
    for(int i=0; i<17;i++){
        if(strcmp(argv[1], treepatternspath[i])==0){
            patternnumber = i;
            treepattern = 1;
        }
    }
    for(int i=0; i<29; i++){
        if(strcmp(argv[1], arbitrarypatternspath[i])==0){
            patternnumber = i;
            treepattern = 0;
        }
    }
    //Search for Input
    for(int i=0; i<7; i++){
        if(strcmp(argv[2], snapgraphspath[i])==0){
            inputnumber = i;
            snapgraph = 1;
        }
    }
    for(int i=0; i<4; i++){
        if(strcmp(argv[2], myinputpath1[i])==0){
            inputnumber = i;
            snapgraph = 0;
        }
    }
    for(int i=0; i<4; i++){
        if(strcmp(argv[2], myinputpath2[i])==0){
            inputnumber = i;
            snapgraph = -1;
        }
    }


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
    int exacthomarg = 0;
    int exactisoarg = 0;

    mpf_t exactbuf;
    mpf_init(exactbuf);
    mpf_set_ui(exactbuf, 1);
    mpf_class exacthom(exactbuf);
    mpf_class exactiso(exactbuf);

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
                    mpf_set_str(exactbuf, argv[i+1], 10);
                    exacthom = mpf_class(exactbuf);
                    exacthomarg = 1;
                    i++;
                }
                if(flag == 7){
                    mpf_set_str(exactbuf, argv[i+1], 10);
                    exactiso = mpf_class(exactbuf);
                    exactisoarg = 1;
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

    if(exacthomarg == 0){
        if(treepattern == 0){
            if(snapgraph == 0){
                mpf_set_str(exactbuf, exactsolutions_hom_cycle_input[patternnumber*4+inputnumber], 10);
                exacthom = mpf_class(exactbuf);
                if(exacthom == -1){
                    cout << "Homomorphism Solution unknown." << endl;
                    exacthom = mpf_class(-1);
                }
            }
            else{
                cout << "Homomorphism Solution unknown." << endl;
                exacthom = mpf_class(-1);
            }
        }
        else{
            if(snapgraph == 1){
                mpf_set_str(exactbuf, exactsolutions_hom_snap[patternnumber*8+inputnumber], 10);
                exacthom = mpf_class(exactbuf);
                if(exacthom == -1){
                    cout << "Homomorphism Solution unknown." << endl;
                    exacthom = mpf_class(-1);
                }
            }
            if(snapgraph == -1){
                mpf_set_str(exactbuf, exactsolutions_hom_trees_input[patternnumber*4+inputnumber], 10);
                exacthom = mpf_class(exactbuf);
                if(exacthom == -1){
                    cout << "Homorphism Solution unknown." << endl;
                    exacthom = mpf_class(-1);
                }
            }
            if(snapgraph == 0){
                cout << "Homomorphism Solution unknown." << endl;
                exacthom = mpf_class(-1);
            }
        }

    }
    if(exactisoarg == 0){
        if(treepattern == 0){
            cout << "Isomorphism Solution unknown." << endl;
            exactiso = mpf_class(-1);
        }
        else{
            if(snapgraph == 1){
                mpf_set_str(exactbuf, exactsolutions_iso_snap[patternnumber*8+inputnumber], 10);
                exactiso = mpf_class(exactbuf);
                if(exactiso == -1){
                    cout << "Isomorphism Solution unknown." << endl;
                    exactiso = mpf_class(-1);
                }
            }
            if(snapgraph == -1){
                mpf_set_str(exactbuf, exactsolutions_iso_input[patternnumber*4+inputnumber], 10);
                exactiso = mpf_class(exactbuf);
                if(exactiso == -1){
                    cout << "Isomorphism Solution unknown." << endl;
                    exactiso = mpf_class(-1);
                }
            }
            if(snapgraph == 0){
                cout << "Isomorphism Solution unknown." << endl;
                exactiso = mpf_class(-1);
            }
        }
        cout << endl;
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
            solutions_sghd[i] /= exacthom;
            solutions_sghd[i] -= 1;
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
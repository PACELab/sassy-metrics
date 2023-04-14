// sudo perf stat -e cycles,instructions,ref-cycles,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores -I 1000 --per-thread &> perftrace.txt

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main (int argc,char* argv[]) {
    ifstream infile("rapltrace-" + string(argv[1]) + ".txt");
    ofstream outfile("raplparsed-" + string(argv[1]) + ".csv");
    outfile << "time,pkg_pwr,ram_pwr" << endl;

    // 1.001034101  nextcloud-fixer-2365924         462,094,832      cycles 
    // float t;
    // string pid, count, event;
    // string rw;
    string flush;
    string a, b;
    string stop_header = "PkgWatt	RAMWatt";

    while(1){
        getline(infile, flush);
        if(flush == stop_header) break;
        flush = "";
    }

    int i = 1;
    // getline(infile, flush);
    while (infile >> a >> b) {
        getline(infile, flush);
        string str = to_string(i) + "," + a + "," + b;
        getline(infile, flush);
        getline(infile, flush);
        getline(infile, flush);
        outfile << str << endl;
        i++;
    }
    outfile.close();
}
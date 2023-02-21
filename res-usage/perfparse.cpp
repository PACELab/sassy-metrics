// sudo perf stat -e cycles,instructions,ref-cycles,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores -I 1000 --per-thread &> perftrace.txt
// ./perfparse mnn

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main (int argc, char* argv[]) {
    ifstream infile("perftrace-" + string(argv[1]) + ".txt");
    ofstream outfile("perfparsed-" + string(argv[1]) + ".csv");
    outfile << "time,pid,count,event" << endl;

    // 1.001034101  nextcloud-fixer-2365924         462,094,832      cycles 
    float t;
    string pid, count, event;
    string rw;
    string flush;
    getline(infile, flush);
    int streampos;
    string gbg;
    
    while (infile >> t >> pid >> count >> event) {
        int time = int(t);
        if (pid == "rs:main") {
            infile.seekg(streampos);
            infile >> t >> gbg >> pid >> count >> event;
            pid = pid.substr(pid.find_last_of('-') + 1);
            count.erase(remove(count.begin(), count.end(), ','), count.end());
            string str = to_string(time) + "," + pid + "," + count + "," + event;
            outfile << str << endl;
            getline(infile, flush);
            streampos = infile.tellg();
            continue;
        }
        pid = pid.substr(pid.find_last_of('-') + 1);
        count.erase(remove(count.begin(), count.end(), ','), count.end());
        string str = to_string(time) + "," + pid + "," + count + "," + event;
        outfile << str << endl;
        getline(infile, flush);
        streampos = infile.tellg();
    }
    outfile.close();
}
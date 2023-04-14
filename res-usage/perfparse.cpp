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
        // if pid is a kernel thread, skip
        // kernel threads can contain any of the following in the pid: kworker, ksoftirqd, kthrotld, kswapd, kauditd, kpsmoused, kintegrityd, kblockd, kthreadd, kdevtmpfs, rcu_, 
        if (pid.find("kworker") != string::npos || pid.find("ksoftirqd") != string::npos || pid.find("kthrotld") != string::npos || pid.find("kswapd") != string::npos || pid.find("kauditd") != string::npos || pid.find("kpsmoused") != string::npos || pid.find("kintegrityd") != string::npos || pid.find("kblockd") != string::npos || pid.find("kthreadd") != string::npos || pid.find("kdevtmpfs") != string::npos || pid.find("rcu_") != string::npos) {
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
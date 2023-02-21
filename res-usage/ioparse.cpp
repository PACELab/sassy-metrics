// sudo blktrace -d /dev/sda -o - | blkparse -i - -f "%5T.%9t %5p %5n %9N %3d\n" &> trace.txt

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (int argc,char* argv[]) {
    ifstream infile("iotrace-" + string(argv[1]) + ".txt");
    ofstream outfile("ioparsed-" + string(argv[1]) + ".csv");
    outfile << "time,pid,block,byte" << endl;

    // 0.000000000 1253124     8      4096   W
    float t;
    int pid, block, byte;
    string rw;
    string flush;
    while (infile >> t >> pid >> block >> byte) {
        int time = int(t);
        string str = to_string(time) + "," + to_string(pid) + "," + to_string(block) + "," + to_string(byte);
        outfile << str << endl;
        getline(infile, flush);
    }
    outfile.close();
}


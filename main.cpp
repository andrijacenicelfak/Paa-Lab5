#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>

#include "Node.hpp"

using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2)
        return -1;

    ofstream f(argv[2], ios::app);

    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    /*
    f   << "Binomni heap sa : " << N << " elemenata\n"
        << "Vreme za extractmin :" << extractmin - pocetak << "ms\n"
        << "Vreme za decrement key :" << deckey - extractmin << "ms\n"
        << "Vreme za delete node : " << delnode - deckey << "ms\n"
        << "Vreme za add : " << add - delnode << "ms\n"
        << "-----------------------------------------\n";
        */
    f.close();
    return 1;
}
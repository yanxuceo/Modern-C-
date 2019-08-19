#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int main() {
    stringstream s_out;
    string ext = ".txt";
    string file_name = "";

    for (int i = 0; i < 500; i++) {
        s_out << setw(5) << setfill('0') << i << ext;
        file_name = s_out.str();
        s_out.str("");
        cerr << file_name << endl;
    }

    stringstream s_in(file_name);
    int i;
    string rest;
    s_in >> i >> rest;
    cerr << "Number: " << i << " rest is: " << rest;

    return 0;
}

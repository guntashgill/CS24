#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

string rotate(string str, int rot) {
    int len = str.length();
    rot = rot % len;
    if (rot < 0) {
        rot += len;
    }
    return str.substr(len-rot) + str.substr(0, len-rot);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <rotation amount>" << endl;
        return 1;
    }

    int rot = atoi(argv[1]);
    string line;
    getline(cin, line);

    cout << rotate(line, rot) << endl;

    return 0;
}

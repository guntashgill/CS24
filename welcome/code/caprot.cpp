#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

string rotate(string word, int num) {
    int len = word.length();
    num = num % len;
    if (num < 0) {
        num += len;
    }
    return word.substr(len-num) + word.substr(0, len-num);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <rotation amount>" << endl;
        return 1;
    }

    int num = atoi(argv[1]);
    string line;
    getline(cin, line);

    cout << rotate(line, num) << endl;

    return 0;
}

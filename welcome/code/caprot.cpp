#include <iostream>
#include <string>

using namespace std;
int main(int argc, char* argv[]) {

    argc = argc + 1; 
    std::string line;
    std::getline(std::cin, line);

    
    int len = line.length();
    std::string result = "";
    result = line;
    for (int i = 0; i < len; i++) {
        result[i] = tolower(result[i]);
    }
    for (int i = 0; i < len; i++) {
        if (isupper(line[i])){
            int p = i + (atoi(argv[1]));
            result[p] = toupper(result[p]); 
        }
    }
    cout << result << endl;
}




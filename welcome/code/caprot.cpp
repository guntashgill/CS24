#include <iostream>
#include <string>

using namespace std;
int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <num>" << endl;
        return 1;
    }

    argc = argc + 1; 
    std::string line;
    std::getline(std::cin, line);
    long input1 = atoi(argv[1]);


    if ((input1) > 0) {
        int len = line.length();
        std::string result = "";
        result = string(line);
        for (int i = 0; i < len; i++) {
            result[i] = tolower(result[i]);
        }
        for (int i = 0; i < len; i++) {
            if (isupper(line[i])){
                long p = (i + (input1));
                while (p >= len) {
                    p -= len;
                }
                result[p] = toupper(result[p]); 
            }
        }
        cout << result << endl;
    }
    else{
        int len = line.length();
        std::string result = "";
        result = string(line);
        for (int i = 0; i < len; i++) {
            result[i] = tolower(result[i]);
        }
        for (int i = 0; i < len; i++) {
            if (isupper(line[i])){
                int p = (i + (atoi(argv[1])));
                while (p < 0) {
                    p += len;
                }
                result[p] = toupper(result[p]); 
            }
        }
        cout << result << endl;
    }
}







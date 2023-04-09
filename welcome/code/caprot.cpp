#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: caprot <num_chars>" << std::endl;
        return 1;
    }


    int num_chars = std::stoi(argv[1]);


    std::string line;
    std::getline(std::cin, line);

    
    int len = line.length();
    std::string result;
    for (int i = 0; i < len; i++) {
        char c = line[(i + len - num_chars) % len];
        if (std::islower(c)) {
            c = std::toupper(c);
        }
        result += c;
    }

    std::cout << result << std::endl;

    return 0;
}


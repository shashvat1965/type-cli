#include <iostream>
#include <chrono>
#include <fstream>
#include <fstream>
#include "typing_test.cpp"

int main(){
    // read sentences.txt file and get a random line
    std::ifstream file("sentences.txt");
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(file, line)){

        for (int i = 0; i < line.size(); i++){
            if (line[i] >= 'A' && line[i] <= 'Z'){
                line[i] += 32;
            }
        }

        lines.push_back(line);
    }

    srand(time(0));
    TypingTest typingTest = TypingTest(lines[rand() % lines.size()]);
    typingTest.start();

    return 0;
}

#include <cstring>
#include <curses.h>
#include <string>
#include <iostream>
#include <chrono>
#include <ncurses.h>


class TypingTest{

    std::string sentence;
    std::string user_input;
    int errors;
    int words;
    float time;
    int wpm;
    float accuracy;

    public:
        TypingTest(std::string sentence){
            this->sentence = sentence;
            errors = 0;
            words = 0;
            time = 0;
            wpm = 0;
            accuracy = 0;
            user_input = "";
        };

        void start(){
            auto start = std::chrono::high_resolution_clock::now();

            initscr(); // Initialize ncurses
            noecho();
            cbreak();

            printw("%s", sentence.c_str());
            printw("\n");
            int i = 0;
            printw("%s", user_input.c_str());
            printw("%s", "Type to start");
            while(i < sentence.size()){
                int ch = getch();

                if (ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127) {
                        user_input.pop_back();
                        i--;
                        refresh_text();
                        continue;
                    }

                if (ch == '\n') {
                    break;
                }

                user_input += char(ch);
                i++;
                refresh_text();
            }
            endwin();

            // calculate time
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            time = duration / 1000.0;

            calculate_details();
            display();
        }

        void refresh_text(){
            clear();
            printw("%s", sentence.c_str());
            printw("\n");
            printw("%s", user_input.c_str());
        };

        void calculate_details(){
            // reset values
            errors = 0;
            words = 0;

            // error count
            for (int i = 0; i < sentence.size(); i++){
                if (sentence[i] != user_input[i]){
                    errors++;
                }
            }

            // word count
            for (int i = 0; i < sentence.size(); i++){
                if (sentence[i] == ' '){
                    words++;
                }
            }
            words++;

            // calculate wpm and accuracy
            wpm = words / time * 60;
            accuracy = (sentence.size() - (float)errors) / sentence.size() * 100;
        }

        void display(){
            std::cout << "Time taken: " << time << " seconds" << std::endl;
            std::cout << "Errors: " << errors << std::endl;
            std::cout << "Words: " << words << std::endl;
            std::cout << "WPM: " << wpm << std::endl;
            std::cout << "Accuracy: " << accuracy << "%" << std::endl;
            std::cout << "\n";
            std::cout << user_input << std::endl;
        }

};

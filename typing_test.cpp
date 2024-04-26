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
    int accuracy;

    public:
        TypingTest(std::string sentence){
            this->sentence = sentence;
            user_input = "";
            errors = 0;
            words = 0;
            time = 0;
            wpm = 0;
            accuracy = 0;

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
            printw("\n");

            while(i < sentence.size()){
                int ch = getch();

                if (ch == 127 || ch == KEY_BACKSPACE || ch == '\b') {
                    if (i != 0) {
                        i--;
                        user_input.pop_back();
                        refresh_text();
                    }
                    continue;
                }

                // if (ch == '\n') {
                //     break;
                // }

                user_input[i++] = ch;
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
            calculate_details();
            clear();
            printw("%s", sentence.c_str());
            printw("\n");
            printw("%s", user_input.c_str());
            printw("\n");
            printw("%s", "Typing speed: ");
            printw("%d", wpm);
        };

        void calculate_details(){
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

            // calculate wpm and accuracy
            wpm = words / time * 60;
            accuracy = (sentence.size() - errors) / sentence.size() * 100;
        }

        void display(){
            std::cout << "Time taken: " << time << " seconds" << std::endl;
            std::cout << "Errors: " << errors << std::endl;
            std::cout << "Words: " << words << std::endl;
            std::cout << "WPM: " << wpm << std::endl;
            std::cout << "Accuracy: " << accuracy << "%" << std::endl;
        }

};

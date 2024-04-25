/**
 * @file main.cpp
 *
 * @mainpage DA project2
 * @section intro_sec Introduction
 * This project was made in the context of the Algorithm Design class.
 *
 * INTROOO
 *
 * This project was made by: Frederica Pereira (up202108167) and  Leonor Couto (up202205796).
 */

#include <map>
#include <stack>
//#include <chrono>
#include "AuxFunctions.h"



map<string, int> m = {{"dataset", 0}, {"main", 1},{"algo", 2}};
stack<string> menus;
bool over = false;
bool quit = false;

void clearMenus();

int main();
void mainMenu();
void datasetMenu();
void algo();


/**
 * @brief Clears all the menus
 *
 * Complexity: O(n)
 */
void clearMenus() {
    while (!menus.empty()) {
        menus.pop();
    }
}


/**
 * @brief Main function to initialize data and run the program.
 *
 * Complexity: O(???)
 *
 * @return Program exit status.
 */
int main() {
    //load csv
    menus.emplace("dataset");

    //menus.emplace("main");
    while (true) {
        string next = menus.top();
        switch (m.at(next)) {
            case 0:
                datasetMenu();
                break;
            case 1:
                mainMenu();
                break;
            case 2:
                algo();
                break;
            default:
                quit = true;
        }
        if (over) {
            int op = 0;
            cout << endl;
            cout << "1 - Return to Main Menu" << endl;
            cout << "0 - Exit." << endl;
            while (true) {
                cout << "Write the number of what you want to do: ";
                if (cin >> op) {
                    if (op == 1) {
                        clearMenus();
                        menus.emplace("main");
                        break;
                    }
                    else if (op == 0) {
                        quit = true;
                        break;
                    }
                    else {
                        cout << "Invalid number! The number should be 0 or 1." << endl;
                    }
                }
                else {
                    cout << "Invalid input! Please enter a valid number." << endl;
                    cin.clear();          // Clear the error state
                    cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
                }
            }
            over = false;
        }
        if (quit) break;
    }
    system("exit");
    return 0;
}

/**
 * @brief Main Menu
 *
 * Complexity: O(???)
 */
void mainMenu() {

    int op = 0;
    cout << endl << "----------------------------" << endl;
    cout << endl << "      Main Menu   " << endl;
    cout << endl << "----------------------------" << endl;
    cout << "1 - algo." << endl;
    cout << "0 - Quit." << endl;
    cout << endl;
    cout << "Note: If you enter a 'q' when asked for an input," << endl;
    cout << "you will return to the main menu." << endl;
    cout << endl;

    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            cout << endl;
            switch (op) {
                case 1 :
                    menus.emplace("algo");
                    return;
                case 0:
                    quit = true;
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 7." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

void datasetMenu(){
    int op = 0;
    cout << endl << "----------------------------" << endl;
    cout << endl << "      Dataset Menu   " << endl;
    cout << endl << "----------------------------" << endl;
    cout << "1 - Toy-Graphs - shipping" << endl;
    cout << "2 - Toy-Graphs - stadiums" << endl;
    cout << "3 - Toy-Graphs - tourism" << endl;
    cout << "0 - Quit." << endl;
    cout << endl;
    cout << "Note: If you enter a 'q' when asked for an input," << endl;
    cout << "you will return to the main menu." << endl;
    cout << endl;

    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            cout << endl;
            switch (op) {
                case 1 :
                    csvInfo::createGraph("a");
                    menus.emplace("main");
                    return;
                case 2 :
                    csvInfo::createGraph("b");
                    menus.emplace("main");
                    return;
                case 3 :
                    csvInfo::createGraph("c");
                    menus.emplace("main");
                    return;
                case 0:
                    quit = true;
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 7." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief à de ser algo :)
 */
void algo(){
    cout << "entrei no algo";
    AuxFunctions::test();
    over = true;
}
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
#include <chrono>
#include "AuxFunctions.h"




map<string, int> m = {{"dataset", 0}, {"main", 1},{"backtracking", 2}, {"triangular", 3}, {"otherTSP", 4},};
stack<string> menus;
bool over = false;
bool quit = false;

void clearMenus();

int main();
void mainMenu();
void datasetMenu();
//void algo();
void solveTSPBacktracking();
void tsp_2_approximation();

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
                solveTSPBacktracking();
                break;
            case 3:
                tsp_2_approximation();
                break;
            case 4:
                //topico 5
                break;
            case 5:
                //topico 4
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
    cout << "1 - T2.1 - Backtracking Algorithm." << endl;
    cout << "2 - T2.2 - Triangular Approximation Heuristic." << endl;
    cout << "3" << endl;
    cout << "4 - Change dataset" << endl;
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
                    menus.emplace("backtracking");
                    return;
                case 2 :
                    menus.emplace("triangular");
                    return;
                case 3 :
                    //menu3
                    return;
                case 4 :
                    csvInfo::edgesGraph = Graph();
                    menus.emplace("dataset");
                    return;
                case 0:
                    quit = true;
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 4." << endl;
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
 * @brief Dataset Menu
 *
 * Complexity: ???
 */
void datasetMenu(){
    int op = 0;
    cout << endl << "----------------------------" << endl;
    cout << endl << "      Dataset Menu   " << endl;
    cout << endl << "----------------------------" << endl;
    cout << "1 - Toy-Graphs - shipping" << endl;
    cout << "2 - Toy-Graphs - stadiums" << endl;
    cout << "3 - Toy-Graphs - tourism" << endl;
    cout << "4 - Fully Connected - 25 edges" << endl;
    cout << "5 - Fully Connected - 50 edges" << endl;
    cout << "6 - Fully Connected - 75 edges" << endl;
    cout << "7 - Fully Connected - 100 edges" << endl;
    cout << "8 - Fully Connected - 200 edges" << endl;
    cout << "9 - Fully Connected - 300 edges" << endl;
    cout << "10 - Fully Connected - 400 edges" << endl;
    cout << "11 - Fully Connected - 500 edges" << endl;
    cout << "12 - Fully Connected - 600 edges" << endl;
    cout << "13 - Fully Connected - 700 edges" << endl;
    cout << "14 - Fully Connected - 800 edges" << endl;
    cout << "15 - Fully Connected - 900 edges" << endl;
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
                    csvInfo::createGraph(1);
                    menus.emplace("main");
                    return;
                case 2 :
                    csvInfo::createGraph(2);
                    menus.emplace("main");
                    return;
                case 3 :
                    csvInfo::createGraph(3);
                    menus.emplace("main");
                    return;
                case 4 :
                    csvInfo::createNodes(25);
                    csvInfo::createGraph(25);
                    menus.emplace("main");
                    return;
                case 5 :
                    csvInfo::createNodes(50);
                    csvInfo::createGraph(50);
                    menus.emplace("main");
                    return;
                case 6 :
                    csvInfo::createNodes(75);
                    csvInfo::createGraph(75);
                    menus.emplace("main");
                    return;
                case 7 :
                    csvInfo::createNodes(100);
                    csvInfo::createGraph(100);
                    menus.emplace("main");
                    return;
                case 8 :
                    csvInfo::createNodes(200);
                    csvInfo::createGraph(200);
                    menus.emplace("main");
                    return;
                case 9 :
                    csvInfo::createNodes(300);
                    csvInfo::createGraph(300);
                    menus.emplace("main");
                    return;
                case 10 :
                    csvInfo::createNodes(400);
                    csvInfo::createGraph(400);
                    menus.emplace("main");
                    return;
                case 11 :
                    csvInfo::createNodes(500);
                    csvInfo::createGraph(500);
                    menus.emplace("main");
                    return;
                case 12 :
                    csvInfo::createNodes(600);
                    csvInfo::createGraph(600);
                    menus.emplace("main");
                    return;
                case 13 :
                    csvInfo::createNodes(700);
                    csvInfo::createGraph(700);
                    menus.emplace("main");
                    return;
                case 14 :
                    csvInfo::createNodes(800);
                    csvInfo::createGraph(800);
                    menus.emplace("main");
                    return;
                case 15 :
                    csvInfo::createNodes(900);
                    csvInfo::createGraph(900);
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

//para testar (apagar no final)
/*void algo(){
    cout << "entrei no algo";
    AuxFunctions::test();
    over = true;
}*/


/**
 * @brief Backtracking Algorithm
 *
 * Complexity: O(n^3)
 */
void solveTSPBacktracking() {

    cout << "vertexSet size: " << csvInfo::edgesGraph.getVertexSet().size() << endl;
    auto startTime = std::chrono::high_resolution_clock::now(); // Start measuring time
    string startNode = "0";

    for (auto a : csvInfo::edgesGraph.getVertexSet()){
        a->setVisited(false);
    }

    vector<string> tour;
    vector<string> minTour;
    double min = INT_MAX;
    double tourDistance = 0;
    tour.push_back("0");

    AuxFunctions::backtrack(startNode, tour, csvInfo::edgesGraph, min, tourDistance, minTour);


    auto endTime = std::chrono::high_resolution_clock::now(); // Stop measuring time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;

    cout << endl;
    std::cout << "Time taken by Backtracking: "
            << minutes.count() << " minutes "
            << seconds.count() << " seconds "
            << duration.count() << " milliseconds "
            << duration.count() << " microseconds" << endl;
    cout << endl;
    cout << "Minimum Tour using Backtracking algorithm:" << endl;
    for (auto a : minTour) {
        cout << a << " ";

    } cout << endl;
    cout << "Distance: " << min << endl;
    over = true;
}



void tsp_2_approximation() {

    auto startTime = std::chrono::high_resolution_clock::now(); // Start measuring time

    std::vector<string> tour; ///< Stores nodes in the order they are visited in the tour.
    // Clear the tour vector
    tour.clear();

    vector<string> prim;
    // Create a minimum spanning tree (MST) of the graph
    AuxFunctions::primMST(prim);
    cout << "sai do prim" << endl;
    for (auto a : prim){
        Vertex* v = csvInfo::edgesGraph.findVertex(a);
        v->setVisited(false);
    }

    AuxFunctions::triangular("0", tour, prim);

    auto endTime = std::chrono::high_resolution_clock::now(); // Stop measuring time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;

    cout << endl;
    std::cout << "Time taken by Triangular Approximation Heuristic: "
              << minutes.count() << " minutes "
              << seconds.count() << " seconds "
              << duration.count() << " milliseconds "
              << duration.count() << " microseconds" << endl;
    cout << endl;

    double min = AuxFunctions::calculateTourDistance(tour, csvInfo::edgesGraph);

    for (auto a : tour) {
        if (!a.empty()) {
            cout << a << " ";
        } else {
            cout << "No tour found!" << endl;
        }
    } cout << endl;
    cout << "Distance: " << min << endl;

    over = true;
}

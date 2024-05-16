/**
 * @file main.cpp
 *
 * @mainpage DA project2
 * @section intro_sec Introduction
 * This project was made in the context of the Algorithm Design class.
 *
 * The goal of this assignment is twofold. First, implement a basic exhaustive approach for the
 * classic routing problem using the TSP abstraction, therefore learning first-hand that although
 * such an approach can find optimal solutions, its applicability is restricted to very small graphs.
 * Second, refine your critical thinking skills, by developing and analysing a set of approximate
 * solutions to the TSP.
 *
 * This project designs efficient algorithms to find optimal routes for vehicles in generic shipping and
 * delivery scenarios, from urban deliveries to ocean shipping. This problem corresponds to the TSP.
 * As the TSP is intractable, there are no known efficient algorithms to solve it.
 * Backtracking techniques can find the optimal solution to this problem.
 * If the graph is small, the application of these approaches might be reasonable.
 * However their application to large graphs is infeasible, due to their high computational complexity.
 *
 * This project was made by: Frederica Pereira (up202108167), Leonor Couto (up202205796) and Tomás Rodrigues (up202205749).
 */

#include <map>
#include <stack>
#include <chrono>
#include "AuxFunctions.h"




map<string, int> m = {{"dataset", 0}, {"main", 1},{"backtracking", 2}, {"triangular", 3}, {"otherTSP", 4},{"realWorld", 5},{"test", 6}};
stack<string> menus;
bool over = false;
bool quit = false;
int graphN = 0;

void clearMenus();

int main();
void mainMenu();
void datasetMenu();

void solveTSPBacktracking();
void tsp_2_approximation();
void tsp_otherheuristic();
void tsp_otherheuristicForRealWorld();
void teste();

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
int main(){
    menus.emplace("dataset");

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
                tsp_otherheuristic();
                break;
            case 5:
                tsp_otherheuristicForRealWorld();
                break;
            case 6:
                teste();
                break;
            default:
                quit = true;
        }
        if (over) {
            int op = 0;
            cout << endl;
            cout << "1 - Return to Main Menu" << endl;
            cout << "2 - Change dataset" << endl;
            cout << "0 - Exit." << endl;
            while (true) {
                cout << "Write the number of what you want to do: ";
                if (cin >> op) {
                    if (op == 1) {
                        clearMenus();
                        menus.emplace("main");
                        break;
                    }
                    else if (op == 2) {
                        clearMenus();
                        csvInfo::edgesGraph = Graph();
                        menus.emplace("dataset");
                        break;
                    }
                    else if (op == 0) {
                        quit = true;
                        break;
                    }
                    else {
                        cout << "Invalid number! The number should be 0, 1 or 2." << endl;
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
    cout << endl << "         Main Menu          " << endl;
    cout << endl << "----------------------------" << endl;
    if(graphN > 14){
        cout << "T2.1 - Backtracking Algorithm not possible for bigger graphs." << endl;
    } else {
        cout << "1 - T2.1 - Backtracking Algorithm." << endl;
    }
    cout << "2 - T2.2 - Triangular Approximation Heuristic." << endl;
    cout << "3 - T2.3 - Other Heuristic - Nearest Neighbor." << endl;
    cout << "4 - T2.4 - Other Heuristic - Nearest Neighbor - Choose start node." << endl;
    cout << "5 - Change dataset." << endl;
    cout << "6 - Print number of vertex and number edges." << endl;
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
                    if(graphN > 14){
                        cout << "Backtracking Algorithm not possible for bigger graphs." << endl;
                        menus.emplace("main");
                    } else {
                        menus.emplace("backtracking");
                    }
                    return;
                case 2 :
                    menus.emplace("triangular");
                    return;
                case 3 :
                    menus.emplace("otherTSP");
                    return;
                case 4 :
                    menus.emplace("realWorld");
                    return;
                case 5 :
                    csvInfo::edgesGraph = Graph();
                    menus.emplace("dataset");
                    return;
                case 6 :
                    menus.emplace("test");
                    return;
                case 0:
                    quit = true;
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 6." << endl;
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
    cout << "16 - Real-world Graphs - Graph 1" << endl;
    cout << "17 - Real-world Graphs - Graph 2" << endl;
    cout << "18 - Real-world Graphs - Graph 3" << endl;
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
                    csvInfo::createGraph(13);
                    graphN = 13;
                    menus.emplace("main");
                    return;
                case 2 :
                    csvInfo::createGraph(10);
                    graphN = 10;
                    menus.emplace("main");
                    return;
                case 3 :
                    csvInfo::createGraph(4);
                    graphN = 4;
                    menus.emplace("main");
                    return;
                case 4 :
                    csvInfo::createNodes(25);
                    csvInfo::createGraph(25);
                    graphN = 25;
                    menus.emplace("main");
                    return;
                case 5 :
                    csvInfo::createNodes(50);
                    csvInfo::createGraph(50);
                    graphN = 50;
                    menus.emplace("main");
                    return;
                case 6 :
                    csvInfo::createNodes(75);
                    csvInfo::createGraph(75);
                    graphN = 75;
                    menus.emplace("main");
                    return;
                case 7 :
                    csvInfo::createNodes(100);
                    csvInfo::createGraph(100);
                    graphN = 100;
                    menus.emplace("main");
                    return;
                case 8 :
                    csvInfo::createNodes(200);
                    csvInfo::createGraph(200);
                    graphN = 200;
                    menus.emplace("main");
                    return;
                case 9 :
                    csvInfo::createNodes(300);
                    csvInfo::createGraph(300);
                    graphN = 300;
                    menus.emplace("main");
                    return;
                case 10 :
                    csvInfo::createNodes(400);
                    csvInfo::createGraph(400);
                    graphN = 400;
                    menus.emplace("main");
                    return;
                case 11 :
                    csvInfo::createNodes(500);
                    csvInfo::createGraph(500);
                    graphN = 500;
                    menus.emplace("main");
                    return;
                case 12 :
                    csvInfo::createNodes(600);
                    csvInfo::createGraph(600);
                    graphN = 600;
                    menus.emplace("main");
                    return;
                case 13 :
                    csvInfo::createNodes(700);
                    csvInfo::createGraph(700);
                    graphN = 700;
                    menus.emplace("main");
                    return;
                case 14 :
                    csvInfo::createNodes(800);
                    csvInfo::createGraph(800);
                    graphN = 800;
                    menus.emplace("main");
                    return;
                case 15 :
                    csvInfo::createNodes(900);
                    csvInfo::createGraph(900);
                    graphN = 900;
                    menus.emplace("main");
                    return;
                case 16 :
                    csvInfo::createNodes(1000);
                    csvInfo::createGraph(1000);
                    graphN = 1000;
                    menus.emplace("main");
                    return;
                case 17 :
                    csvInfo::createNodes(5000);
                    csvInfo::createGraph(5000);
                    graphN = 5000;
                    menus.emplace("main");
                    return;
                case 18 :
                    csvInfo::createNodes(10000);
                    csvInfo::createGraph(10000);
                    graphN = 10000;
                    menus.emplace("main");
                    return;
                case 0:
                    quit = true;
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 15." << endl;
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
 * @brief Function to print the number of nodes and the number of edges
 *
 * Complexity: 0(n^2)
 */
void teste(){
    int n = 0;
    for (auto v : csvInfo::edgesGraph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            e->setTest(false);
        }
    }
    for (auto v : csvInfo::edgesGraph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            if (!e->isTest()) {
                n++;
                e->setTest(true);
            }
        }
    }

    cout << "Number of nodes: " << csvInfo::edgesGraph.getVertexSet().size() << endl;
    cout << "Number of edges: " << n << endl;
    over = true;
}


/**
 * @brief Backtracking Algorithm
 *
 * Complexity: O(n! * n^2)
 */
void solveTSPBacktracking() {
    auto startTime = chrono::high_resolution_clock::now();
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

    cout << "Minimum Tour using Backtracking algorithm:" << endl;
    for (auto a : minTour) {
        cout << a << " ";

    } cout << endl;
    cout << "Distance: " << min << endl;

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    auto minutes = chrono::duration_cast<chrono::minutes>(duration);
    duration -= minutes;
    auto seconds = chrono::duration_cast<chrono::seconds>(duration);
    duration -= seconds;
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration);
    duration -= milliseconds;

    cout << endl;
    cout << "Time taken by Backtracking: "
            << minutes.count() << " minutes "
            << seconds.count() << " seconds "
            << milliseconds.count() << " milliseconds "
            << duration.count() << " microseconds" << endl;
    cout << endl;

    over = true;
}


/**
 * @brief Executes the Triangular Approximation Heuristic for the TSP problem.
 *
 * Complexity: 0(n^3)
 */
void tsp_2_approximation() {
    auto startTime = chrono::high_resolution_clock::now();

    vector<string> tour;

    vector<string> prim;
    AuxFunctions::primMST(prim);


    for (auto a : prim){
        Vertex* v = csvInfo::edgesGraph.findVertex(a);
        v->setVisited(false);
    }

    tour.clear();
    tour.push_back("0");
    AuxFunctions::triangular("0", tour, prim);

    double min = AuxFunctions::calculateTourDistance(tour, csvInfo::edgesGraph, graphN);

    cout << "Minimum Tour using Triangular Approximation Heuristic algorithm:" << endl;
    for (auto a : tour) {
        if (!a.empty()) {
            cout << a << " ";
        } else {
            cout << "No tour found!" << endl;
        }
    } cout << endl;
    cout << "Distance: " << min << endl;

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    auto minutes = chrono::duration_cast<chrono::minutes>(duration);
    duration -= minutes;
    auto seconds = chrono::duration_cast<chrono::seconds>(duration);
    duration -= seconds;
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration);
    duration -= milliseconds;

    cout << endl;
    cout << "Time taken by Triangular Approximation Heuristic: "
              << minutes.count() << " minutes "
              << seconds.count() << " seconds "
              << milliseconds.count() << " milliseconds "
              << duration.count() << " microseconds" << endl;
    cout << endl;

    over = true;
}



/**
 * @brief Executes the nearest neighbor heuristic for the TSP problem.
 *
 * This function implements the nearest neighbor heuristic for solving the
 * Travelling Salesman Problem (TSP). It starts from a given node, then
 * iteratively selects the nearest unvisited node as the next node to visit.
 * The process is repeated until all nodes have been visited, and the tour
 * is complete.
 *
 * Complexity: O(n^2)
 */
void tsp_otherheuristic() {
    auto startTime = chrono::high_resolution_clock::now();
    string startNode = "0";

    for (auto a : csvInfo::edgesGraph.getVertexSet()){
        a->setVisited(false);
    }

    vector<string> tour;
    vector<string> minTour;
    double min = INT_MAX;


    AuxFunctions::other_heuristic(startNode, tour, csvInfo::edgesGraph, min, 0, minTour, graphN);


    auto endTime = chrono::high_resolution_clock::now(); // Stop measuring time
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    auto minutes = chrono::duration_cast<chrono::minutes>(duration);
    duration -= minutes;
    auto seconds = chrono::duration_cast<chrono::seconds>(duration);
    duration -= seconds;
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration);
    duration -= milliseconds;

    cout << endl;
    cout << "Time taken by Nearest Neighbor Heuristic algorithm: "
              << minutes.count() << " minutes "
              << seconds.count() << " seconds "
              << milliseconds.count() << " milliseconds "
              << duration.count() << " microseconds" << endl;
    cout << endl;
    over = true;
}


/**
 * @brief Executes the nearest neighbor heuristic for the TSP problem but allows user to choose start node.
 *
 * Complexity: O(n^2)
 */
void tsp_otherheuristicForRealWorld() {

    int op = 0;

    cout << endl << "Choose the starting node between 0 and " << graphN << endl;
    bool flag = true;
    while (flag) {
        cout << "Enter the node number: ";
        if (cin >> op) {
            cout << endl;
            cout << "Starting node : " << op << endl;
            cout << "Calculating ..." << endl;
            cout << endl;
           flag = false;
        }
        else {
            cout << "Invalid input! Please enter a valid Airport Code." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }


    auto startTime = chrono::high_resolution_clock::now();
    string startNode = to_string(op);

    for (auto a : csvInfo::edgesGraph.getVertexSet()){
        a->setVisited(false);
    }

    vector<string> tour;
    vector<string> minTour;
    double min = INT_MAX;

    AuxFunctions::other_heuristic(startNode, tour, csvInfo::edgesGraph, min, 0, minTour, graphN);

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    auto minutes = chrono::duration_cast<chrono::minutes>(duration);
    duration -= minutes;
    auto seconds = chrono::duration_cast<chrono::seconds>(duration);
    duration -= seconds;
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration);
    duration -= milliseconds;

    cout << endl;
    cout << "Time taken by Nearest Neighbor Heuristic for Real World Graphs algorithm: "
              << minutes.count() << " minutes "
              << seconds.count() << " seconds "
              << milliseconds.count() << " milliseconds "
              << duration.count() << " microseconds" << endl;
    cout << endl;
    over = true;
}

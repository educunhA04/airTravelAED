#include <iostream>
#include "menu.h"

using namespace std;


Menu::Menu() {
    cout << "----------------------------------------------" << "\n\n";
    cout << "Hello! Welcome to our flight management system!" << "\n\n";
    reader = new Reader();
}
void Menu::init() {
    string inp;
    while (true) {
        cout << "Select an option: " << "\n\n"
        << "1 -> Consult Info" << endl
        << "2 -> Consult Statistics" << endl
        << "E -> EXIT" << "\n\n"
        << "Option: ";
        cin >> inp;

        if (inp == "1") {information();}
        else if (inp == "2") {statistics();}
        else if (inp == "E" or inp == "e") {exit(0);}
        else {
            cout << "\n Insert a valid input. \n\n";
            cin.clear();
        }
    }
}

void Menu::airportTrafMax() { // airport with the biggest number of flights (also the count of flights) //
    Airport result;
    int count = 0;

    for(auto v : reader->getGraph().getVertexSet()){
        if(v->getAdj().size() > count){
            count = v->getAdj().size();
            result = v->getInfo();
        }
    }
    auto x = result.getName();
    auto y = result.getCode();
    auto a = result.getCountry();
    auto b = result.getCity();
    cout << "\nThe airport with the biggest number of flights is " << x << " (Code: "<< y << ") "
         << "located in: " << b << ", " << a << " with " << count << " flights." << endl;
    airportsStat();
}

void Menu::information() {
    string inp;
    while (true) {
        cout << "\n\n" << "Which information do you want to consult?" << endl
             << "Select a valid option: " << "\n\n"
             << "1 -> Airports list" << endl
             << "2 -> Airlines list" << endl
             << "B -> Back to the previous Menu \n\n"
             << "Option: ";
        cin >> inp;
        if (inp == "1") {
            showAirports();
        }
        else if (inp == "2") {
            showAirlines();
        }
        else if (inp == "B" or inp == "b") {
            init();
        }
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }
}
void Menu::showAirports() {
    cout << "\nNow showing all airports:" << endl;
    for (auto i : reader->getAirports()) {
        cout << "/ Code: " << i.getCode() << " / "
             << "Name: "<< i.getName() << " / "
             << "City: " << i.getCity() << " / "
             << "Country: " << i.getCountry() << " /" << endl;
    }
}
void Menu::showAirlines() {
    cout << "\nNow showing all airlines" << endl;
    for (auto i : reader->getAirlines()) {
        cout << "/ Code: " << i.getCode() << " / "
             << "Name: " << i.getName() << " / "
             << "Call Sign: " << i.getCall() << " / "
             << "Country: " << i.getCountry() << " /" << endl;
    }
}

void Menu::statistics() {
    string inp;
    while (true){
        cout << "\n\n" << "Within the following options, from which do you want to access to statistics?" << endl
             << "Select a valid option: " << "\n\n"
             << "1 -> All Airports" << endl
             << "2 -> A specific Airport" << endl
             << "3 -> The Flights" << endl
             << "4 -> A reachable Country" << endl
             << "B -> Back to the previous Menu \n\n"
             << "Option: ";
        cin >> inp;

        if(inp == "1") airportsStat();
        // if(inp == "2") specificAirport();
        // if(inp == "3") flights();
        // if(inp == "4") reachable();
        if (inp == "B" or inp == "b") init();
        else {
            cout << "\n Insert a valid input. \n\n";
            cin.clear();
        }
    }
}

void Menu::airportsStat() {
    string inp;
    while (true) {
        cout << "\n\n" << "Airports Statistics" << endl
             << "Select a valid option: " << "\n\n"
             << "1 -> Number of airports" << endl
             << "2 -> Airport with the greatest air traffic" << endl
             << "3 -> Important airports" << endl
             << "B -> Back to the previous Menu \n\n"
             << "Option: ";
        cin >> inp;

        if(inp == "1") numAirports();
        if(inp == "2") airportTrafMax();
        // if(inp == "3") importantAirport();
        if (inp == "B" or inp == "b") statistics();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }
}

void Menu::numAirports() {
    auto x = reader->getAirports().size();
    cout << "\nThere are " << x << " airports!" << endl;
    statistics();
}


void Menu::end() {
    cout << "----------------------------------------------" << endl;
}


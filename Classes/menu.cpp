#include <iostream>
#include "menu.h"

using namespace std;

string toUpperSTR(string str) { /// Function to convert a string to uppercase
    for (auto& elem : str) {
        elem = toupper(elem);
    }
    return str;
}

Menu::Menu() {
    cout << "\nHello! Welcome to our flight management system!" << "\n\n";
    reader = new Reader();
}
void Menu::init() {
    string inp;
    while (true) {
        cout << "# Select an option: #" << "\n\n"
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
        cout << "\n\n" << "# Which information do you want to consult? #" << endl
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
        cout << "| Code: " << i.getCode() << " | "
             << "Name: "<< i.getName() << " | "
             << "City: " << i.getCity() << " | "
             << "Country: " << i.getCountry() << " |" << endl;
    }
}
void Menu::showAirlines() {
    cout << "\nNow showing all airlines" << endl;
    for (auto i : reader->getAirlines()) {
        cout << "| Code: " << i.getCode() << " | "
             << "Name: " << i.getName() << " | "
             << "Call Sign: " << i.getCall() << " | "
             << "Country: " << i.getCountry() << " |" << endl;
    }
}

void Menu::statistics() {
    string inp;
    while (true){
        cout << "\n\n" << "# Within the following options, from which do you want to access to statistics? #" << endl
             << "Select a valid option: " << "\n\n"
             << "1 -> All Airports" << endl
             << "2 -> A specific Airport" << endl
             << "3 -> The Flights" << endl
             << "4 -> A reachable Country" << endl
             << "B -> Back to the previous Menu \n\n"
             << "Option: ";
        cin >> inp;

        if(inp == "1") airportsStat();
        if(inp == "2") specificAirport();
        // if(inp == "3") flights();
        // if(inp == "4") reachable();
        if (inp == "B" or inp == "b") init();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }
}

void Menu::airportsDest() { // printa a lista de aeroportos para o qual o aeroporto inp viaja
    string inp;
    cout << "\nInsert a valid Airport code: " << endl;
    cin >> inp;
    bool found = false;

    inp = toUpperSTR(inp);

    for(auto x : reader->getAirports()){
        if (x.getCode() == inp){
            found = true;
            break;
        }
    }
    if (!found){
        cout << "\nNo airport was found with code: " << inp << endl;
        airportsDest();
    }
    else {
        set<Airport> result = {};
        for(auto x : reader->getGraph().getVertexSet()){
            if (x->getInfo().getCode() == inp){
                auto y = x->getAdj();
                for(auto z : y){
                    result.insert(z.getDest()->getInfo());
                }
            }
        }
        cout << "The airport represented by the code " << inp << " has flights to the following airports:" << endl;
        auto it = result.begin();
        while(it != result.end()){
            auto a = *it;
            cout << "| Code: " << a.getCode() << " | "
                 << "Name: "<< a.getName() << " | " << endl;
            it++;
        }
        specificAirport();
    }
}

void Menu::numDest() {
    string inp;
    cout << "\nInsert a valid Airport code: " << endl;
    cin >> inp;
    bool found = false;

    inp = toUpperSTR(inp);

    for(auto x : reader->getAirports()){
        if (x.getCode() == inp){
            found = true;
            break;
        }
    }
    if (!found){
        cout << "\nNo airport was found with code: " << inp << endl;
        numDest();
    }
    else{
        set<string> result;
        for (auto x : reader->getGraph().getVertexSet()) {
            if (x -> getInfo().getCode() == inp) {
                auto y = x->getAdj();
                for(auto z : y){
                    auto a = z.getDest()->getInfo().getCode();
                    result.insert(a);
                }
            }
        }
        cout << "The airport represented by the code " << inp << " has flights to " << result.size() << " different destinations.";
        specificAirport();
    }
}
void Menu::citiesDest() {
    string inp;
    cout << "\nInsert a valid Airport code: " << endl;
    cin >> inp;
    bool found = false;

    inp = toUpperSTR(inp);

    for(auto x : reader->getAirports()){
        if (x.getCode() == inp){
            found = true;
            break;
        }
    }
    if (!found){
        cout << "\nNo airport was found with code: " << inp << endl;
        citiesDest();
    }
    else {
        set<string> cities;
        for(auto x : reader->getGraph().getVertexSet()){
            if(x->getInfo().getCode() == inp){
                auto adj = x->getAdj();
                for(auto c : adj){
                    auto i = c.getDest()->getInfo();
                    cities.insert(i.getCity());
                }
            }
        }
        cout << "The airport represented by the code " << inp << " has flights to the following cities: " << endl;
        auto it = cities.begin();
        while(it != cities.end()){
            auto a = *it;
            cout << "| " << a << " |" << endl;
            it++;
        }
        cout << endl;
        specificAirport();
    }
}

void Menu::countriesDest() {
    string inp;
    cout << "\nInsert a valid Airport code: " << endl;
    cin >> inp;
    bool found = false;

    inp = toUpperSTR(inp);

    for(auto x : reader->getAirports()){
        if (x.getCode() == inp){
            found = true;
            break;
        }
    }
    if (!found){
        cout << "\nNo airport was found with code: " << inp << endl;
        citiesDest();
    }
    else {
        set<string> countries;
        for(auto x : reader->getGraph().getVertexSet()){
            if(x->getInfo().getCode() == inp){
                auto adj = x->getAdj();
                for(auto c : adj){
                    auto i = c.getDest()->getInfo();
                    countries.insert(i.getCountry());
                }
            }
        }
        cout << "The airport represented by the code " << inp << " has flights to the following countries: " << endl;
        auto it = countries.begin();
        while(it != countries.end()){
            auto a = *it;
            cout << "| " << a << " |" << endl;
            it++;
        }
        cout << endl;
        specificAirport();
    }
}
void Menu::specificAirport() {
    string inp;
    while (true) {
        cout << "\n\n" << "# Specific Airport Statistics #" << endl
             << "Select a valid option: " << "\n\n"
             << "1 -> Number of avaiable destinations" << endl
             << "2 -> List of destination airports" << endl
             << "3 -> List of destination cities" << endl
             << "4 -> List of destination countries" << endl
             << "B -> Back to the previous Menu \n\n"
             << "Option: ";
        cin >> inp;

        if (inp == "1") numDest();
        if (inp == "2") airportsDest();
        if (inp == "3") citiesDest();
        if (inp == "4") countriesDest();
        if (inp == "b" or inp == "B") statistics();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }
}

void Menu::airportsStat() {
    string inp;
    while (true) {
        cout << "\n\n" << "# Airports Statistics #" << endl
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
    cout << "\nThere are " << x << " airports." << endl;
    statistics();
}


void Menu::end() {
    cout << "----------------------------------------------" << endl;
}


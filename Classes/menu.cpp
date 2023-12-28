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
        set<string> result2;
        for (auto x : reader->getGraph().getVertexSet()) {
            if (x -> getInfo().getCode() == inp) {
                auto y = x->getAdj();
                for(auto z : y){
                    auto a = z.getDest()->getInfo().getCode();
                    result.insert(a);
                    result2.insert(z.getDest()->getInfo().getCity());
                }
            }
        }
        cout << "The airport represented by the code " << inp << " has flights to " << result.size() << " different airports and "
             << result2.size() << " different cities.";
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

void Menu::numFlights() {
    int result = 0;
    for (auto x : reader->getGraph().getVertexSet()){
        auto y = x->getAdj();
        result += y.size();
    }
    cout << "There is a total of " << result << " different flights registered in our system.";
    flights();
}
void Menu::flightsAirport() { // 2 -> List of flights from an airport
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
        flightsAirport();
    }
    else{
        set<string> flight;
        for(auto v : reader->getGraph().getVertexSet()){
            if(v->getInfo().getCode() == inp){
                auto x = v->getAdj();
                for(auto y : x){
                    string result = "| Departure: " + inp + " | Arrival : " + y.getDest()->getInfo().getCode()
                                    + " | Airline: " + y.getAirline().getName() + " |";
                    flight.insert(result);
                }
            }
        }
        cout << "Now showing flights departing from the airport represented by the code: " << inp << ":" << endl;
        auto it = flight.begin();
        while(it != flight.end()){
            auto a = *it;
            cout << a << endl;
            it++;
        }
        flights();
    }
}
void Menu::flightsCountries() {
    string inp;
    cout << "\nInsert a valid city name: " << endl;
    cin >> inp;
    inp = toUpperSTR(inp);
    bool found = false;
    Vertex<Airport> * a;

    for(auto v : reader->getGraph().getVertexSet()){
        if(toUpperSTR(v->getInfo().getCountry()) == inp) {
            found = true;
        }
    }
    if (!found){
        cout << "\nCountry: " << inp << " not found."<< endl;
        flightsCountries();
    }
    else{
        set<string> result;
        for(auto v : reader->getGraph().getVertexSet()){
            if(toUpperSTR(v->getInfo().getCountry()) == inp) {
                auto a = v->getAdj();
                for(auto x : a){
                    string current;
                    current = "| Departure (Country / Airport): " + v->getInfo().getCountry() + " / " + v->getInfo().getCode() + " " +
                              "| Arrival (Country / Airport): " + x.getDest()->getInfo().getCountry() + " / " + x.getDest()->getInfo().getCode() + " " +
                              "| Airline: " + x.getAirline().getName() + " |";
                    result.insert(current);
                }
            }
        }
        auto it = result.begin();
        while(it != result.end()){
            auto q = *it;
            cout << q << endl;
            it++;
        }
    }
}
void Menu::flightsAirlines(){
    string inp;
    cout << "\nInsert a valid Airline code: " << endl;
    cin >> inp;
    inp = toUpperSTR(inp);
    bool found = false;
    string airline_name;
    for(auto x : reader->getAirlines()){
        if(inp == x.getCode()) {
            found = true;
            airline_name = x.getName();
        }
    }
    if(!found){
        cout << "No airline was found with code: " << inp << "." << endl;
        flightsAirlines();
    }
    if(found){
        set<string> result;
        for(auto v : reader->getGraph().getVertexSet()){
            auto adj = v->getAdj();
            for(auto a : adj){
                if (a.getAirline().getCode() == inp){
                    string current = "| Departure: " + v->getInfo().getCode() + " - " + v->getInfo().getCity() + " - " + v->getInfo().getCountry() + " "
                                     "| Arrival: " + a.getDest()->getInfo().getCode() + " - " + a.getDest()->getInfo().getCity() + " - " + a.getDest()->getInfo().getCountry() + " |";
                    result.insert(current);
                }
            }
        }
        cout << "The airline represented by the code " << inp << " (" << airline_name << ") is responsible for the following flights: " << endl;
        auto it = result.begin();
        while(it != result.end()){
            auto st = *it;
            cout << st << endl;
            it++;
        }
    }
}
void Menu::flightsCities() {
    string inp;
    cout << "\nInsert a valid city name: " << endl;
    cin >> inp;
    inp = toUpperSTR(inp);
    bool found = false;
    Vertex<Airport> * a;

    for(auto v : reader->getGraph().getVertexSet()){
        if(toUpperSTR(v->getInfo().getCity()) == inp) {
            found = true;
            a = v;
        }
    }

    if(!found){
        cout << "\nCity: " << inp << " not found."<< endl;
        flightsCities();
    }
    else{
        set<string> flight;
        auto b = a->getAdj();
        for(auto e : b){
            string result;
            result = "| Departure: " + a->getInfo().getCity() + " | Arrival: " + e.getDest()->getInfo().getCity() +
                    " | Airline: " + e.getAirline().getName() + " |";
            flight.insert(result);
        }
        cout << "Now showing flights departing from " << a->getInfo().getCity() << ":" << endl;
        auto it = flight.begin();
        while(it != flight.end()){
            auto n = *it;
            cout << n << endl;
            it++;
        }
        flights();
    }
}
void Menu::flights() {
    string inp;
    while (true) {
        cout << "\n\n" << "# Flight Statistics #" << endl
             << "Select a valid option: " << "\n\n"
             << "1 -> Total number of flights" << endl
             << "2 -> List of flights departed from an airport" << endl
             << "3 -> List of flights departed from a city" << endl
             << "4 -> List of flights departed from a country" << endl
             << "5 -> List of flights from an airline" << endl
             << "B -> Back to the previous Menu \n\n"
             << "Option: ";
        cin >> inp;
        if (inp == "1") numFlights();
        if (inp == "2") flightsAirport();
        if (inp == "3") flightsCities();
        if (inp == "4") flightsCountries();
        if (inp == "5") flightsAirlines();
        if (inp == "b" or inp == "B") statistics();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
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

void Menu::statistics() {
    string inp;
    while (true){
        cout << "\n\n" << "# Within the following options, from which do you want to access to statistics? #" << endl
             << "Select a valid option: " << "\n\n"
             << "1 -> All Airports" << endl
             << "2 -> A specific Airport" << endl
             << "3 -> The Flights" << endl
             << "4 -> A reachable Target" << endl
             << "B -> Back to the previous Menu \n\n"
             << "Option: ";
        cin >> inp;

        if(inp == "1") airportsStat();
        if(inp == "2") specificAirport();
        if(inp == "3") flights();
        //if(inp == "4") reachable();
        if (inp == "B" or inp == "b") init();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }
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
    airportsStat();
}
void Menu::end() {
    cout << "----------------------------------------------" << endl;
}


#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "menu.h"

using namespace std;

Menu::Menu() {
    cout << "\n                            Hello!               " << "\n ";
    cout << "           Welcome to our flight management system!" << "\n\n";
    cout << "            ______" << endl;
    cout << "            _\\ _~-\\___" << endl;
    cout << "=  = ==(____AED____" << endl;
    cout << "            \\_____\\___________________,-~~~~~~~`-.." << endl;
    cout << "            /     o O o o o o O O o o o o o o O o  |\\_" << endl;
    cout << "            `~-.__        ___..----..                  )" << endl;
    cout << "                  `---~~\\___________/------------`````" << endl;
    cout << "=  ===(_________D" << "\n\n";
    reader = new Reader();
}

void Menu::init() {
    string inp;
    while (true) {
        cout <<"##############################" << "\n"
             <<"#     Select an option:      #" << "\n"
             <<"#----------------------------#" << "\n"
             <<"#   1 -> Consult Info        #"<< '\n'
             <<"#   2 -> Consult Statistics  #" << "\n"
             <<"#   E -> EXIT                #" << "\n"
             <<"#                            #" << "\n"
             <<"##############################" << "\n\n"
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
//--------------------------------------INFO------------------------------------------//
void Menu::information() {
    string inp;
    while (true) {
        cout << "\n\n"   <<"#############################################" << endl
                         <<"# Which information do you want to consult? #" << endl
                         <<"#-------------------------------------------#"<< endl
                         <<"#         Select a valid option:            #" << "\n"
                         <<"#         1 -> Airports list                #"<< endl
                         <<"#         2 -> Airlines list                #" << endl
                         <<"#         B -> Back to the previous Menu    #"<<"\n"
                         <<"#                                           #"<< endl
                         <<"#############################################" << "\n\n"
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

    cout << "\n                      Now showing all airports                             " << endl;
    cout << "+------+--------------------------------+---------------------------+----------------------+" << endl;
    cout << "| Code |              Name              |            City           |        Country       |" << endl;
    cout << "+------+--------------------------------+---------------------------+----------------------+" << endl;

    for (auto i : reader->getAirports()) {
        cout << "| " << std::setw(4) << i.getCode() << " | "
             << std::setw(30) << i.getName() << " | "
             << std::setw(25) << i.getCity() << " | "
             << std::setw(20) << i.getCountry() << " |" << endl;
    }

    cout << "+------+--------------------------------+---------------------------+----------------------+" << endl;

}
void Menu::showAirlines() {
    cout << "\n                      Now showing all airlines                             " << endl;
    cout << "+------+-------------------------------+--------------------------+----------------------+" << endl;
    cout << "| Code |              Name             |         Call Sign        |        Country       |" << endl;
    cout << "+------+-------------------------------+--------------------------+----------------------+" << endl;

    for (auto i : reader->getAirlines()) {
        cout << "| " << std::setw(4) << i.getCode() << " | "
             << std::setw(30) << i.getName() << " | "
             << std::setw(25) << i.getCall() << " | "
             << std::setw(20) << i.getCountry() << " |" << endl;
    }

    cout << "+------+-------------------------------+--------------------------+----------------------+" << endl;
}


//--------------------------------STATISTICS----------------------------------------//

void Menu::statistics() {
    string inp;
    while (true) {
        cout << "\n\n"
             << "##############################################" << endl
             << "#      Within the following options, from    #" << endl
             << "#      which do you want to access to        #" << endl
             << "#      statistics?                           #" << endl
             << "#--------------------------------------------#" << endl
             << "#                                            #" << endl
             << "#        Select a valid option:              #" << "\n"
             << "#        1 -> All Airports                   #" << endl
             << "#        2 -> A specific Airport             #" << endl
             << "#        3 -> The Flights                    #" << endl
             << "#        4 -> A reachable Target             #" << endl
             << "#        B -> Back to the previous Menu      #" << "\n"
             << "#                                            #" << endl
             << "##############################################" << "\n\n"
             << "Option: ";
        cin >> inp;

        if (inp == "1") airportsStat();
        else if (inp == "2") specificAirport();
        else if (inp == "3") flights();
        else if (inp == "4") reachable();
        else if (inp == "B" || inp == "b") init();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }
}



string toUpperSTR(string str) { /// Function to convert a string to uppercase
    for (auto& elem : str) {
        elem = toupper(elem);
    }
    return str;
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
    cout << "\nThe airport with the biggest number of flights is " << x << " (Code: "<< y << ") "<< "located in: " << b << ", " << a << " with " << count << " flights." << endl;
    airportsStat();
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
        while (it != result.end()) {
            auto a = *it;
            cout << "+------+-------------------------------+" << endl;
            cout << "| Code |              Name             |" << endl;
            cout << "+------+-------------------------------+" << endl;
            cout << "| " << std::setw(4) << a.getCode() << " | "<< std::setw(30) << a.getName() << " |" << endl;
            cout << "+------+-------------------------------+" << endl;

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
        while (it != cities.end()) {
            auto a = *it;
            cout << "+----------------------+" << endl;
            cout << "| " << std::setw(20) << a << " |" << endl;
            cout << "+----------------------+" << endl;

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
        while (it != countries.end()) {
            auto a = *it;
            cout << "+----------------------+" << endl;
            cout << "| " << std::setw(20) << a << " |" << endl;
            cout << "+----------------------+" << endl;

            it++;
        }
        cout << endl;
        specificAirport();
    }
}

void Menu::numFlights() {
    int flightsresult = 0;
    for (auto x : reader->getGraph().getVertexSet()){
        auto y = x->getAdj();
        flightsresult += y.size();
    }
    int airlinesresult=0;
    set<string> airlines;
    for(auto vertex : reader->getGraph().getVertexSet()){
        auto currentadj = vertex->getAdj();
        for(auto it=currentadj.begin(); it!=currentadj.end();it++){
            airlines.insert(it->getAirline().getCode());
        }
    }
    airlinesresult=airlines.size();

    cout << "There is a total of " << flightsresult << " different flights from "<<airlinesresult<<" different airlines registered in our system."<<'\n';
    flights();
}


void Menu::flightsCountries() {
    string inp;
    cout << "\nInsert a valid country name: " << endl;
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
        set<tuple<string,string,string>> international;
        set<tuple<string,string,string>> domestic;
        for(auto v : reader->getGraph().getVertexSet()){
            if(toUpperSTR(v->getInfo().getCountry()) == inp) {
                auto adj = v->getAdj();
                for(auto current : adj){
                    if(current.getDest()->getInfo().getCountry() != inp){
                        auto prov=make_tuple(v->getInfo().getCity(),current.getDest()->getInfo().getCity(),current.getAirline().getName());
                        international.insert(prov);
                    }
                    else{
                        auto prov=make_tuple(v->getInfo().getCity(),current.getDest()->getInfo().getCity(),current.getAirline().getName());
                        domestic.insert(prov);
                    }
                }
            }
        }
        cout<<"The country represented by the code "<<inp<<" has "<<international.size()<<" international flights and "<<domestic.size()<<" domestic flights."<<'\n';
        cout<<"###################################################################"<<'\n';
        cout<<"#    Do you want to see:                                          #"<<'\n';
        cout<<"#-----------------------------------------------------------------#"<<endl;
        cout<<"#   1 -> The departing and arriving of the domestic flights       #"<<endl;
        cout<<"#   2 -> The departing and arriving of the international flights  #"<<endl;
        cout<<"#   B -> Back to the previous Menu                                #"<<endl;
        cout<<"#                                                                 #"<<endl;
        cout<<"###################################################################"<<'\n';
        int inp1;
        cin>>inp1;
        if(inp1==1){
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            cout << "|           Departure            |              Arrival           |        Airline       |" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            for(auto current : domestic){
                cout << "| " << std::setw(30) << get<0>(current) << " | "
                     << std::setw(30) << get<1>(current) << " | "
                     << std::setw(20) << get<2>(current) << " |" << endl;
                cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            }
        }
        else if(inp1==2){
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            cout << "|           Departure            |              Arrival           |        Airline       |" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            for(auto current : international){
                cout << "| " << std::setw(30) << get<0>(current) << " | "
                     << std::setw(30) << get<1>(current) << " | "
                     << std::setw(20) << get<2>(current) << " |" << endl;
                cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            }

        }
    }
}
void Menu::flightsAirlines() {
    string inp;
    cout << "\nInsert a valid Airline code: " << endl;
    cin >> inp;
    inp = toUpperSTR(inp);
    bool found = false;
    string airline_name;
    for (auto x: reader->getAirlines()) {
        if (inp == x.getCode()) {
            found = true;
            airline_name = x.getName();
        }
    }
    if (!found) {
        cout << "No airline was found with code: " << inp << "." << endl;
        flightsAirlines();
    }
    if (found) {
        set<tuple<string, string, string, string, string, string>> airlinesFlights;
        for (auto v: reader->getGraph().getVertexSet()) {
            auto adj = v->getAdj();
            for (auto current: adj) {
                if (current.getAirline().getCode() == inp) {
                    auto fly = make_tuple(v->getInfo().getCode(), v->getInfo().getCity(), v->getInfo().getCountry(),
                                          current.getDest()->getInfo().getCode(),
                                          current.getDest()->getInfo().getCity(),
                                          current.getDest()->getInfo().getCountry());
                    airlinesFlights.insert(fly);
                }
            }
        }
        cout << "The airline represented by the code " << inp << " (" << airline_name << ") is responsible for "
             << airlinesFlights.size() << " flights." << endl;
        cout << "#######################################################################"<<'\n';
        cout << "#  Do you want to see the airline " << inp << " is responsible?       #"<< '\n';
        cout << "#---------------------------------------------------------------------#"<<'\n';
        cout << "#  1-> yes                                                            #" << '\n';
        cout << "#  2-> no                                                             #" << '\n';
        cout << "#######################################################################" << '\n';

        int inp1;
        cin >> inp1;
        if (inp1 == 1) {
            cout<< "|----------------------------------------------------||----------------------------------------------------|"<< '\n';
            cout<< "|                   Departure                        ||                    Arriving                        |"<< '\n';
            cout<< "|----------------------------------------------------||----------------------------------------------------|"<< '\n';
            cout<< "|       Code      |       City      |     Country    ||       Code      |       City      |     Country    |"<< '\n';
            cout<< "|----------------------------------------------------||----------------------------------------------------|"<< '\n';

            for (const auto &flight: airlinesFlights) {
                cout << "| " << setw(16) << get<0>(flight) << " | "
                     << setw(16) << get<1>(flight) << " | "
                     << setw(16) << get<2>(flight) << " | "
                     << setw(16) << get<3>(flight) << " | "
                     << setw(16) << get<4>(flight) << " | "
                     << setw(16) << get<5>(flight) << " |" << '\n';
                cout<< "+-----------------+-----------------+----------------||-----------------+-----------------+----------------|"<< '\n';
            }
        }
        flights();
    }
}
void Menu::flightsCities() { //Number of flights per a city
    string inp;
    cout << "\nInsert a valid city name: " << endl;
    cin >> inp;
    inp = toUpperSTR(inp);
    bool found = false;
    Vertex<Airport> * airport;

    for(auto v : reader->getGraph().getVertexSet()){
        if(toUpperSTR(v->getInfo().getCity()) == inp) {
            found = true;
            airport= v;
        }
    }

    if(!found){
        cout << "\nCity: " << inp << " not found."<< endl;
        flightsCities();
    }
    cout<<"################################################################################################"<<endl;
    cout<<"#  Select an option:                                                                           #"<<'\n';
    cout<<"#----------------------------------------------------------------------------------------------#"<<endl;
    cout<<"#  1-> See the number of flights departing from the city and the respective airline            #"<<endl;
    cout<<"#  2-> See the number of flights arriving to the city and the respective airline               #"<<endl;
    cout<<"#  3-> See the number of flights departing and arriving to the city and the respective airline #"<<endl;
    cout<<"#  B-> Back to the previous menu                                                               #"<<endl;
    cout<<"#                                                                                              #"<<endl;
    cout<<"################################################################################################"<<endl;
    string option;
    cin>>option;
    if(option=="1"){
        set<string> flight;
        auto adj = airport->getAdj();
        int numdeparting=adj.size();
        cout<<"The number of flights departing from "<<airport->getInfo().getCity()<<" is "<<numdeparting<<"."<<'\n';
        cout<<"######################################################"<<'\n';
        cout<<"#    Do you want to see the flights departing from   #"<<'\n';
        cout<<"#    the city and the respective airline?            #"<<endl;
        cout<<"#----------------------------------------------------#"<<endl;
        cout<<"#   1 -> yes                                         #"<<endl;
        cout<<"#   2 -> no                                          #"<<endl;
        cout<<"#                                                    #"<<endl;
        cout<<"######################################################"<<'\n';
        int inp1;
        cin>>inp1;
        if(inp1==1){
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            cout << "|           Departure            |              Arrival           |        Airline       |" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            for(auto current : adj){
                cout << "| " << std::setw(30) << airport->getInfo().getCity() << " | "
                     << std::setw(30) << current.getDest()->getInfo().getCity() << " | "
                     << std::setw(20) << current.getAirline().getName() << " |" << endl;
                cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            }
        }
        flights();
    }
    else if(option=="2"){
        set<tuple<string,string,string>> flight;
        for(auto vertex : reader->getGraph().getVertexSet()){
            auto adj = vertex->getAdj();
            for(auto current : adj){
                if(current.getDest()->getInfo().getCity()==airport->getInfo().getCity()){
                    auto prov=make_tuple(vertex->getInfo().getCity(),current.getDest()->getInfo().getCity(),current.getAirline().getName());
                }
            }
        }
        cout<<"The number of flights arriving from "<<airport->getInfo().getCity()<<" is "<<flight.size()<<'\n';
        cout<<"######################################################"<<'\n';
        cout<<"#    Do you want to see the flights arriving from    #"<<'\n';
        cout<<"#    the city and the respective airline?            #"<<endl;
        cout<<"#----------------------------------------------------#"<<endl;
        cout<<"#   1 -> yes                                         #"<<endl;
        cout<<"#   2 -> no                                          #"<<endl;
        cout<<"#                                                    #"<<endl;
        cout<<"######################################################"<<'\n';
        int inp1;
        cin>>inp1;
        if(inp1==1){
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            cout << "|           Departure            |              Arrival           |        Airline       |" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            for(auto current : flight){
                cout << "| " << std::setw(30) << get<0>(current) << " | "
                     << std::setw(30) << get<1>(current) << " | "
                     << std::setw(20) << get<2>(current) << " |" << endl;
                cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            }
        }
        flights();
    }
    else if(option=="3"){
        set<tuple<string,string,string>> flight;
        for(auto vertex : reader->getGraph().getVertexSet()){
            auto adj = vertex->getAdj();
            for(auto current : adj){
                if(current.getDest()->getInfo().getCity()==airport->getInfo().getCity()){
                    auto prov=make_tuple(vertex->getInfo().getCity(),current.getDest()->getInfo().getCity(),current.getAirline().getName());
                }
            }
        }
        auto adj=airport->getAdj();
        for(auto current:adj){
            auto prov=make_tuple(airport->getInfo().getCity(),current.getDest()->getInfo().getCity(),current.getAirline().getName());
        }
        cout<<"The number of flights arriving and departing from "<<airport->getInfo().getCity()<<" is "<<flight.size()<<'\n\n';
        cout<<"######################################################"<<'\n';
        cout<<"#    Do you want to see the flights arriving from    #"<<'\n';
        cout<<"#    the city and the respective airline?            #"<<endl;
        cout<<"#----------------------------------------------------#"<<endl;
        cout<<"#   1 -> yes                                         #"<<endl;
        cout<<"#   2 -> no                                          #"<<endl;
        cout<<"#                                                    #"<<endl;
        cout<<"######################################################"<<'\n';
        int inp1;
        cin>>inp1;
        if(inp1==1){
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            cout << "|           Departure            |              Arrival           |        Airline       |" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            for(auto current : flight){
                cout << "| " << std::setw(30) << get<0>(current) << " | "
                     << std::setw(30) << get<1>(current) << " | "
                     << std::setw(20) << get<2>(current) << " |" << endl;
                cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            }
        }
        flights();
    }
    else if(option=="B" or option=="b"){
        flights();
    }
    else{
        cout<<"Invalid option"<<'\n';
        flightsCities();
    }
}
void Menu::flightsAirport() { // 2 -> Number of flights from an airport
    string inp;
    cout << "\nInsert a valid Airport code: " << endl;
    cin >> inp;
    bool found = false;

    inp = toUpperSTR(inp);

    for (auto x: reader->getAirports()) {
        if (x.getCode() == inp) {
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\nNo airport was found with code: " << inp << endl;
        flightsAirport();
    } else {

        set<tuple<string,string,string>> departing;
        set<tuple<string,string,string>> arriving;
        set<string> airlines;
        for (auto vertex: reader->getGraph().getVertexSet()) {
            if (vertex->getInfo().getCode() == inp) {
                auto adj = vertex->getAdj();
                for (auto current: adj) {
                    airlines.insert(current.getAirline().getName());
                    auto prov=make_tuple(vertex->getInfo().getCode(),current.getDest()->getInfo().getCode(),current.getAirline().getName());
                    departing.insert(prov);
                }
            }
            else{
                auto adj = vertex->getAdj();
                for (auto current: adj) {
                    if(current.getDest()->getInfo().getCode()==inp){
                        airlines.insert(current.getAirline().getName());
                        auto prov=make_tuple(vertex->getInfo().getCode(),current.getDest()->getInfo().getCode(),current.getAirline().getName());
                        arriving.insert(prov);
                    }
                }
            }
        }
        int departingflights=departing.size();
        int arrivingflights=arriving.size();

        cout << "The airport represented by the code " << inp << " has " << departingflights << "flights departing and " << arrivingflights << " flights arriving from " <<
             airlines.size() << " different airlines." << endl;

        cout <<"######################################################################################"<<'\n';
        cout <<"#    Do you want to see:                                                             #"<<'\n';
        cout <<"#------------------------------------------------------------------------------------#"<<endl;
        cout <<"#  1-> The flights departing from the airport and the respective airline.            # " << endl;
        cout <<"#  2-> The flights arriving to the airport and the respective airline.               #" << endl;
        cout <<"#  3-> The flights arriving and departing to the airport and the respective airline. #" << endl;
        cout <<"#  B-> Back to the previous menu.                                                    #" << endl;
        cout <<"######################################################################################"<< endl;
        int inp1;
        cin >> inp1;


        if (inp1 == 1) {
            cout << "Now showing flights departing from the airport represented by the code: " << inp << ":" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            cout << "|           Departure            |              Arrival           |        Airline       |" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;

            for (auto fly: departing){
                cout << "| " << std::setw(30) << get<0>(fly) << " | "
                     << std::setw(30) << get<1>(fly) << " | "
                     << std::setw(20) << get<2>(fly) << " |" << endl;
                cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            }
        }

        else if(inp1==2){
            cout << "Now showing flights arriving from the airport represented by the code: " << inp << ":" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            cout << "|           Departure            |              Arrival           |        Airline       |" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;

            for (auto fly: arriving){
                cout << "| " << std::setw(30) << get<0>(fly) << " | "
                     << std::setw(30) << get<1>(fly) << " | "
                     << std::setw(20) << get<2>(fly) << " |" << endl;
                cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            }
        }
        else if(inp1==3){
            auto compareFunction = [](const tuple<std::string, string, string>& a, const tuple<string, string, string>& b) {
                return get<0>(a) < get<0>(b);
            };
            set<tuple<string, string, string>, decltype(compareFunction)> allFlights(compareFunction);
            for (const auto& tuple : departing) {
                allFlights.insert(tuple);
            }

            for (const auto& tuple : arriving) {
                allFlights.insert(tuple);
            }

            cout << "Now showing flights departing and arriving from the airport represented by the code: " << inp << ":" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            cout << "|           Departure            |              Arrival           |        Airline       |" << endl;
            cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            for (auto fly: allFlights){
                cout << "| " << std::setw(30) << get<0>(fly) << " | "
                     << std::setw(30) << get<1>(fly) << " | "
                     << std::setw(20) << get<2>(fly) << " |" << endl;
                cout << "+--------------------------------+--------------------------------+----------------------+" << endl;
            }
        }
        flights();
    }
}


void Menu::reachableAirport() {
    string inp;
    cout << "\nInsert a valid airport IATA code: ";
    cin >> inp;
    inp = toUpperSTR(inp);
    set<Airport> visited;
    queue<Airport> q;

    for (auto i : reader->getAirports()) {
        if (i.getCode() == inp) {
            q.push(i);
            visited.insert(i);  // Mark the starting airport as visited
        }
    }

    while (!q.empty()) {
        Airport front = q.front();
        q.pop();

        for (auto vertex : reader->getGraph().getVertexSet()) {
            if (vertex->getInfo() == front) {
                auto adj = vertex->getAdj();

                for (auto edge : adj) {
                    Airport destAirport = edge.getDest()->getInfo();
                    if (visited.find(destAirport) == visited.end()) {
                        visited.insert(destAirport);
                        q.push(destAirport);
                    }
                }
            }
        }
    }

    cout << "The airport with code " << inp << " can reach " << visited.size() - 1 << " other airports.\n\n";



    string show;
    while (true) {
        cout << "Do you want to know to which airports you can reach?" << endl
             << "1 -> yes" << endl
             << "2 -> no\n\n"
             << "Option: ";

        cin >> show;
        if (show == "1") {
            cout << "\n\nList of airports: " << endl;
            for (auto x : visited) {
                if (x.getCode() != inp) {
                    cout << "| Code: " << x.getCode() << " | Name: " << x.getName() << endl;
                }
            }
            reachable();
        }
        if (show == "2") reachable();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }

}


void Menu::reachableCity() {
    string inp;
    string cityInp;
    cout << "\nInsert a valid airport IATA code: ";
    cin >> inp;
    inp = toUpperSTR(inp);
    set<string> visited;
    queue<string> q;

    for (auto i : reader->getAirports()) {
        if (i.getCode() == inp) {
            cityInp = i.getCity();
            q.push(cityInp);
            visited.insert(cityInp);
            break;
        }
    }

    while (!q.empty()) {
        string front = q.front();
        q.pop();

        for (auto vertex : reader->getGraph().getVertexSet()) {
            if (vertex->getInfo().getCity() == front) {
                auto adj = vertex->getAdj();

                for (auto edge : adj) {
                    string destCity = edge.getDest()->getInfo().getCity();
                    if (visited.find(destCity) == visited.end()) {
                        visited.insert(destCity);
                        q.push(destCity);
                    }
                }
            }
        }
    }

    cout << "The airport with code " << inp << " can reach " << visited.size() - 1 << " cities.\n\n";


    string show;
    while (true) {
        cout << "Do you want to know to which cities you can reach?" << endl
             << "1 -> yes" << endl
             << "2 -> no\n\n"
             << "Option: ";

        cin >> show;
        if (show == "1") {
            cout << "\n\nList of cities: " << endl;
            for (auto x : visited) {
                if (x != cityInp) {
                    cout << x << endl;
                }
                reachable();
            }
        }
        if (show == "2") reachable();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }

}

void Menu::reachableCountry() {
    string inp;
    string countryInp;
    cout << "\nInsert a valid airport IATA code: ";
    cin >> inp;
    inp = toUpperSTR(inp);
    set<string> visited;
    queue<string> q;

    for (auto i : reader->getAirports()) {
        if (i.getCode() == inp) {
            countryInp = i.getCountry();
            q.push(countryInp);
            visited.insert(countryInp);
            break;
        }
    }

    while (!q.empty()) {
        string front = q.front();
        q.pop();

        for (auto vertex : reader->getGraph().getVertexSet()) {
            if (vertex->getInfo().getCountry() == front) {
                auto adj = vertex->getAdj();

                for (auto edge : adj) {
                    string destCountry = edge.getDest()->getInfo().getCountry();
                    if (visited.find(destCountry) == visited.end()) {
                        visited.insert(destCountry);
                        q.push(destCountry);
                    }
                }
            }
        }
    }

    cout << "The airport with code " << inp << " can reach " << visited.size() - 1 << " countries.\n\n";


    string show;
    while (true) {
        cout << "Do you want to know to which countries you can reach?" << endl
             << "1 -> yes" << endl
             << "2 -> no\n\n"
             << "Option: ";

        cin >> show;
        if (show == "1") {
            cout << "\n\nList of countries: " << endl;
            for (auto x : visited) {
                if (x != countryInp) {
                    cout << x << endl;
                }
            }
            reachable();
        }
        if (show == "2") reachable();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }
}

string max_flights(unordered_map<string,int> &numberflights){
    int max=0;
    string maxairport;
    for(auto a: numberflights){
        if(a.second>max){
            max=a.second;
            maxairport=a.first;
        }
    }
    return maxairport;
}

void Menu::importantAirport() {
    set<string> topairports;
    unordered_map<string, int> numberflights;
    for (auto airport : reader->getGraph().getVertexSet()) {
        numberflights[airport->getInfo().getCode()]= airport->getAdj().size();
    }
    for( auto airport:reader->getGraph().getVertexSet()){
        auto adj=airport->getAdj();
        for(auto it=adj.begin(); it!=adj.end();it++){
            auto found=numberflights.find(it->getDest()->getInfo().getCode());
            if(found!=numberflights.end()){
                found->second=found->second+1;
            }
        }
    }
    unordered_map<string, int> copy=numberflights;
    for(auto a:numberflights){
        string deleteairport=max_flights(copy);
        topairports.insert(deleteairport);
        copy.erase(deleteairport);
    }
    cout<<"What is the top number of airports you want to see?"<<endl;
    cout<<"Insert number: ";
    int number;
    cin>>number;
    int i=0;
    for(auto a:topairports){
        if(i==number){
            break;
        }
        i++;
        for(auto airport:reader->getGraph().getVertexSet()){
            if(airport->getInfo().getCode()==a){
                cout<<i<<"º: "<<airport->getInfo().getCode()<<" | "<<airport->getInfo().getName()<<endl;
            }
        }
    }

}





//--------------------------------------------- MENUS ------------------------------------------------//
void Menu::flights() {
    string inp;
    while (true) {
    cout<<"\n\n"
             <<"################ Flight Statistics #############" << endl
             <<"#  Select a valid option:                      #" << "\n"
             <<"#----------------------------------------------#"<<endl
             <<"#  1 -> Total number of flights                #" << endl
             <<"#  2 -> Statics related to a airport           #" << endl
             <<"#  3 -> Statics related to a city              #" << endl
             <<"#  4 -> Statics related to a country           #" << endl
             <<"#  5 -> Statics related to a airline           #" << endl
             <<"#  B -> Back to the previous Menu              #"<<'\n'
             <<"#                                              #"<<endl
             <<"################################################"<<endl
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
            cout << "\n\n"
                 << "################ Specific Airport Statistics #################" << endl
                 << "#  Select a valid option:                                    #" << "\n"
                 << "#------------------------------------------------------------#"<<endl
                 << "#  1 -> Number of available destinations                     #" << endl
                 << "#  2 -> List of destination airports                         #" << endl
                 << "#  3 -> List of destination cities                           #" << endl
                 << "#  4 -> List of destination countries                        #" << endl
                 << "#  B -> Back to the previous Menu                            #"<<'\n'
                 << "#                                                            #"<<endl
                 << "##############################################################"<<endl
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


void Menu::reachable() {
    string inp;
    while (true) {
        cout << "\n\n"
             << "################# Reachable Statistics ###################" << endl
             << "#  Select a valid option:                                #" << "\n\n"
             << "#--------------------------------------------------------#"<<endl
             << "#  1 -> Reachable Airports                               #" << endl
             << "#  2 -> Reachable City                                   #" << endl
             << "#  3 -> Reachable Country                                #" << endl
             << "#  B -> Back to the previous Menu                        #"<<'\n'
             << "#                                                        #"<<endl
             << "##########################################################"<<endl
             << "Option: ";

        cin >> inp;

        if (inp == "1") reachableAirport();
        else if (inp == "2") reachableCity();
        else if (inp == "3") reachableCountry();
        else if (inp == "B" or inp == "b") statistics();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }
}




void Menu::airportsStat() {
    string inp;
    while (true) {
        cout << "\n\n"
             << "################## Airports Statistics ###################" << endl
             << "#  Select a valid option:                                #" << "\n"
             << "#--------------------------------------------------------#"<<endl
             << "#  1 -> Number of airports                               #" << endl
             << "#  2 -> Airport with the greatest air traffic            #" << endl
             << "#  3 -> Important airports                               #" << endl
             << "#  B -> Back to the previous Menu                        #"<<'\n'
             << "#                                                        #"<<endl
             << "##########################################################"<<endl
             << "Option: ";

        cin >> inp;

        if(inp == "1") numAirports();
        if(inp == "2") airportTrafMax();
        if(inp == "3") importantAirport();
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


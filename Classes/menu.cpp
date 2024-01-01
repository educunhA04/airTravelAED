#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "menu.h"
#include <cmath>
#include <algorithm>

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
             <<"#   1 -> Consult Info        #" << "\n"
             <<"#   2 -> Consult Statistics  #" << "\n"
             <<"#   3 -> Best Flight Option  #" << "\n"
             <<"#   E -> EXIT                #" << "\n"
             <<"#                            #" << "\n"
             <<"##############################" << "\n\n"
             << "Option: ";
        cin >> inp;

        if (inp == "1") {information();}
        else if (inp == "2") {statistics();}

        else if (inp == "3") {
            bestOption();
        }

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
//--------------------------------------BEST OPTION------------------------------------------//

double haversine(double lat1, double lon1, double lat2, double lon2) {
    //function to calculate the distance between two points
    const double R = 6371.0;

    lat1 = lat1 * M_PI / 180.0;
    lon1 = lon1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    lon2 = lon2 * M_PI / 180.0;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    double a = sin(dlat / 2.0) * sin(dlat / 2.0) +
               cos(lat1) * cos(lat2) * sin(dlon / 2.0) * sin(dlon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    double distance = R * c;

    return distance;
}
set<Airport> Menu::Coordinates() {
    cout << "What are the coordinates of the location?" << "\n";
    string inp;
    cout << "\nInsert a valid latitude: " << endl;
    cin >> inp;
    double lat = stod(inp);

    if (lat< -90.0 && lat > 90.0){
        cout << "Invalid latitude"<< "\n";
        Coordinates();
    }
    cout << "\nInsert a valid longitude: " << endl;
    cin >> inp;
    double lon = stod(inp);
    if(lon < -180.0 && lon > 180.0){
        cout << "Invalid longitude" << "\n";
        Coordinates();
    }

//---------------------------------Calculate the closest airport-----------------------------------//
    set<Airport> closestAirports;
    double minDistance=10000000;
    Airport closest;
    for (auto airport:reader->getAirports()){
        if (haversine(lat,lon,airport.getLatitude(),airport.getLongitude()) < minDistance) {
            minDistance = haversine(lat,lon,airport.getLatitude(),airport.getLongitude());
            closest = airport;
        }
    }
    closestAirports.insert(closest);
    for (auto airport:reader->getAirports()){
        if (haversine(lat,lon,airport.getLatitude(),airport.getLongitude()) == minDistance){
            closestAirports.insert(airport);
        }
    }
    return closestAirports;
}
set<Airport> Menu::city() {
    set<Airport> airports;
    cout<<"What is the city of the location?"<<'\n';
    string inp;
    cin>>inp;
    /*if(inp=="B" or inp=="b"){
        bestOptionSetter();
    }*/
    for(auto airport:reader->getAirports()){
        if(airport.getCity()==inp){
            airports.insert(airport);
        }
    }
    if(airports.empty()){
        cout << "No city was found with name " << inp << "." << "\n";
        city();
    }
    return airports;
}
set<Airport> Menu::AirportsChoice() {
    cout<<"What is the airport of the location?"<<'\n';
    string inp;
    cin>>inp;
    set<Airport> airports;
    /*if (inp == "B" or inp == "b"){
        bestOptionSetter();
    }*/
    for(auto airport:reader->getAirports()){
        if(airport.getCode()==inp){
            airports.insert(airport);
        }
    }
    if(airports.empty()){
        cout << "No airport was found with code " << inp << "." << "\n";
        AirportsChoice();
    }
    return airports;
}

void Menu::bestOptionSetter(set<string> &airlinesPreference, bool &minimumAirlines,bool &neutral, set<Airport> &departing,set<Airport> &destination){
    bool departingsubmenus = true;

    while(departingsubmenus) {
        string inp;
        cout << "\n\n"
             << "##############################################" << endl
             << "#         Choose your departing based on:    #" << endl
             << "#--------------------------------------------#" << endl
             << "#                                            #" << endl
             << "#        Select a valid option:              #" << "\n"
             << "#        1 -> Airport                        #" << endl
             << "#        2 -> City                           #" << endl
             << "#        3 -> Coordinates                    #" << endl
             << "#        B -> Back to the previous Menu      #" << "\n"
             << "#                                            #" << endl
             << "##############################################" << "\n\n"
             << "Option: ";

        cin >> inp;
        if (inp == "1") { departing = AirportsChoice(); departingsubmenus = false; }
        else if (inp == "2") { departing = city(); departingsubmenus = false;}
        else if (inp == "3") { departing = Coordinates(); departingsubmenus = false;}
        else if (inp == "B" || inp == "b") {information();}

        else {
            cout << "\nInsert a valid input. \n\n";
            departingsubmenus = true;
        }
    }

    bool destinationsubmenus = true;

    while(destinationsubmenus) {
        string inp1;
        cout << "\n\n"
             << "##############################################" << endl
             << "#      Choose your destination based on:     #" << endl
             << "#--------------------------------------------#" << endl
             << "#                                            #" << endl
             << "#        Select a valid option:              #" << "\n"
             << "#        1 -> Airport                        #" << endl
             << "#        2 -> City                           #" << endl
             << "#        3 -> Coordinates                    #" << endl
             << "#        B -> Back to the previous Menu      #" << "\n"
             << "#                                            #" << endl
             << "##############################################" << "\n\n"
             << "Option: ";

        cin >> inp1;

        if (inp1 == "1") {destination =AirportsChoice();destinationsubmenus=false;}
        else if (inp1 == "2") {destination = city();destinationsubmenus= false;}
        else if (inp1 == "3") {destination = Coordinates();destinationsubmenus= false;}
        else if (inp1 == "B" || inp1 == "b") information();
        else {
            cout << "\nInsert a valid input. \n\n";
            destinationsubmenus=true;
        }
    }


    string inp2;
    bool airlinessubmenu = true;
    while (airlinessubmenu) {
        cout << "##############################################" << endl
             << "#           Preferences in airlines          #" << endl
             << "#--------------------------------------------#" << "\n"
             << "#        1 -> Minimum number of airlines     #" << endl
             << "#        2 -> Neutral                        #" << endl
             << "#        3 -> Have a preference              #" << endl
             << "#                                            #" << endl
             << "##############################################" << "\n\n"
             << "Option: ";

        cin >> inp2;
        if (inp2 == "1") {
            minimumAirlines = true;
            airlinessubmenu = false;
        }
        else if (inp2 == "2"){
            neutral = true;
            airlinessubmenu = false;
        }

        else if (inp2 == "3"){
            bool found=false;
            cout<<"Insert the airlines the code of the airlines you have preference (insert 0 to stop): "<<'\n';
            string inp3;
            cin>>inp3;

            while(inp3 != "0"){
                for(auto airline:reader->getAirlines()){
                    if(airline.getCode()==inp2){
                        airlinesPreference.insert(inp2);
                        found=true;
                    }
                }

                if(!found){
                    cout << "No airline was found with code "<< inp2 << "." << "\n";
                }
            }
            airlinessubmenu=false;
        }
        else {
            cout << "\nInsert a valid input. \n\n";
            airlinessubmenu = true;
        }
    }
}
bool dfsFindPathsToNode(Vertex<Airport>* current, Vertex<Airport>* end, vector<Vertex<Airport>*>& currentPath, set<vector<Vertex<Airport>*>>& paths, set<Vertex<Airport>*>& visited) {
    visited.insert(current);
    currentPath.push_back(current);

    if (current == end) {
        paths.insert(currentPath);
    } else {
        for (auto flight : current->getAdj()) {
            auto next = flight.getDest();

            if (visited.find(next) == visited.end()) {
                dfsFindPathsToNode(next, end, currentPath, paths, visited);
            }
        }
    }

    visited.erase(current);
    currentPath.pop_back();
    return false;  // Always return false to continue the search for other paths
}
struct CompareVectors {
    bool operator()(const vector<Vertex<Airport>*>& lhs, const vector<Vertex<Airport>*>& rhs) const {
        return lhs.size() < rhs.size();
    }
};
void Menu::bestOption() {
    bool minimumAirlines = false;
    bool neutral = false;
    set<string> airlinesPreference;
    set<Airport> departing;
    set<Airport> destination;
    set<vector<Vertex<Airport> *>> paths;
    bestOptionSetter(airlinesPreference, minimumAirlines, neutral, departing, destination);

    auto provdeparting = departing.begin();
    auto provdestination = destination.begin();


    Vertex<Airport> *startVertex = reader->getGraph().findVertex(*provdeparting);
    Vertex<Airport> *endVertex = reader->getGraph().findVertex(*provdestination);
    /*
    for(auto it=departing.begin();it!=departing.end();it++){
        if(it!=departing.begin()){
            Vertex<Airport> *startVertex=reader->getGraph().findVertex(*it);
            Vertex<Airport> *endVertex=reader->getGraph().findVertex(*provdestination);
            vector<Vertex<Airport> *> currentPath;
            set<Vertex<Airport> *> visited;
            dfsFindPathsToNode(startVertex, endVertex, currentPath, paths, visited);
        }
    }*/
    //------------------------------------AQUI VAMOS TER TODOS OS PATHS POSSIVEIS----------------------//
    vector<Vertex<Airport> *> currentPath;
    set<Vertex<Airport> *> visited;
    dfsFindPathsToNode(startVertex, endVertex, currentPath, paths, visited);
    //----------------------------------------------------------------------------------------------//
    vector<vector<tuple<string, string, string>>> bestoptionsvectorfinal;
    set<vector<Vertex<Airport> *>, CompareVectors> leastStops;
    vector<Vertex<Airport> *> bestOptionflight;
    bestOptionflight = *paths.begin();
    //---------------------------------LEAST STOPS--------------------------------------//
    //-------------------------FALTA IMPLEMENTAR AS AIRLINES DESTE---------------------//
    if (neutral == true) {
        //------------------------VÊ QUAL A MELHOR OPÇÃO E AS OPÇÕES ESTÃO ORGANIZADAS POR NÚMERO DE AIRLINES-------------//
        for (auto path: paths) {
            if (path.size() < bestOptionflight.size()) {
                bestOptionflight = path;
            }
        }
        leastStops.insert(bestOptionflight);
        for (auto path: paths) {
            if (path.size() == bestOptionflight.size()) {
                leastStops.insert(path);
            }
        }
        vector<vector<tuple<string, string, string>>> bestoptionsvector;
        vector<tuple<string, string, string>> bestOptionN;
        vector<tuple<string, string, string>> prov;
        set<string> nairlines;
        int minimumsize;
        auto a = paths.begin();
        bestOptionN = airlinesChoiceMinimum(*paths.begin(), nairlines);
        for (auto path: paths) {
            nairlines.clear();
            prov = airlinesChoiceMinimum(path, nairlines);
            if (minimumsize > nairlines.size()) {
                bestOptionN = prov;
                minimumsize = nairlines.size();
            }
        }
        bestoptionsvector.push_back(bestOptionN);
        for (auto path: paths) {
            nairlines.clear();
            prov = airlinesChoiceMinimum(path, nairlines);
            if (minimumsize == nairlines.size()) {
                bestoptionsvector.push_back(prov);
            }
        }
        sort(bestoptionsvector.begin(), bestoptionsvector.end(),
             [](const auto &a, const auto &b) {
                 return a.size() < b.size();
             });

        bestoptionsvectorfinal=bestoptionsvector;
        //-------------------------By default vamos apresentar o menor número de airlines-------------------------------------//

    }
        //-------------------------MINIMUM NUMBER OF DIFFERENT AIRLINES ----------------------------------------//
    else if (minimumAirlines) {
        vector<vector<tuple<string, string, string>>> bestoptionsvector;
        vector<tuple<string, string, string>> bestOptionM;
        vector<tuple<string, string, string>> prov;
        set<string> nairlines;
        int minimumsize;
        auto a = paths.begin();
        bestOptionM = airlinesChoiceMinimum(*paths.begin(), nairlines);
        for (auto path: paths) {
            nairlines.clear();
            prov = airlinesChoiceMinimum(path, nairlines);
            if (minimumsize > nairlines.size()) {
                bestOptionM = prov;
                minimumsize = nairlines.size();
            }
        }
        bestoptionsvector.push_back(bestOptionM);
        for (auto path: paths) {
            nairlines.clear();
            prov = airlinesChoiceMinimum(path, nairlines);
            if (minimumsize == nairlines.size()) {
                bestoptionsvector.push_back(prov);
            }
        }

        //O VETOR ESTÁ ORGANIZADO PELO NÚMERO DE PARAGENS
        sort(bestoptionsvector.begin(), bestoptionsvector.end(),
             [](const auto &a, const auto &b) {
                 return a.size() < b.size();
             });

        bestoptionsvectorfinal=bestoptionsvector;
        //VETOR FINAL ORDENADO
    } else if (!airlinesPreference.empty()) {
        vector<vector<tuple<string, string, string>>> bestoptionsvector;
        vector<tuple<string, string, string>> bestOptionP;
        vector<tuple<string, string, string>> prov;
        set<string> nairlines;
        bestOptionP = airlinesChoicePreference(*paths.begin(), nairlines, airlinesPreference);
        int minimumsize = bestOptionP.size();
        for (auto path: paths) {
            prov = airlinesChoicePreference(path, nairlines, airlinesPreference);
            if (minimumsize > prov.size()) {
                bestOptionP = prov;
                minimumsize = nairlines.size();
            }
        }
        bestoptionsvector.push_back(bestOptionP);
        for (auto path: paths) {
            prov = airlinesChoicePreference(path, nairlines, airlinesPreference);
            if (minimumsize == prov.size()) {
                bestoptionsvector.push_back(prov);
            }
        }
        //O VETOR ESTÁ ORGANIZADO PELO NÚMERO DE PARAGENS
        sort(bestoptionsvector.begin(), bestoptionsvector.end(),
             [](const auto &a, const auto &b) {
                 return a.size() < b.size();
             });
        bestoptionsvectorfinal=bestoptionsvector;
    }
    cout << "The best option of flight for you is:" << '\n';
    for (auto path: bestoptionsvectorfinal) {
        cout << "########################################################################" << '\n';
        cout << "#          |       Departure       |        Arrival        |  Airline  #" << '\n';
        int i = 1;
        for (auto flight: path) {
            cout << "#--------------------------------------------------------------------#" << '\n';
            cout << "#  " << "Flight " << i << "| " << setw(21) << get<0>(flight) << " | " << setw(22) << get<1>(flight)<< "|" << setw(10) << get<2>(flight) << "#" << '\n';
            i++;
        }
        cout << "######################################################################" << '\n';
    }
}

set<string> Menu::airlinesAvailable( Vertex<Airport>* source, Vertex<Airport>* dest ) {
    set<string> airlines;
    for (auto it = source->getAdj().begin(); it != source->getAdj().end(); it++) {
        if (it->getDest() == dest){
            if(airlines.find(it->getAirline().getCode())==airlines.end()) {
                airlines.insert(it->getAirline().getCode());
            }
        }
    }
    return airlines;
}
//-----------------------------vê a melhor escolha por path----------------//
vector<tuple<string, string, string>>  Menu::airlinesChoiceMinimum(vector<Vertex<Airport>*> path, set<string> &nairlines ) {
    set<string> airlines;
    unordered_map<string, int> airlinesAvailableMap;

    //----------- Calcula a quantidade de cada airline em todas as possibilidades para o path--------------//
    for (auto i = 0; i < path.size() - 1; i++) {
        auto source = path[i];
        auto dest = path[i + 1];
        auto provairlinesavai = airlinesAvailable(source, dest);

        for (const auto& airline : provairlinesavai) {
            if (airlinesAvailableMap.find(airline) == airlinesAvailableMap.end()) {
                airlinesAvailableMap[airline] = 1;
            }
            else {
                airlinesAvailableMap[airline]++;
            }
        }
    }
    //---------------------------------------------------------------------------------------------------//
    //------------escolhe a melhor airline-------------------------//
    vector<tuple<string, string, string>> flightsWAirline;
    for (auto i = 0; i < path.size() - 1; i++) {
        auto source = path[i];
        auto dest = path[i + 1];
        auto provairlinesavai = airlinesAvailable(source, dest);

        struct CompareAirlines {
            const unordered_map<string, int>& airlinesAvailableMap;

            CompareAirlines(const unordered_map<string, int>& airlinesMap): airlinesAvailableMap(airlinesMap) {}

            bool operator()(const string& lhs, const string& rhs) const {
            return airlinesAvailableMap.at(lhs) < airlinesAvailableMap.at(rhs);
            }
        };

        set<string, CompareAirlines> sortedAirlines(provairlinesavai.begin(), provairlinesavai.end(), CompareAirlines(airlinesAvailableMap));
        string bestairline = *sortedAirlines.begin();
        flightsWAirline.push_back(make_tuple(source->getInfo().getCode(), dest->getInfo().getCode(), bestairline));
    }
    return flightsWAirline;
}
vector<tuple<string, string, string>>  Menu::airlinesChoicePreference(vector<Vertex<Airport>*> path, set<string> &nairlines ,set<string> airlinesPreference) {
    set<string> airlines;
    unordered_map<string, int> airlinesAvailableMap;

    // Calcula a quantidade de cada airline em todas as possibilidades para o path
    for (auto i = 0; i < path.size() - 1; i++) {
        auto source = path[i];
        auto dest = path[i + 1];
        auto provairlinesavai = airlinesAvailable(source, dest);

        for (const auto &airline: provairlinesavai) {
            if (airlinesAvailableMap.find(airline) == airlinesAvailableMap.end()) {
                airlinesAvailableMap[airline] = 1;
            } else {
                airlinesAvailableMap[airline]++;
            }
        }
    }
    vector<tuple<string, string, string>> flightsWAirlin;
    for (auto i = 0; i < path.size() - 1; i++) {
        auto source = path[i];
        auto dest = path[i + 1];
        auto provairlinesavai = airlinesAvailable(source, dest);
        unordered_map<string, int> airlinesPreferenceMap;
        set<string> airlinesPreferenceAvai;
        for (auto it = airlinesAvailableMap.begin(); it != airlinesAvailableMap.end(); it++) {
            if (airlinesPreference.find(it->first) != airlinesPreference.end()) {
                airlinesPreferenceAvai.insert(it->first);
                airlinesPreferenceMap[it->first] = it->second;
            }
        }
        struct CompareAirlinesPreference {
            const unordered_map<string, int> &airlinesPreferenceMap;

            CompareAirlinesPreference(const unordered_map<string, int> &airlinesMap) : airlinesPreferenceMap(
                    airlinesMap) {}

            bool operator()(const string &lhs, const string &rhs) const {
                return airlinesPreferenceMap.at(lhs) < airlinesPreferenceMap.at(rhs);
            }
        };
        set<string, CompareAirlinesPreference> sortedPreferenceAirlines(airlinesPreferenceAvai.begin(),
                                                                        airlinesPreferenceAvai.end(),
                                                                        CompareAirlinesPreference(
                                                                                airlinesPreferenceMap));
        vector<string> SortedAirlines;
        for (auto p: sortedPreferenceAirlines) {
            SortedAirlines.push_back(p);
        }
        unordered_map<string, int> airlinesAvaiWOP;
        set<string> airlinesAvai;
        for (auto it = airlinesAvailableMap.begin(); it != airlinesAvailableMap.end(); it++) {
            if (airlinesPreference.find(it->first) == airlinesPreference.end()) {
                airlinesAvaiWOP[it->first] = it->second;
                airlinesAvai.insert(it->first);

            }
        }
        struct CompareAirline {
            const unordered_map<string, int> &airlinesAvaiWOP;

            CompareAirline(const unordered_map<string, int> &airlinesMap) : airlinesAvaiWOP(airlinesMap) {}

            bool operator()(const string &lhs, const string &rhs) const {
                return airlinesAvaiWOP.at(lhs) < airlinesAvaiWOP.at(rhs);
            }
        };
        set<string, CompareAirline> sortedAirlinesAvai(airlinesAvai.begin(), airlinesAvai.end(),
                                                       CompareAirline(airlinesAvaiWOP));
        for (auto a: sortedAirlinesAvai) {
            SortedAirlines.push_back(a);
        }
        auto bestairline = *SortedAirlines.begin();
        flightsWAirlin.push_back(make_tuple(source->getInfo().getCode(), dest->getInfo().getCode(), bestairline));
    }
    return flightsWAirlin;
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
    for (auto &elem: str) {
        elem = toupper(elem);
    }
    return str;
}

//--------------------------------------------- FLIGHTS STATISTIC ------------------------------------------------//
void Menu::flights() {
    string inp;
    while (true) {
    cout<<"\n\n"
             <<"################ Flight Statistics ##############" << endl
             <<"#  Select a valid option:                       #" << "\n"
             <<"#-----------------------------------------------#"<<endl
             <<"#  1 -> Total number of flights                 #" << endl
             <<"#  2 -> Statistics related to a airport         #" << endl
             <<"#  3 -> Statistics related to a city            #" << endl
             <<"#  4 -> Statistics related to a country         #" << endl
             <<"#  5 -> Statistics related to a airline         #" << endl
             <<"#  6 -> Maximum trip (greatest number of stops) #" << endl
             <<"#  B -> Back to the previous Menu               #" << endl
             <<"#                                               #" << endl
             <<"#################################################" << endl
             << "Option: ";
        cin >> inp;
        if (inp == "1") numFlights();
        if (inp == "2") flightsAirport();
        if (inp == "3") flightsCities();
        if (inp == "4") flightsCountries();
        if (inp == "5") flightsAirlines();
        if (inp == "6") maxFlight();
        if (inp == "b" or inp == "B") statistics();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
    }
}
void Menu::dfsVisit(Vertex<Airport>* v, int currentStops, set<tuple<Airport, Airport, int>>& stopPairs, Vertex<Airport>* v2) {
    v->setVisited(true);
    for (auto edge : v->getAdj()) {
        auto dest = edge.getDest();
        if (!dest->isVisited()) {
            currentStops++;
            dfsVisit(dest, currentStops, stopPairs, v2);
        }
        stopPairs.insert({v2->getInfo(), dest->getInfo(), currentStops + 1});
    }
}
void Menu::maxFlight() {
    string inp;
    while (true) {
        cout<<"\n\n"
            <<"################ Flight Statistics ##############" << endl
            <<"#  Select a valid option:                       #" << endl
            <<"#-----------------------------------------------#" << endl
            <<"#  1 -> All the airports                        #" << endl
            <<"#  2 -> Specific airport                        #" << endl
            <<"#  B -> Back to the previous Menu               #" << endl
            <<"#                                               #" << endl
            <<"#################################################" << endl
            << "Option: ";
        cin >> inp;

        if (inp == "1") {
            set<tuple<Airport, Airport, int>> stopPairs;
            vector<Vertex<Airport> *> allAirports = reader->getGraph().getVertexSet();

            for (auto airport : allAirports) {
                airport->setVisited(false);
            }

            for (auto airport: allAirports) {
                dfsVisit(airport,0, stopPairs, airport);
            }


            cout << "The maximum trip, with the greatest number of stops is: \n";
            string partida;
            string destino;
            int stops;
            int max = 0;
            for (auto p : stopPairs) {
                stops = get<2>(p);
                if (stops > max) {
                    partida = get<0>(p).getName();
                    destino = get<1>(p).getName();
                    max = stops;
                }
            }

            cout << partida << " --> " << destino << " | stops: " << max << endl;
        }

        else if (inp == "2") {
            string inp;
            cout << "\nInsert a valid airport IATA code: ";
            cin >> inp;
            inp = toUpperSTR(inp);
            bool found = false;

            for (auto i: reader->getAirports()) {
                if (i.getCode() == inp) {
                    found = true;
                }
            }

            if (!found) {
                cout << "\nNo airport was found with code: " << inp << endl;
                maxFlight();
            }

            set<tuple<Airport, Airport, int>> stopPairs;
            vector<Vertex<Airport> *> allAirports = reader->getGraph().getVertexSet();
            Vertex<Airport>* air;
            for (auto airport : allAirports) {
                airport->setVisited(false);
                if (airport->getInfo().getCode() == inp) {
                    air = airport;
                }

            }


            dfsVisit(air,0, stopPairs, air);


            cout << "The maximum trip, with the greatest number of stops is: \n";
            string partida;
            string destino;
            int stops;
            int max = 0;
            for (auto p : stopPairs) {
                stops = get<2>(p);
                if (stops > max) {
                    partida = get<0>(p).getName();
                    destino = get<1>(p).getName();
                    max = stops;
                }
            }

            cout << partida << " --> " << destino << " | stops: " << max << endl;
        }

        else if (inp == "b" or inp == "B") statistics();
        else {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
        }
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
            if(domestic.size()==0){
                cout<<"There are no domestic flights departing or arriving from "<<inp<<"."<<'\n';
                flights();
            }
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
            if(international.size()==0){
                cout<<"There are no international flights departing or arriving from "<<inp<<"."<<'\n';
                flights();
            }
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
        cout << "#  Do you want to see the flights " << inp << " is responsible?       #"<< '\n';
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
            if(numdeparting==0){
                cout<<"There are no flights departing from the city represented by the code "<<inp<<"."<<'\n';
                flights();
            }
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
            if(flight.size()==0){
                cout<<"There are no flights arriving from the city represented by the code "<<inp<<"."<<'\n';
                flights();
            }
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
        cout<<"The number of flights arriving and departing from "<<airport->getInfo().getCity()<<" is "<<flight.size()<<"\n\n";
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
            if(flight.size()==0){
                cout<<"There are no flights arriving or departing from the city represented by the code "<<inp<<"."<<'\n';
                flights();
            }
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

        cout << "The airport represented by the code " << inp << " has " << departingflights << " flights departing and " << arrivingflights << " flights arriving from " <<
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
            if(departingflights==0){
                cout<<"There are no flights departing from the airport represented by the code "<<inp<<"."<<'\n';
                flights();
            }
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
            if(arrivingflights==0){
                cout<<"There are no flights arriving to the airport represented by the code "<<inp<<"."<<'\n';
                flights();
            }
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
            if(arrivingflights==0 and departingflights==0){
                cout<<"There are no flights arriving or departing to the airport represented by the code "<<inp<<"."<<'\n';
                flights();
            }
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
//nOTA: NÃO ESQUECER DE POR A OPCAO DE NÃO EXISTRIREM ARRIVINGS/DEPARTINGS
//---------------------------------------------SPECIFIC AIRPORT------------------------------------------------//
void Menu::specificAirport() {
        string inp;
        while (true) {
            cout << "\n\n"
                 << "################ Specific Airport Statistics #################" << endl
                 << "#  Do you want to see:                                       #" << "\n"
                 << "#------------------------------------------------------------#"<<endl
                 << "#  1 -> Number of available destinations                     #" << endl
                 << "#  2 -> Number of available destination airport              #" << endl
                 << "#  3 -> Number of available destination countries            #" << endl
                 << "#  4 -> Number of available destination cities               #" << endl
                 << "#  B -> Back to the previous Menu                            #" << endl
                 << "#                                                            #" << endl
                 << "##############################################################" << endl
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
void Menu::numDest() {
    string inp;
    cout << "\nInsert a valid Airport code: " << endl;
    cin >> inp;
    bool found = false;
    if(inp=="B" or inp=="b"){
        specificAirport();
    }
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
        set<string> cities;
        set<string> countries;
        set<string> airports;
        for (auto vertex : reader->getGraph().getVertexSet()) {
            if (vertex-> getInfo().getCode() == inp) {
                auto adj = vertex->getAdj();
                for(auto current : adj){
                    auto city= current.getDest()->getInfo().getCity();
                    auto country= current.getDest()->getInfo().getCountry();
                    auto airport= current.getDest()->getInfo().getCode();
                    cities.insert(city);
                    countries.insert(country);
                    airports.insert(airport);
                }
            }
        }
        cout << "----------------------------------------------------------------------"<<'\n';
        cout << "|  The airport represented by the code " << inp << " has flights to : |" <<"\n";
        cout << "|                                                                     |" <<"\n"
             << "|   -> "<<airports.size() << " different airports ;                   |"<<'\n';
        cout << "|   -> "<<airports.size() << " different airports ;                   |"<<'\n';
        cout << "|   -> "<<countries.size() << " different countries ;                 | "<<'\n';
        cout << "|   -> "<<cities.size() << " different cities ;                       |"<<'\n';
        cout << "----------------------------------------------------------------------"<<'\n';
        specificAirport();
    }
}
void Menu::airportsDest() { // printa a lista de aeroportos para o qual o aeroporto inp viaja
    string inp;
    cout << "\nInsert a valid Airport code: " << endl;
    cin >> inp;
    bool found = false;

    if(inp=="B" or inp=="b"){
        specificAirport();
    }

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
        set<Airport> airports;
        for(auto vertex : reader->getGraph().getVertexSet()){
            if (vertex->getInfo().getCode() == inp){
                auto adj = vertex->getAdj();
                for(auto current : adj){
                    airports.insert(current.getDest()->getInfo());
                }
            }
        }
        cout << "The airport represented by the code " << inp << " has flights to"<< airports.size()<<" different airports." << endl;
        cout<<"###################################################################"<<'\n';
        cout<<"#    Do you want to see the list of destination airports?         #"<<'\n';
        cout<<"#-----------------------------------------------------------------#"<<endl;
        cout<<"#   1 -> yes                                                      #"<<endl;
        cout<<"#   2 -> no                                                       #"<<endl;
        cout<<"#                                                                 #"<<endl;
        cout<<"###################################################################"<<'\n';
        int inp1;
        cin>>inp1;
        if (inp1==1) {
            for (auto airport: airports) {
                cout << "+------+-------------------------------+" << endl;
                cout << "| Code |              Name             |" << endl;
                cout << "+------+-------------------------------+" << endl;
                cout << "| " << std::setw(4) << airport.getCode() << " | " << std::setw(30) << airport.getName() << " |"
                     << endl;
                cout << "+------+-------------------------------+" << endl;
            }
        }
        specificAirport();
    }
}
void Menu::citiesDest() {
    string inp;
    cout << "\nInsert a valid Airport code: " << endl;
    cin >> inp;
    bool found = false;
    if(inp=="B" or inp=="b"){
        specificAirport();
    }
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
        cout << "The airport represented by the code " << inp << " has flights to "<< cities.size()<<"different cities. " << endl;
        cout<<"###################################################################"<<'\n';
        cout<<"#    Do you want to see the list of destination cities?           #"<<'\n';
        cout<<"#-----------------------------------------------------------------#"<<endl;
        cout<<"#   1 -> yes                                                      #"<<endl;
        cout<<"#   2 -> no                                                       #"<<endl;
        cout<<"#                                                                 #"<<endl;
        cout<<"###################################################################"<<'\n';
        int inp1;
        cin>>inp1;
        if (inp1==1) {
            for (auto city: cities) {
                cout << "+----------------------+" << endl;
                cout << "| " << std::setw(20) << city << " |" << endl;
                cout << "+----------------------+" << endl;
            }
        }
        specificAirport();
    }
}
void Menu::countriesDest() {
    string inp;
    cout << "\nInsert a valid Airport code: " << endl;
    cin >> inp;
    bool found = false;
    if(inp=="B" or inp=="b"){
        specificAirport();
    }
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
        cout << "The airport represented by the code " << inp << " has flights to "<< countries.size()<<" different countries." << endl;
        cout<<"###################################################################"<<'\n';
        cout<<"#    Do you want to see the list of destination countries?        #"<<'\n';
        cout<<"#-----------------------------------------------------------------#"<<endl;
        cout<<"#   1 -> yes                                                      #"<<endl;
        cout<<"#   2 -> no                                                       #"<<endl;
        cout<<"#                                                                 #"<<endl;
        cout<<"###################################################################"<<'\n';
        int inp1;
        cin>>inp1;
        if (inp1==1) {
            for (auto country: countries) {
                cout << "+----------------------+" << endl;
                cout << "| " << std::setw(20) << country << " |" << endl;
                cout << "+----------------------+" << endl;
            }
        }
        specificAirport();
    }
}
//------------------------------------------------------------------------------------------------------------//

//---------------------------------------------REACHABLE STATISTICS-------------------------------------------//

void Menu::reachable() {
    string inp;
    while (true) {
        cout << "\n\n"
             << "################# Reachable Statistics ###################" << endl
             << "#  Select a valid option:                                #" << "\n\n"
             << "#--------------------------------------------------------#" << endl
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
void dfsVistidAdj(Vertex<Airport> *v, queue<Airport> &prov2, set<Airport> visited){
    for (auto edge : v->getAdj()) {
        if (visited.find(edge.getDest()->getInfo()) == visited.end()) {
            visited.insert(edge.getDest()->getInfo());
            prov2.push(edge.getDest()->getInfo());
        }
    }
}
void Menu::reachableAirport() {
    string inp;
    cout << "\nInsert a valid airport IATA code: ";
    cin >> inp;
    bool found = false;
    inp = toUpperSTR(inp);
    if (inp == "B" or inp == "b"){
        reachable();
    }
    Airport source;
    for(auto x : reader->getAirports()){
        if (x.getCode() == inp){
            source = x;
            found = true;
            break;
        }
    }
    if (!found){
        cout << "\nNo airport was found with code: " << inp << endl;
        reachableAirport();
    }
    cout << "#####################################################"<<'\n';
    cout << "#  How many lay-overs do you want to do?            #"<<'\n';
    cout << "#####################################################"<<endl;
    cout << "Number of lay-overs: ";
    int inp1;
    cin >> inp1;


    if (inp1 < 0) {
            cout << "\nInsert a valid input. \n\n";
            cin.clear();
            reachableAirport();
    }
    else {
            int distance=inp1+1;
            int currentDistance=0;
            queue<Airport> prov1;
            queue<Airport> prov2;
            queue<Airport> final;
            set<Airport> visited;
            visited.insert(source);
            final.push(source);
            prov1=final;
            while(currentDistance<distance){
                while(!prov1.empty()){
                    Airport current=prov1.front();
                    prov1.pop();
                    dfsVistidAdj(reader->getGraph().findVertex(current),prov2,visited);
                }
                currentDistance++;
                final=prov2;
                prov1=prov2;
                queue<Airport> emptyQueue;
                prov2.swap(emptyQueue);
            }
            set<Airport> finalSet;
            while(!final.empty()){
                auto add=final.front();
                final.pop();
                finalSet.insert(add);
            }
            cout<<"The airport represented by the code "<<inp<<" can reach "<<finalSet.size()<<" airports with "<< inp1 <<" lay-overs"<<'\n';
            if(finalSet.size()==0){reachable();}
            cout<<"###################################################################"<<'\n';
            cout<<"#    Do you want to see the list of reachable airports?           #"<<'\n';
            cout<<"#-----------------------------------------------------------------#"<<endl;
            cout<<"#   1 -> yes                                                      #"<<endl;
            cout<<"#   2 -> no                                                       #"<<endl;
            cout<<"#                                                                 #"<<endl;
            cout<<"###################################################################"<<'\n';
            int inp2;
            cin>>inp2;
            if (inp2==1) {
                    cout << "+------+-------------------------------+" << endl;
                    cout << "| Code |              Name             |" << endl;
                    cout << "+------+-------------------------------+" << endl;
                for (auto airport: finalSet) {
                    cout << "| " << std::setw(4) << airport.getCode() << " |" << std::setw(30) << airport.getName() << " |"<< endl;
                    cout << "+------+-------------------------------+" << endl;
                }
            }
            reachable();
        }
}
void Menu::reachableCity() {
    string inp;
    cout << "\nInsert a valid airport IATA code: ";
    cin >> inp;
    bool found = false;
    inp = toUpperSTR(inp);
    if (inp == "B" or inp == "b"){
        reachable();
    }
    Airport source;
    for(auto x : reader->getAirports()){
        if (x.getCode() == inp){
            source = x;
            found = true;
            break;
        }
    }
    if (!found){
        cout << "\nNo airport was found with code: " << inp << endl;
        reachableAirport();
    }
    cout << "#####################################################"<<'\n';
    cout << "#  How many lay-overs do you want to do?            #"<<'\n';
    cout << "#####################################################"<<endl;
    cout << "Number of lay-overs: ";
    int inp1;
    cin >> inp1;


    if (inp1 < 0) {
        cout << "\nInsert a valid input. \n\n";
        cin.clear();
        reachableAirport();
    }
    else {
        int distance=inp1+1;
        int currentDistance=0;
        queue<Airport> prov1;
        queue<Airport> prov2;
        queue<Airport> final;
        set<Airport> visited;
        visited.insert(source);
        final.push(source);
        prov1=final;
        while(currentDistance<distance){
            while(!prov1.empty()){
                Airport current=prov1.front();
                prov1.pop();
                dfsVistidAdj(reader->getGraph().findVertex(current),prov2,visited);
            }
            currentDistance++;
            final=prov2;
            prov1=prov2;
            queue<Airport> emptyQueue;
            prov2.swap(emptyQueue);
        }
        set<string> finalSetCities;
        while(!final.empty()){
            auto add=final.front();
            final.pop();
            auto city=add.getCity();
            finalSetCities.insert(city);
        }
        cout<<"The airport represented by the code "<<inp<<" can reach "<<finalSetCities.size()<<" cities with "<< inp1 <<" lay-overs"<<'\n';
        if(finalSetCities.size()==0){reachable();}
        cout<<"###################################################################"<<'\n';
        cout<<"#    Do you want to see the list of reachable cities?           #"<<'\n';
        cout<<"#-----------------------------------------------------------------#"<<endl;
        cout<<"#   1 -> yes                                                      #"<<endl;
        cout<<"#   2 -> no                                                       #"<<endl;
        cout<<"#                                                                 #"<<endl;
        cout<<"###################################################################"<<'\n';
        int inp2;
        cin>>inp2;
        if (inp2==1) {
            cout << "+--------------------------------+" << endl;
            cout << "|              City              |" << endl;
            cout << "+--------------------------------+" << endl;
            for (auto city: finalSetCities) {
                cout << "| " << setw(31) <<left<< city <<"|" << endl;
                cout << "+--------------------------------+" << endl;
            }
        }
        reachable();
    }
}
void Menu::reachableCountry() {
    string inp;
    cout << "\nInsert a valid airport IATA code: ";
    cin >> inp;
    bool found = false;
    inp = toUpperSTR(inp);
    if (inp == "B" or inp == "b"){
        reachable();
    }
    Airport source;
    for(auto x : reader->getAirports()){
        if (x.getCode() == inp){
            source = x;
            found = true;
            break;
        }
    }
    if (!found){
        cout << "\nNo airport was found with code: " << inp << endl;
        reachableAirport();
    }
    cout << "#####################################################"<<'\n';
    cout << "#  How many lay-overs do you want to do?            #"<<'\n';
    cout << "#####################################################"<<endl;
    cout << "Number of lay-overs: ";
    int inp1;
    cin >> inp1;


    if (inp1 < 0) {
        cout << "\nInsert a valid input. \n\n";
        cin.clear();
        reachableAirport();
    }
    else {
        int distance=inp1+1;
        int currentDistance=0;
        queue<Airport> prov1;
        queue<Airport> prov2;
        queue<Airport> final;
        set<Airport> visited;
        visited.insert(source);
        final.push(source);
        prov1=final;
        while(currentDistance<distance){
            while(!prov1.empty()){
                Airport current=prov1.front();
                prov1.pop();
                dfsVistidAdj(reader->getGraph().findVertex(current),prov2,visited);
            }
            currentDistance++;
            final=prov2;
            prov1=prov2;
            queue<Airport> emptyQueue;
            prov2.swap(emptyQueue);
        }
        set<string> finalSetCountries;
        string homecountry=source.getCountry();
        while(!final.empty()){
            auto add=final.front();
            final.pop();
            if(add.getCountry()!=homecountry){
                auto country=add.getCountry();
                finalSetCountries.insert(country);
            }
        }
        cout<<"The airport represented by the code "<<inp<<" can reach "<<finalSetCountries.size()<<" countries with "<< inp1 <<" lay-overs"<<'\n';
        if(finalSetCountries.size()==0){reachable();}
        cout<<"###################################################################"<<'\n';
        cout<<"#    Do you want to see the list of reachable countries?           #"<<'\n';
        cout<<"#-----------------------------------------------------------------#"<<endl;
        cout<<"#   1 -> yes                                                      #"<<endl;
        cout<<"#   2 -> no                                                       #"<<endl;
        cout<<"#                                                                 #"<<endl;
        cout<<"###################################################################"<<'\n';
        int inp2;
        cin>>inp2;
        if (inp2==1) {
            cout << "+--------------------------------+" << endl;
            cout << "|              Country           |" << endl;
            cout << "+--------------------------------+" << endl;
            for (auto country: finalSetCountries) {
                cout << "| " << setw(31) <<left<< country <<"|" << endl;
                cout << "+--------------------------------+" << endl;
            }
        }
        reachable();
    }
}
//------------------------------------------------------------------------------------------------------------//
//------------------------------------ALL AIRPORTS STATICS-----------------------------------------------//
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
struct CompareFlights {
    bool operator()(const pair<string, int>& a, const pair<string, int>& b) const {
        return a.second > b.second;
    }
};
void Menu::importantAirport() {
    set<pair<string,int>, CompareFlights> preparation;
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
    for(auto a:numberflights){
        preparation.insert(a);
    }
    cout<<"What is the top number of airports you want to see?"<<endl;
    cout<<"Insert number: ";
    int number;
    cin>>number;
    int i=0;
    cout<<"--------------------------------------------"<<endl;
    for(auto it=preparation.begin();it!=preparation.end();it++){
        if(i==number){
            break;
        }
        auto current=it->first;

        for(auto airport:reader->getGraph().getVertexSet()){

            if(airport->getInfo().getCode()==current){
                cout<<"#"<<i+1<<"º: "<<airport->getInfo().getCode()<<" | "<<setw(30)<<airport->getInfo().getName()<<" #"<<endl;
                cout<<"--------------------------------------------"<<endl;
            }
        }
        i++;
    }

}

//------------------------------------------------------------------------------------------------------------//

void Menu::end() {
    cout << "----------------------------------------------" << endl;
}


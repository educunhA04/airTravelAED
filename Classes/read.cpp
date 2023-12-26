#include <fstream>
#include <sstream>
#include "read.h"

Reader::Reader() {
    readAirlines();
    readAirports();
    readFlights();
}

void Reader::readAirlines() {
    ifstream file;

    string code;
    string name;
    string callsign;
    string country;

    string current;
    file.open("..data/airlines.csv");

    getline(file, current); // ignore first line

    while(getline(file, current)){
        istringstream iss(current);

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country, ',');

        Airlines new_airline = Airlines(code,name,callsign,country);
        airlines.insert(new_airline);
    }
    file.close();
}

void Reader::readAirports() {
    ifstream file;

    string current;
    string code;
    string name;
    string city;
    string country;
    string number;
    string number2;

    double latitude;
    double longitude;

    file.open("../Data/airports.csv");
    getline(file,current); // ignore first line //

    while(getline(file,current)){
        istringstream iss(current);

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        getline(iss, number, ','); latitude = stod(number);
        getline(iss, number2, ','); longitude = stod(number2);

        Airport new_airport = Airport(code,name,city,country,latitude,longitude);
        graph.addVertex(new_airport);
        airports.insert(new_airport);
    }

    file.close();
}

void Reader::readFlights() {
    ifstream file;
    string current;

    string source;
    string target;
    string airlineCode;

    file.open("../Data/flights.csv");
    getline(file,current); // ignore first line //

    while (getline(file,current)) {
        istringstream iss(current);
        getline(iss, source, ',');
        getline(iss, target, ',');
        getline(iss, airlineCode, ',');

        Airport first;
        Airport second;
        Airlines airline;

        auto it = airports.begin(); int count = 0;
        while(it != airports.end() && count != 2){
            auto currentAP = *it;
            if (currentAP.getCode() == source){
                first = currentAP;
                count++;
            }
            if (currentAP.getCode() == target){
                second = currentAP;
                count++;
            }
            it++;
        }

        auto it2 = airlines.begin();
        while(it2 != airlines.end()){
            auto currentAirline = *it2;
            if(currentAirline.getCode() == airlineCode){
                airline = currentAirline;
                break;
            }
            it++;
        }

        double distance; //= calculateDistance(first, second); -> CALCULA DISTANCIA ENTRE AEROPORTOS
    }
    file.close();
}

#include <fstream>
#include <sstream>
#include "read.h"
#include <cmath>

using namespace std;

/**
 * Calculates de distance between two airports a and b
 * @param a - first airport
 * @param b - second airport (order doesnt matter // distance is the same)
 * @return distance between airport a and airport b;
 */
double calculateDistance(Airport a, Airport b) {
    double dif_Lat = (b.getLatitude() - a.getLatitude()) * M_PI / 180.0;
    double dif_Lon = (b.getLongitude() - a.getLongitude()) * M_PI / 180.0;

    double x = pow(sin(dif_Lat / 2), 2) + pow(sin(dif_Lon / 2), 2);
    double y = x * cos(a.getLatitude() * M_PI / 180.0) * cos(b.getLatitude() * M_PI / 180.0);

    double radius = 6371;
    double z = 2 * asin(sqrt(y));

    return radius * z;
}

Reader::Reader() {
    readAirlines();
    readAirports();
    readFlights();
}
/**
 * Function that reads the file airlines.csv
 * inserts each Airline (code, name, callsign and country) in a set
 */
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

        Airlines new_airline = Airlines(code);
        airlines.insert(new_airline);
    }
    file.close();
}
/**
 * Function that reads the file airports.csv
 * Creates an airport with its code, name, city, country and coordinates
 * Adds a new vertex with the airport to the graph of airports
 * Also inserts the airport in a set of airports
 */
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
/**
 * This function reads the file flights.csv
 * For each line of the file, adds to the Vertex of the graph corresponding to the source of the flight an edge with the
 * destination, the distance between the two airports, and the airline responsible for the flight
 */
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

        double distance = calculateDistance(first, second);

        auto it2 = airlines.begin();
        while(it2 != airlines.end()) {
            auto currentAirline = *it2;
            if(currentAirline.getCode() == airlineCode){
                airline = currentAirline;
                break;
            }
            it++;
        }

        graph.addEdgeAirlines(graph.findVertex(first)->getInfo(), graph.findVertex(second)->getInfo(),distance, airline);
    }
    file.close();
}

set<Airport> const& Reader::getAirports() const {
    return airports;
}

set<Airlines> const& Reader::getAirlines() const {
    return airlines;
}
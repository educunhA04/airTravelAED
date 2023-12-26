#ifndef AIRTRAVELAED_READ_H
#define AIRTRAVELAED_READ_H

#include "airlines.h"
#include "airport.h"
#include "Graph.h"
#include <set>

using namespace std;

class Reader {
public:
    Reader();
private:
    void readAirlines();
    void readAirports();
    void readFlights();

    set<Airport> airports;   /// set with the airports and their info (from airports.csv)
    set<Airlines> airlines; /// set with the airlines and their info (from airlines.csv)
    Graph<Airport> graph;  /// graph of flights between airports
};

#endif //AIRTRAVELAED_READ_H

#ifndef AIRTRAVELAED_READ_H
#define AIRTRAVELAED_READ_H

#include "airlines.h"
#include "airport.h"
#include "Graph.h"
#include <set>
#include <unordered_set>

using namespace std;

class Reader {
public:
    Reader();
    set<Airport> const& getAirports() const;
    set<Airlines> const& getAirlines() const;
    Graph<Airport> const& getGraph() const;

    void readAirlines();
    void readAirports();
    void readFlights();
private:
    set<Airport> airports;   /// set with the airports and their info (from airports.csv)
    set<Airlines> airlines; /// set with the airlines and their info (from airlines.csv)
    Graph<Airport> graph;  /// graph of flights between airports
};

#endif //AIRTRAVELAED_READ_H

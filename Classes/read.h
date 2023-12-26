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

    set<Airport> airports;
    set<Airlines> airlines;
    Graph<Airport> graph;
};
#endif //AIRTRAVELAED_READ_H

#ifndef AIRTRAVELAED_MENU_H
#define AIRTRAVELAED_MENU_H

#include "read.h"

class Menu {
private:
    //info menu//
    void information();
    void showAirports();
    void showAirlines();


    //statistics menu//
    void statistics();

    //airports//
    void airportsStat();
    void numAirports();
    void airportTrafMax();
    void importantAirport();
    void specificAirport();
    //specific airport statistics//
    void numDest(Airport airport);
    void airportsDest(Airport airport);
    void citiesDest(Airport airport);
    void countriesdest(Airport airport);

    //Flights//
    void numFlights();
    void numFlightsSrc();
    void flightsAirport(Airport airport);
    void flightsCities(); //TODO
    void flightsAirlines(Airlines airlines);
    void flightsCountries(); //TODO

    //Reachable country//
    void reachable();
    void reachableAirport(Airport airport);
    void reachableAirlines(Airlines airlines);
    void reachableCity(); //TODO
    void reachableCountry(); //TODO


    Reader* reader;
    vector<string> src;
    vector<string> dest;
public:
    Menu();
    void init();
    static void end();
};


#endif //AIRTRAVELAED_MENU_H

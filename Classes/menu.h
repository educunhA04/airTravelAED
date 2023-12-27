#ifndef AIRTRAVELAED_MENU_H
#define AIRTRAVELAED_MENU_H

#include "read.h"

class Menu {
private:
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


    //info menu//

    void info();
    void showAirports();
    void showAirlines();

    Reader* reader;
public:
    Menu();
    void init();
    static void end();
};


#endif //AIRTRAVELAED_MENU_H

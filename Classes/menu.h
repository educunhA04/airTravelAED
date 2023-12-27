#ifndef AIRTRAVELAED_MENU_H
#define AIRTRAVELAED_MENU_H

#include "read.h"

class Menu {
private:
    //info menu//
    void information(); // DONE
    void showAirports(); // DONE
    void showAirlines(); // DONE


    //statistics menu//
    void statistics(); // DONE


    //airports//
    void airportsStat(); // DONE

    void numAirports(); // DONE
    void airportTrafMax(); // DONE
    void importantAirport(); // TODO ARTICULATION POINTS


    //specific airport statistics//
    void specificAirport();

    void numDest(); // DONE
    void airportsDest(); // DONE
    void citiesDest();
    void countriesdest();


    //Flights//
    void flights();

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

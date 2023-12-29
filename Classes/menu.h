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
    void importantAirport(); // DONE

    //specific airport statistics//
    void specificAirport();
    void numDest(); // DONE
    void airportsDest(); // DONE
    void citiesDest(); // DONE
    void countriesDest(); // DONE

    //Flights//
    void flights();

    void numFlights(); // DONE
    void flightsAirport(); // DONE
    void flightsCities(); // DONE
    void flightsAirlines(); // DONE
    void flightsCountries(); // DONE


    //Reachable country//
    void reachable();

    void reachableAirport(); //DONE
    void reachableCity(); //DONE
    void reachableCountry(); //DONE


    Reader* reader;
    vector<string> src;
    vector<string> dest;

public:
    Menu();
    void init();
    static void end();
};


#endif //AIRTRAVELAED_MENU_H

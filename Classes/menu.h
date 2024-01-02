#ifndef AIRTRAVELAED_MENU_H
#define AIRTRAVELAED_MENU_H

#include "read.h"

class Menu {
private:
    //info menu//
    struct ComparePaths{
        bool operator()(const vector<Airport>& path1, const vector<Airport>& path2) const {
            return path1.size() < path2.size();
        }
    };
    void information(); // DONE
    void showAirports(); // DONE
    void showAirlines(); // DONE
    void bestOptionWOAirSetter(set<Airport> &departing,set<Airport> &destination); // TODO
    void bestOptionWOAir(); // TODO
    void bestOptionSetter(set<string> &airlinesPreference, bool &minimumAirlines,bool &neutral, set<Airport> &departing,set<Airport> &destination); // DONE
    void bestOption(); // TODO
    set<string> airlinesAvailable( Vertex<Airport>*source, Vertex<Airport>*destination );
    vector<tuple<string, string, string>>  airlinesChoiceMinimum(vector<Vertex<Airport>*> path, set<string> &nairlines);
    vector<tuple<string, string, string>>  airlinesChoicePreference(vector<Vertex<Airport>*> path, set<string> &nairlines ,set<string> airlinesPreference);
    bool dfsFindPathsToNode(Airport current, Airport end, vector<Airport>& currentPath, set<vector<Airport>, ComparePaths>& paths, set<Vertex<Airport>*> &visited);

    //helper functions//
    set<Airport> city(); // DONE
    set<Airport> Coordinates(); // DONE
    Airport Airports(); // DONE
    set<Airport> AirportsChoice();
    //statistics menu//
    void statistics(); // DONE

    //airports//
    void airportsStat(); // DONE
    void numAirports(); // DONE
    void airportTrafMax(); // DONE
    void importantAirport(); // DONE
    void maxFlight();
    void calculateMax(string num);
    void dfsVisit(Vertex<Airport>* v, int currentStops, set<tuple<Airport, Airport, int>>& stopPairs, Vertex<Airport>* v2);

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

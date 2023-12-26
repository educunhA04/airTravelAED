#ifndef AIRTRAVELAED_AIRPORT_H
#define AIRTRAVELAED_AIRPORT_H

#include <string>

using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    double latitude{};
    double longitude{};

public:
    Airport(string, string, string, string, double, double);
    Airport();
    string getCode();
    string getName();
    string getCity();
    string getCountry();
    double getLatitude();
    double getLongitude();
    bool operator<(const Airport &a) const;
    bool operator==(const Airport &a) const;
};
#endif //AIRTRAVELAED_AIRPORT_H

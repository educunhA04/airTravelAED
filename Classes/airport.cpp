#include "airport.h"

using namespace std;

Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

string Airport::getCode() {
    return code;
}
string Airport::getCity() {
    return city;
}
string Airport::getCountry() {
    return country;
}
string Airport::getName() {
    return name;
}
double Airport::getLatitude() {
    return latitude;
}
double Airport::getLongitude() {
    return longitude;
}

bool Airport::operator<(const Airport &a) const {
    return code < a.code;
}

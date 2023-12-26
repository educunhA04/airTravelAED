#include "airlines.h"

using namespace std;

Airlines::Airlines(std::string code, std::string name, std::string callSign, std::string country) {
    this->code = code;
    this->name = name;
    this->callSign = callSign;
    this->country = country;
}
Airlines::Airlines(std::string code) {this->code = code;}
string Airlines::getName() {return name;}
string Airlines::getCountry() {return country;}
string Airlines::getCode() {return code;}
string Airlines::getCall() {return callSign;}

bool Airlines::operator< (const Airlines &a) const {return code < a.code;}

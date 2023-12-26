#ifndef AIRTRAVELAED_AIRLINES_H
#define AIRTRAVELAED_AIRLINES_H

#include <string>
using namespace std;

class Airlines {
private:
    string code;
    string name;
    string callSign;
    string country;
public:
    Airlines(string code, string name, string callSign, string country);
    string getCode();
    string getName();
    string getCall();
    string getCountry();
};
#endif //AIRTRAVELAED_AIRLINES_H
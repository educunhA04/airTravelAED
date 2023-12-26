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
    Airlines();
    string getCode();
    string getName();
    string getCall();
    string getCountry();
    explicit Airlines(string code);
    bool operator <(const Airlines &a) const;
};
#endif //AIRTRAVELAED_AIRLINES_H

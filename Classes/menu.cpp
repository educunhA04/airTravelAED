#include <iostream>
#include "menu.h"

using namespace std;

Menu::Menu() {
    cout << "----------------------------------------------" << "\n\n";
    cout << "Hello! Welcome to our flight management system!" << "\n\n";
    reader = new Reader();
}

void Menu::init() {
    string inp;
    while(true) {
        cout << "Select an option: " << "\n\n"
        << "1 -> Consult Info" << endl
        << "2 -> Consult Statistics" << endl
        << "E -> EXIT" << "\n\n"
        << "Option: ";
        cin >> inp;

        if (inp == "1") {
            information();
        }
        /*
        else if (inp == "2") {
            statistics();
        }
        */
        else if (inp == "E" or inp == "e") {
            return;
        }

        else {
            cout << "\n Insert a valid input. \n\n";
            cin.clear();
        }
    }
}

void Menu::information() {
    string inp;
    while(true) {
        cout << "\n\n" << "Which information do you want to consult?" << endl << "Select a valid option: " << "\n\n"
             << "1 -> Airports list" << endl
             << "2 -> Airlines list" << endl
             << "B -> Back to the previous Menu \n\n"
             << "Option: ";

        cin >> inp;

        if (inp == "1") {
            showAirports();
        }

        else if (inp == "2") {
            showAirlines();
        }

        else if (inp == "B" or inp == "b") {
            init();
        }

        else {
            cout << "\n Insert a valid input. \n\n";
            cin.clear();
        }
    }
}
void Menu::showAirports() {
    for (auto i : reader->getAirports()) {
        cout << i.getCode() << " - "
             << i.getName() << " - "
             << i.getCity() << " - "
             << i.getCountry() << endl;
    }
}

void Menu::showAirlines() {
    for (auto i : reader->getAirlines()) {
        cout << i.getCode() << " - "
             << i.getName() << " - "
             << i.getCall() << " - "
             << i.getCountry() << endl;
    }
}

void Menu::end() {
    cout << "----------------------------------------------"<< endl;

}


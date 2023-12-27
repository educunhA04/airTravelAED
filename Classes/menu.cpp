#include <iostream>
#include "menu.h"

using namespace std;

Menu::Menu() {
    cout << "-----------------" << endl;
    cout << "Olá!!" << endl;
    reader = new Reader();
}

void Menu::init() {
    string inp;
    cout << "Insert 1" << endl;
    cin >> inp;

    if (inp == "1") {
        showAirports();
    }
}

void Menu::showAirports() {
    for (auto i : reader->getAirports()) {
        cout << i.getName() << endl;
    }
}

void Menu::end() {
    cout << "-------------------"<< endl;
}


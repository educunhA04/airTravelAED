#include <iostream>
#include "menu.h"

using namespace std;

void Menu::init() {
    string inp;
    cout << "Insert 1" << endl;
    cin >> inp;

    if (inp == "1") {
        showAirports();
    }
}

Menu::Menu() {
    cout << "-----------------" << endl;
    cout << "Olá!!" << endl;
    reader = new Reader();
}

void Menu::showAirports() {
    cout << "Now showing all airports:" << endl;
    for (auto i : reader->getAirports()) {
        cout << "Name: " << i.getName() << "| Code: "<< i.getCode() << endl;
    }
}

void Menu::showAirlines() {
    cout << "Now showing all airlines" << endl;
    for(auto a : reader->getAirlines()){
        cout << "Name: " << a.getName() << "| Code: " << a.getCode() << endl;
    }
}

void Menu::end() {
    cout << "-------------------"<< endl;
}


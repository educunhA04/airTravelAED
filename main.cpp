#include <iostream>
#include "Classes/menu.h"

int main() {

    std::cout << "we love aed\n" << std::endl;
    std::cout << "boas pessoal daqui é o tiagovski com um video novozinho\n"
                 "pessoal e hoje tou aqui pra fazer uma homenagem ao peter deniz" << std::endl;

    Menu menu;
    menu.init();
    Menu::end();
}

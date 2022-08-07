#include "rfui.h"
#include <iostream>
#include <chrono>
#include <thread>


int main() {
    rfui::clearScreen();

    rfui::Widget w(4, 20, 5, 3, rfui::C::BG::RED, rfui::C::FG::BLACK, "Test Widget");
    w.draw();
    system("pause");
    return 0;
}

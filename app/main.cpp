#include "rfui.h"
#include <iostream>
#include <chrono>
#include <thread>


int main() {
    rfui::init();
    rfui::clearScreen();

    rfui::Root root(40, 120);

    auto *w = new rfui::Widget(4, 20, 5, 3, rfui::C::BG::BLU, rfui::C::FG::BLK, "Test Тест");
    auto *a = new rfui::Widget(4, 20, 5, 7, rfui::C::BG::YEL, rfui::C::FG::BLK, "Test Widget");
    auto *t = new rfui::Label(0, 0, "Пізда", rfui::C::FG::BLK);

    root.addWidget(w);
    w->addLabel(t);
    root.addWidget(a);
    root.draw();
    rfui::pause();
    return 0;
}

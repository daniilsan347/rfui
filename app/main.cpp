#include "rfui.h"
#include <iostream>
#include <chrono>
#include <thread>


int main() {
    rfui::init();
    rfui::clearScreen();

    rfui::Root root(30, 80, rfui::C::BG::GRN, rfui::C::FG::YEL);

    auto *w = new rfui::Widget(4, 20, 1, 3, rfui::C::BG::BLU, rfui::C::FG::BLK, "Test Тест");
    auto *a = new rfui::Widget(4, 20, 1, 7, rfui::C::BG::YEL, rfui::C::FG::BLK, "Test Widget");
    auto *t = new rfui::Label(0, 0, "Ярик", rfui::C::FG::BLK);
    auto *l = new rfui::Label(0, 1, "Пізда");
    auto *b = new rfui::Label(0, 2, "Рулю");

    root.addWidget(w);
    w->addLabel(t);
    w->addLabel(l);
    w->addLabel(b);
    root.addWidget(a);
    int tW, tH;
    rfui::getTerminalSize(tW, tH);
    a->addLabel(
        new rfui::Label(0, 0, std::to_string(tW))
            );
    a->addLabel(
        new rfui::Label(0, 1, std::to_string(tH))
            );
    root.addWidget(
        new rfui::Widget(1, 80, 1, 1, rfui::C::BG::BLU, rfui::C::FG::WHT, "Top")
            ); // Top widget
    root.addWidget(
            new rfui::Widget(1, 80, 1, 30, rfui::C::BG::RED, rfui::C::FG::YEL, "Bottom")
            ); // Bottom widget
    root.draw();
    rfui::pause();
    return 0;
}

#include "rfui.h"
#include <chrono>
#include <string>
#include <thread>

int main() {
    rfui::init();
    rfui::clearScreen();
    int tW, tH; rfui::getTerminalSize(tW, tH);
    rfui::Root root(tH, tW, rfui::C::FG::BLK, rfui::C::BG::WHT);
    auto *wid1 = new rfui::Widget(1, 20, 0, 0, "W: " + std::to_string(tW) + ", H: " + std::to_string(tH), rfui::C::FG::WHT, rfui::C::BG::RED);
    root.addWidget(wid1);
    auto *wid2 = new rfui::Widget(3, 20, 0, 2, "Час", rfui::C::FG::BLK, rfui::C::BG::GRN);
    auto *clock = new rfui::Label(0, 1, ""); wid2->addLabel(clock);
    auto *animation = new rfui::Label(0, 2, ""); wid2->addLabel(animation);
    root.addWidget(wid2);
    root.draw();

    // Starting time
    auto start = std::chrono::system_clock::now();

    int i = 0;
    while (true) {
        // Generate time string in hh:mm:ss format
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::string time = std::ctime(&in_time_t);
        time = time.substr(11, 8);
        clock->setText(time);
        animation->setText(std::to_string(i));
        i++;
        // Draw
        root.draw();
        if (i > 20) break;
    }

    // Final time
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    rfui::resetTextFeatures();
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    std::cout << "FPS: " << i / elapsed_seconds.count() << std::endl;

    return 0;
}

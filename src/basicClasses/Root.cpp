//
// Created by daniilsan on 25.08.2022.
//

#include <iostream>

#include "Root.h"
#include "Widget.h"
#include "rfui.h"

rfui::Root::Root(int lines, int cols, int bgColor, int fgColor) {
    this->lines = lines;
    this->columns = cols;
    this->bgColor = bgColor;
    this->fgColor = fgColor;
}

rfui::Root::~Root() {
    for (auto& widget : this->widgets) {
        delete widget;
    }
}

void rfui::Root::addWidget(Widget* widget) {
    if (!widget->getBgColor()) {
        widget->setBgColor(this->bgColor);
    }
    if (!widget->getFgColor()) {
        widget->setFgColor(this->fgColor);
    }
    widget->setRootBg(this->bgColor);

    this->widgets.push_back(widget);
}

void rfui::Root::draw() {
    // Draw root
    // Move cursor and set colours
    rfui::moveCursorToTop();
    rfui::setBgColor(this->bgColor);
    rfui::setFgColor(this->fgColor);
    // Draw background
    for (int i = 0; i < this->lines; i++) {
        std::cout << "\x1B[0G";
        for (int j = 0; j < this->columns; j++) std::cout << ' ';
        std::cout << std::endl;
    }
    rfui::resetTextFeatures();
    // Draw widgets
    for (auto widget : this->widgets) {
        widget->draw();
    }
    rfui::moveCursorToBottom();
}


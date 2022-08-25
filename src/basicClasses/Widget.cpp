//
// Created by daniilsan on 25.08.2022.
//

#include <string>

#include "Widget.h"
#include "Label.h"
#include "rfui.h"

rfui::Widget::Widget(int height, int width, int x, int y, std::string title, int bgColor, int fgColor) {
    this->height = height;
    this->width = width;
    this->x = x;
    this->y = y;
    this->bgColor = bgColor;
    this->fgColor = fgColor;
    this->visible = true;
    this->title = new rfui::Label(x + 1, y, std::move(title), fgColor, bgColor);
    this->title->setUnderlined(true);
}

// Widget methods
void rfui::Widget::draw() {
    if (this->visible) {
        // Draw Widget
        // Move cursor and set colours
        rfui::moveCursorTo(this->x, this->y);
        rfui::setBgColor(this->bgColor);
        rfui::setFgColor(this->fgColor);
        // Draw background
        for (int i = 0; i < this->height; i++) {
            std::cout << "\x1B[" << this->x << "G";
            for (int j = 0; j < this->width; j++) std::cout << ' ';
            std::cout << std::endl;
        }
        // Draw title
        this->title->print();
        // Draw labels
        for (auto *label : this->labels) label->print();

        rfui::resetTextFeatures();
        moveCursorToBottom();
    }
}

void rfui::Widget::addLabel(rfui::Label *label) {
    int lX, lY;
    label->getPosition(lX, lY);
    label->setPosition(lX + this->x + 1, lY + this->y + 1);
    if (label->getBgColor() == 0) label->setBgColor(this->bgColor);
    if (label->getFgColor() == 0) label->setFgColor(this->fgColor);
    this->labels.push_back(label);
}

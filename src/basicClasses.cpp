//
// Created by daniilsan on 25.07.2022.
//
#include "rfui.h"
#include <iostream>
//#include <utility>

//rfui::Widget::Widget(int height, int width, int x, int y, std::string title, int bgColor, int fgColor) {
//    this->height = height;
//    this->width = width;
//    this->x = x;
//    this->y = y;
//    this->bgColor = bgColor;
//    this->fgColor = fgColor;
//    this->visible = true;
//    this->title = new rfui::Label(x + 1, y, std::move(title), fgColor, bgColor);
//    this->title->setUnderlined(true);
//}
//
//// Widget methods
//void rfui::Widget::draw() {
//    if (this->visible) {
//        // Draw Widget
//        // Move cursor and set colours
//        rfui::moveCursorTo(this->x, this->y);
//        rfui::setBgColor(this->bgColor);
//        rfui::setFgColor(this->fgColor);
//        // Draw background
//        for (int i = 0; i < this->height; i++) {
//            std::cout << "\x1B[" << this->x << "G";
//            for (int j = 0; j < this->width; j++) std::cout << ' ';
//            std::cout << std::endl;
//        }
//        // Draw title
//        this->title->print();
//        // Draw labels
//        for (auto *label : this->labels) label->print();
//
//        rfui::resetTextFeatures();
//        moveCursorToBottom();
//    }
//}
//
//void rfui::Widget::addLabel(rfui::Label *label) {
//    int lX, lY;
//    label->getPosition(lX, lY);
//    label->setPosition(lX + this->x + 1, lY + this->y + 1);
//    if (label->getBgColor() == 0) label->setBgColor(this->bgColor);
//    if (label->getFgColor() == 0) label->setFgColor(this->fgColor);
//    this->labels.push_back(label);
//}

// Label class
//rfui::Label::Label(int x, int y, std::string text, int fgColor, int bgColor) {
//    this->x = x;
//    this->y = y;
//    this->text = std::move(text);
//    this->bold = false;
//    this->italic = false;
//    this->underlined = false;
//    this->visible = true;
//    this->fgColor = fgColor;
//    this->bgColor = bgColor;
//}
//
//void rfui::Label::print() {
//    if (this->visible) {
//        // Draw Label
//        // Move cursor and set colours
//        rfui::moveCursorTo(this->x, this->y);
//        rfui::setFgColor(this->fgColor);
//        rfui::setBgColor(this->bgColor);
//        // Draw text
//        rfui::setBold(this->bold);
//        rfui::setItalic(this->italic);
//        rfui::setUnderlined(this->underlined);
//
//        std::cout << this->text;
//
//        rfui::resetTextFeatures();
//    }
//}

//rfui::Root::Root(int lines, int cols, int bgColor, int fgColor) {
//    this->lines = lines;
//    this->columns = cols;
//    this->bgColor = bgColor;
//    this->fgColor = fgColor;
//}
//
//rfui::Root::~Root() {
//    for (auto& widget : this->widgets) {
//        delete widget;
//    }
//}
//
//void rfui::Root::addWidget(rfui::Widget* widget) {
//    if (!widget->getBgColor()) {
//        widget->setBgColor(this->bgColor);
//    }
//    if (!widget->getFgColor()) {
//        widget->setFgColor(this->fgColor);
//    }
//
//    this->widgets.push_back(widget);
//}
//
//void rfui::Root::draw() {
//    // Draw root
//    // Move cursor and set colours
//    rfui::moveCursorToTop();
//    rfui::setBgColor(this->bgColor);
//    rfui::setFgColor(this->fgColor);
//    // Draw background
//    for (int i = 0; i < this->lines; i++) {
//        std::cout << "\x1B[0G";
//        for (int j = 0; j < this->columns; j++) std::cout << ' ';
//        std::cout << std::endl;
//    }
//    rfui::resetTextFeatures();
//    // Draw widgets
//    for (auto widget : this->widgets) {
//        widget->draw();
//    }
//    moveCursorToBottom();
//}




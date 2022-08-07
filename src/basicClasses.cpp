//
// Created by daniilsan on 25.07.2022.
//
#include "rfui.h"
#include <iostream>
#include <utility>

rfui::Widget::Widget(int height, int width, int x, int y, int bgColor, int fgColor, std::string title) {
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
            for (int j = 0; j < this->width; j++) {
                std::cout << " ";
            }
            std::cout << std::endl;
        }
        // Draw title
        this->title->print();
        moveCursorToBottom();
    }
}

void rfui::Widget::addLabel(rfui::Label *label) {}

// Label class
rfui::Label::Label(int x, int y, std::string text, int fgColor, int bgColor) {
    this->x = x;
    this->y = y;
    this->text = std::move(text);
    this->bold = false;
    this->italic = false;
    this->underlined = false;
    this->visible = true;
    this->fgColor = fgColor;
    this->bgColor = bgColor;
}

void rfui::Label::print() {
    if (this->visible) {
        // Draw Label
        // Move cursor and set colours
        rfui::moveCursorTo(this->x, this->y);
        rfui::setFgColor(this->fgColor);
        rfui::setBgColor(this->bgColor);
        // Draw text
        rfui::setBold(this->bold);
        rfui::setItalic(this->italic);
        rfui::setUnderlined(this->underlined);

        std::cout << this->text;

        rfui::resetTextFeatures();
    }
}





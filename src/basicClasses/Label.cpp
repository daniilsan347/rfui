//
// Created by daniilsan on 23.08.2022.
//

#include <iostream>

#include "Label.h"
#include "rfui.h"

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

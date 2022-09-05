//
// Created by daniilsan on 23.08.2022.
//

#include <iostream>

#include "Label.h"
#include "rfui.h"

rfui::Label::Label() {
    this->x = 1;
    this->y = 1;
    this->len = 0;
    this->bold = false;
    this->italic = false;
    this->underlined = false;
    this->visible = true;
    this->fgColor = rfui::C::FG::NONE;
    this->bgColor = rfui::C::BG::NONE;
}

rfui::Label::Label(int x, int y, std::string text, int fgColor, int bgColor) {
    this->x = x;
    this->y = y;
    this->len = rfui::strLenUtf8(text);
    this->text = std::move(text);
    this->bold = false;
    this->italic = false;
    this->underlined = false;
    this->visible = true;
    this->fgColor = fgColor;
    this->bgColor = bgColor;
}

void rfui::Label::setPosition(int lX, int lY) {
    this->erase();
    this->x = lX; this->y = lY;
    this->draw();
}

void rfui::Label::setVisible(bool isVisible) {
    if (isVisible) {
        this->visible = true;
        this->draw();
    } else {
        this->visible = false;
        this->erase();
    }
}

void rfui::Label::draw() {
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

        rfui::moveCursorToBottom();
        rfui::resetTextFeatures();
    }
}

void rfui::Label::erase() const {
    if (this->visible) {
        // Erase Label
        // Move cursor and set colours
        rfui::moveCursorTo(this->x, this->y);
        rfui::setFgColor(this->bgColor);
        rfui::setBgColor(this->fgColor);
        // Erase text
        for (int i = 0; i < this->len; i++) std::cout << ' ';
        rfui::moveCursorToBottom();
        rfui::resetTextFeatures();
    }
}

void rfui::Label::setText(std::string newText) {
    this->text = std::move(newText);
    this->len = rfui::strLenUtf8(this->text);
    this->draw();
}

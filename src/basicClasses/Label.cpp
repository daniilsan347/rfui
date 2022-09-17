//
// Created by daniilsan on 23.08.2022.
//

#include <iostream>

#include "Label.h"
#include <string>
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

void rfui::Label::setText(std::string newText) {
    this->text = newText;
    this->len = rfui::strLenUtf8(this->text);
}

void rfui::Label::draw(rfui::BufferCell **buffer) {
    if (!this->visible) return;
    // Get separated text
    std::vector<std::string> symbols = rfui::splitUtf8(this->text);
    // Put colours and symbols to the buffer
    for (int i = 0; i < this->len; i++) {
        buffer[this->y][this->x + i].fgColor = this->fgColor;
        buffer[this->y][this->x + i].bgColor = this->bgColor;
        buffer[this->y][this->x + i].bold = this->bold;
        buffer[this->y][this->x + i].italic = this->italic;
        buffer[this->y][this->x + i].underlined = this->underlined;
        buffer[this->y][this->x + i].symbol = symbols[i];
    }
}

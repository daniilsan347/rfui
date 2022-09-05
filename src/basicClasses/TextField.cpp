//
// Created by daniilsan on 01.09.2022.
//

#include "TextField.h"
#include "rfui.h"
#include <iostream>
#include <vector>

// TextField default constructor
rfui::TextField::TextField() {
    this->x = 0; this->y = 0;
    this->w = 0; this->h = 0;
    this->fgColor = 0;
    this->bgColor = 0;
}

// TextField constructor. Text has to be assigned with separate addStr function
rfui::TextField::TextField(int x, int y, int w, int h, int fgColor, int bgColor) {
    this->x = x; this->y = y;
    this->w = w; this->h = h;
    this->fgColor = fgColor;
    this->bgColor = bgColor;
}

// Adds text into TextField object. Automatically wraps text.
void rfui::TextField::addStr(const std::string &str) {
    std::vector<std::string> words{};
    std::string word;
    // Split string into words
    for (auto ch:str) {
        if (ch == ' ') {
            words.push_back(word);
            word = "";
        } else word += ch;
    }
    // If there was word left
    if (!word.empty()) words.push_back(word);

    // Add words to lines
    for (auto &wd:words) {
        if (this->lines.empty()) {
            this->lines.push_back(wd);
        } else {
            if (strLenUtf8(this->lines.back()) + strLenUtf8(wd) + 1 <= this->w) {
                this->lines.back() += " " + wd;
            } else {
                this->lines.push_back(wd);
            }
        }
    }
}

void rfui::TextField::draw() {
    if (this->visible) {
        // Draw background
        rfui::clearArea(this->x, this->y, this->w, this->h, this->bgColor);
        // Set text features
        rfui::setFgColor(this->fgColor);
        rfui::setBold(this->bold);
        rfui::setItalic(this->italic);
        rfui::setUnderlined(this->underlined);
        // Draw text
        if (!this->lines.empty()) {
            for (int i = 0; i < this->lines.size(); ++i) {
                rfui::moveCursorTo(this->x, this->y + i);
                std::cout << this->lines[i];
            }
        }

        rfui::resetTextFeatures();
        rfui::moveCursorToBottom();
    }
}



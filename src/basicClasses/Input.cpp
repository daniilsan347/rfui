//
// Created by daniilsan on 25.08.2022.
//

#include "Input.h"
#include "Label.h"
#include "rfui.h"
#include <iostream>
#include <utility>

rfui::InPrompt::InPrompt(int x, int y, std::string prompt, int fgColor, int bgColor) {
    this->x = x;
    this->y = y;
    this->promptLabel = new Label(x, y, std::move(prompt), fgColor, bgColor);
    this->input = new Label(x + this->promptLabel->getLen() + 1, y, "", fgColor, bgColor);
    this->bgColor = bgColor;
    this->fgColor = fgColor;
    this->visible = true;
}

rfui::InPrompt::~InPrompt() {
    delete this->promptLabel;
}
// Setters
[[maybe_unused]] void rfui::InPrompt::setPosition(int xPos, int yPos) {
    this->x = xPos;
    this->y = yPos;
    this->promptLabel->setPosition(xPos, yPos);
    this->input->setPosition(xPos + this->promptLabel->getLen() + 1, yPos);

}

// Methods

[[maybe_unused]] rfui::InContainer rfui::InPrompt::getInput() {
    if (this->visible) {
        std::string tempString;
        rfui::moveCursorTo(this->input->getX() + 1, this->input->getY() + 1);
        rfui::setBgColor(this->bgColor);
        rfui::setFgColor(this->fgColor);
        rfui::setInverse(true);
        std::cin >> tempString;
        rfui::resetTextFeatures();
        this->data = InContainer(tempString);
        this->input->setText(tempString);
        return InContainer(tempString);
    } else return {};
}

void rfui::InPrompt::draw(rfui::BufferCell **buffer) {
    if (!this->visible) return;
    // Print prompt
    this->promptLabel->draw(buffer);
    // Print input
    if (!this->input->getText().empty()) {
        this->input->draw(buffer);
    }
}

rfui::InField::InField(int x, int y, int w, int h, int fgColor, int bgColor) {
    this->x = x;
    this->y = y;
    this->display.setPosition(x, y);
    this->width = w; this->display.setWidth(w);
    this->height = h; this->display.setHeight(h);
    this->bgColor = bgColor;
    this->fgColor = fgColor;
}

void rfui::InField::setPosition(int posX, int posY) {
    int offX, offY;
    offX = posX - this->x; offY = posY - this->y;
    this->x = posX; this->y = posY;
    this->display.setPosition(this->display.getX() + offX, this->display.getY() + offY);
}


void rfui::InField::draw(BufferCell **buffer) {
    if (!this->visible) return;
    // Put colors to buffer
    for (int i = this->x; i < this->x + this->width; i++) {
        for (int j = this->y; j < this->y + this->height; j++) {
            buffer[i][j].bgColor = this->bgColor;
            buffer[i][j].fgColor = this->fgColor;
        }
    }
    // Call display draw
    this->display.draw(buffer);
}


void rfui::InField::getEndPos(int &xPos, int &yPos) {
    if (this->display.getLines().empty()) {
        xPos = this->getX();
        yPos = this->getY();
    }
    else {
        int len = 0;
        for (auto &line:this->display.getLines()) {
            len += strLenUtf8(line);
        }
        xPos = this->getX() + len%this->width + 1;
        yPos = int(this->getY() + this->display.getLines().size() - 1);
    }
}


std::vector<rfui::InContainer> rfui::InField::getInput(int entries, Root *root) {
    if (!this->visible) return {};
    // Reset
    this->reset();
    root->draw();
    // Get input
    std::string tempString;
    for (int i = 0; i < entries; ++i) {
        rfui::moveCursorTo(this->getX() + 1, this->getY() + 1);
        rfui::setBgColor(this->getBgColor()); rfui::setFgColor(this->getFgColor());
        rfui::setInverse(true);
        std::cin >> tempString;
        rfui::resetTextFeatures();
        this->data.emplace_back(tempString);
        this->addStr(tempString);
        root->draw();
    }
    return this->data;
}

void rfui::InField::reset() {
    this->data.clear();
    this->display.getLines().clear();
}



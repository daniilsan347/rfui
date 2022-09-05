//
// Created by daniilsan on 25.08.2022.
//

#include "Input.h"
#include "Label.h"
#include "rfui.h"
#include <iostream>
#include <utility>

rfui::InPrompt::InPrompt(int x, int y, std::string prompt, int bgColor, int fgColor) {
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

void rfui::InPrompt::setVisible(bool isVisible) {
    if (isVisible) {
        this->visible = true;
        this->promptLabel->setVisible(true);
        this->input->setVisible(true);
    } else {
        this->visible = false;
        this->promptLabel->setVisible(false);
        this->input->setVisible(false);
    }
}

// Methods
void rfui::InPrompt::draw() {
    if (this->visible) {
        // Print prompt
        this->promptLabel->draw();
        // Print input
        if (!this->input->getText().empty()) {
            this->input->draw();
        }
    }
}

[[maybe_unused]] rfui::InContainer rfui::InPrompt::getInput() {
    if (this->visible) {
        std::string tempString;
        rfui::moveCursorTo(this->input->getX(), this->input->getY());
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

rfui::InField::InField(int x, int y, int w, int h, int bgColor, int fgColor) {
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

void rfui::InField::setVisible(bool isVisible) {
    if (isVisible) {
        this->visible = true;
        this->draw();
    } else {
        this->visible = false;
        rfui::clearArea(this->x, this->y, this->width, this->height, this->bgColor);
    }
}

void rfui::InField::draw() {
    // Draw background
    rfui::clearArea(this->x, this->y, this->width, this->height, this->bgColor);
    // Draw content
    this->display.draw();
    // Reset text features
    rfui::resetTextFeatures();
    rfui::moveCursorToBottom();
}

void rfui::InField::update() {
    this->display.draw();
    // Reset text features
    rfui::resetTextFeatures();
    rfui::moveCursorToBottom();

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


std::vector<rfui::InContainer> rfui::InField::getInput(int entries) {
    if (this->visible) {
        // Reset
        this->data.clear();
        this->display.getLines().clear();
        this->update();
        // Get input
        std::string tempString;
        for (int i = 0; i < entries; ++i) {
            rfui::moveCursorTo(this->getX(), this->getY());
            rfui::setBgColor(this->getBgColor()); rfui::setFgColor(this->getFgColor());
            rfui::setInverse(true);
            std::cin >> tempString;
            rfui::resetTextFeatures();
            this->data.emplace_back(tempString);
            this->addStr(tempString);
            this->update();
        }
        return this->data;
    }

    return {};
}



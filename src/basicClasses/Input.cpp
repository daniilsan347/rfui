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
void rfui::InPrompt::print() {
    if (this->visible) {
        // Print prompt
        this->promptLabel->print();
        // Print input
        if (!this->input->getText().empty()) {
            this->input->print();
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
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
    this->title = new Label(x + 1, y, std::move(title), fgColor, bgColor);
    this->title->setUnderlined(true);
    this->rootBgColor = 0;
}

rfui::Widget::~Widget() {
    for (auto label:this->labels) {
        delete label;
    }
    for (auto inPrompt:this->inPrompts) {
        delete inPrompt;
    }
}

// Widget setters
[[maybe_unused]] void rfui::Widget::setSize(int w, int h) {
    this->erase();
    this->width = w; this->height = h;
    this->draw();
}

[[maybe_unused]] void rfui::Widget::setPosition(int wX, int wY) {
    this->setVisible(false);
    int offX, offY;
    offX = this->x - wX; offY = this->y - wY;
    this->x = wX; this->y = wY;
    this->title->setPosition(this->title->getX()+offX, this->title->getY()+offY);
    for (auto label: labels) label->setPosition(label->getX() + offX, label->getY() + offY);
    for (auto inPrompt: inPrompts) inPrompt->setPosition(inPrompt->getX() + offX, inPrompt->getY() + offY);
    this->setVisible(true);
}

void rfui::Widget::setVisible(bool isVisible) {
    if (isVisible) {
        this->visible = true;
        this->drawBg();
        this->title->setVisible(true);
        for (auto label: labels) label->setVisible(isVisible);
        for (auto inPrompt: inPrompts) inPrompt->setVisible(isVisible);
    }
    else {
        this->visible = false;
        this->title->setVisible(false);
        for (auto label: labels) label->setVisible(false);
        for (auto inPrompt: inPrompts) inPrompt->setVisible(false);
        this->erase();
    }
}

// Widget methods
void rfui::Widget::draw() {
    if (this->visible) {
        // Draw Widget
        // Move cursor and set colors
        rfui::hideCursor(true);
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
        // Draw inPrompts
        for (auto *inPrompt : this->inPrompts) inPrompt->print();
        rfui::resetTextFeatures();
        rfui::moveCursorToBottom();
        rfui::hideCursor(false);
    }
}

void rfui::Widget::drawBg() const {
    if (this->visible) {
        // Draw Widget
        // Move cursor and set colors
        rfui::moveCursorTo(this->x, this->y);
        rfui::setBgColor(this->rootBgColor);
        rfui::setFgColor(this->fgColor);
        // Draw background
        for (int i = 0; i < this->height; i++) {
            std::cout << "\x1B[" << this->x << "G";
            for (int j = 0; j < this->width; j++) std::cout << ' ';
            std::cout << std::endl;
        }
        rfui::resetTextFeatures();
        rfui::moveCursorToBottom();
    }
}

void rfui::Widget::erase() const {
    if (this->visible) {
        // Erase widget
        // Move cursor and set colors
        rfui::moveCursorTo(this->x, this->y);
        rfui::setBgColor(this->rootBgColor);
        // Remove background of Widget
        for (int i = 0; i < this->height; i++) {
            std::cout << "\x1B[" << this->x << "G";
            for (int j = 0; j < this->width; j++) std::cout << ' ';
            std::cout << std::endl;
        }

        rfui::resetTextFeatures();
        rfui::moveCursorToBottom();
    }
}

void rfui::Widget::addLabel(Label *label) {
    int lX, lY;
    label->getPosition(lX, lY);
    label->setPosition(lX + this->x + 1, lY + this->y + 1);
    if (label->getBgColor() == 0) label->setBgColor(this->bgColor);
    if (label->getFgColor() == 0) label->setFgColor(this->fgColor);
    this->labels.push_back(label);
}

[[maybe_unused]] void rfui::Widget::addInput(InPrompt *inPrompt) {
    int iPX, iPY;
    inPrompt->getPosition(iPX, iPY);
    inPrompt->setPosition(iPX + this->x + 1, iPY + this->y + 1);
    if (inPrompt->getBgColor() == 0) inPrompt->setBgColor(this->bgColor);
    if (inPrompt->getFgColor() == 0) inPrompt->setFgColor(this->fgColor);
    this->inPrompts.push_back(inPrompt);
}
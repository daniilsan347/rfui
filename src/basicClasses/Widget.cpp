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
    delete this->title;
    for (auto label:this->labels) {
        delete label;
    }
    for (auto inPrompt:this->inPrompts) {
        delete inPrompt;
    }
    for (auto inField:this->inFields) {
        delete inField;
    }
    for (auto textField:this->textFields) {
        delete textField;
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
    offX = wX - this->x; offY = wY - this->y;
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
        this->title->setVisible(false);
        for (auto label: labels) label->setVisible(false);
        for (auto inPrompt: inPrompts) inPrompt->setVisible(false);
        this->erase();
        this->visible = false;
    }
}

// Widget methods
void rfui::Widget::draw() {
    if (this->visible) {
        // Draw Widget
        rfui::clearArea(this->x, this->y, this->width, this->height, this->bgColor);
        rfui::setFgColor(this->fgColor);
        // Draw title
        this->title->draw();
        // Draw labels
        for (auto *label : this->labels) label->draw();
        // Draw textFields
        for (auto *textField : this->textFields) textField->draw();
        // Draw inPrompts
        for (auto *inPrompt : this->inPrompts) inPrompt->draw();
        rfui::resetTextFeatures();
        rfui::moveCursorToBottom();
    }
}

void rfui::Widget::drawBg() const {
    if (this->visible) {
        // Draw Widget
        rfui::clearArea(this->x, this->y, this->width, this->height, this->bgColor);
        rfui::resetTextFeatures();
        rfui::moveCursorToBottom();
    }
}

void rfui::Widget::erase() const {
    if (this->visible) {
        // Erase widget
        rfui::clearArea(this->x, this->y, this->width, this->height, this->rootBgColor);
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

void rfui::Widget::addTextField(rfui::TextField *field) {
    int tfX, tfY;
    field->getPosition(tfX, tfY);
    field->setPosition(tfX + this->x + 1, tfY + this->y + 1);
    if (field->getWidth() >= this->width) field->setWidth(this->width - 2);
    if (field->getBgColor() == 0) field->setBgColor(this->bgColor);
    if (field->getFgColor() == 0) field->setFgColor(this->fgColor);
    this->textFields.push_back(field);
}

void rfui::Widget::addInput(rfui::InField *input) {
    int ifX = input->getX(), ifY = input->getY();
    input->setPosition(ifX + this->x + 1, ifY + this->y);
    if (input->getWidth() >= this->width) input->setWidth(this->width - 2);
    if (input->getBgColor() == 0) input->setBgColor(this->bgColor);
    if (input->getFgColor() == 0) input->setFgColor(this->fgColor);
    this->inFields.push_back(input);
}

void rfui::Widget::setBgColor(int color) {
    this->bgColor = color;
    this->title->setBgColor(color);
    for (auto label: labels) if(!label->getBgColor()) label->setBgColor(color);
    for (auto inPrompt: inPrompts) if(!inPrompt->getBgColor()) inPrompt->setBgColor(color);
    for (auto textField: textFields) if(!textField->getBgColor()) textField->setBgColor(color);
    for (auto inField: inFields) if(!inField->getBgColor()) inField->setBgColor(color);
}

void rfui::Widget::setFgColor(int color) {
    this->fgColor = color;
    this->title->setFgColor(color);
    for (auto label: labels) if(!label->getFgColor()) label->setFgColor(color);
    for (auto inPrompt: inPrompts) if(!inPrompt->getFgColor()) inPrompt->setFgColor(color);
    for (auto textField: textFields) if(!textField->getFgColor()) textField->setFgColor(color);
    for (auto inField: inFields) if(!inField->getFgColor()) inField->setFgColor(color);
}

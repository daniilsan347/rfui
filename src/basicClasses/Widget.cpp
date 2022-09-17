//
// Created by daniilsan on 25.08.2022.
//

#include <string>

#include "Widget.h"
#include "Label.h"
#include "rfui.h"

rfui::Widget::Widget(int height, int width, int x, int y, std::string title, int fgColor, int bgColor) {
    this->height = height;
    this->width = width;
    this->x = x;
    this->y = y;
    this->bgColor = bgColor;
    this->fgColor = fgColor;
    this->visible = true;
    this->title = new Label(x + 1, y, std::move(title), fgColor, bgColor);
    this->title->setUnderlined(true);
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
    this->width = w; this->height = h;
}

[[maybe_unused]] void rfui::Widget::setPosition(int wX, int wY) {
    int offX, offY;
    offX = wX - this->x; offY = wY - this->y;
    this->x = wX; this->y = wY;

    this->title->setPosition(this->title->getX()+offX, this->title->getY()+offY);
    for (auto label: labels) label->setPosition(label->getX() + offX, label->getY() + offY);
    for (auto textField: textFields) textField->setPosition(textField->getX() + offX, textField->getY() + offY);
    for (auto inPrompt: inPrompts) inPrompt->setPosition(inPrompt->getX() + offX, inPrompt->getY() + offY);
    for (auto inField: inFields) inField->setPosition(inField->getX() + offX, inField->getY() + offY);
}

//void rfui::Widget::setVisible(bool isVisible) {
//    if (isVisible) {
//        this->visible = true;
//        this->drawBg();
//        this->title->setVisible(true);
//        for (auto label: labels) label->setVisible(isVisible);
//        for (auto inPrompt: inPrompts) inPrompt->setVisible(isVisible);
//    }
//    else {
//        this->title->setVisible(false);
//        for (auto label: labels) label->setVisible(false);
//        for (auto inPrompt: inPrompts) inPrompt->setVisible(false);
//        this->erase();
//        this->visible = false;
//    }
//}

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

// Add elements function
// Adds Label object to "labels" vector in Widget
void rfui::Widget::addLabel(Label *label) {
    int lX, lY;
    label->getPosition(lX, lY);
    label->setPosition(lX + this->x, lY + this->y);
    if (label->getBgColor() == 0) label->setBgColor(this->bgColor);
    if (label->getFgColor() == 0) label->setFgColor(this->fgColor);
    this->labels.push_back(label);
}

// Adds TextField object to "textFields" vector in Widget
void rfui::Widget::addTextField(rfui::TextField *field) {
    int tfX, tfY;
    field->getPosition(tfX, tfY);
    field->setPosition(tfX + this->x, tfY + this->y);
    if (field->getWidth() >= this->width) field->setWidth(this->width - 2);
    if (field->getBgColor() == 0) field->setBgColor(this->bgColor);
    if (field->getFgColor() == 0) field->setFgColor(this->fgColor);
    this->textFields.push_back(field);
}

// Adds InPrompt object to "inPrompts" vector in Widget
void rfui::Widget::addInput(InPrompt *inPrompt) {
    int iPX, iPY;
    inPrompt->getPosition(iPX, iPY);
    inPrompt->setPosition(iPX + this->x, iPY + this->y);
    if (inPrompt->getBgColor() == 0) inPrompt->setBgColor(this->bgColor);
    if (inPrompt->getFgColor() == 0) inPrompt->setFgColor(this->fgColor);
    this->inPrompts.push_back(inPrompt);
}

// Adds InField object to "inFields" vector in Widget
void rfui::Widget::addInput(rfui::InField *input) {
    int ifX = input->getX(), ifY = input->getY();
    input->setPosition(ifX + this->x, ifY + this->y);
    if (input->getWidth() >= this->width) input->setWidth(this->width - 2);
    if (input->getHeight() > this->height - 1) input->setHeight(this->height - 1);
    if (input->getBgColor() == 0) input->setBgColor(this->bgColor);
    if (input->getFgColor() == 0) input->setFgColor(this->fgColor);
    this->inFields.push_back(input);
}

void rfui::Widget::draw(rfui::BufferCell **buffer) {
    if (!this->visible) return;

    // Put widget colours to the buffer
    for (int i = this->y; i < this->y + this->height; i++) {
        for (int j = this->x; j < this->x + this->width; j++) {
            buffer[i][j].bgColor = this->bgColor;
            buffer[i][j].fgColor = this->fgColor;
        }
    }

    // Call draw() method for all elements
    this->title->draw(buffer);
    for (auto label: this->labels) label->draw(buffer);
    for (auto textField: this->textFields) textField->draw(buffer);
    for (auto inPrompt: this->inPrompts) inPrompt->draw(buffer);
    for (auto inField: this->inFields) inField->draw(buffer);
}

//
// Created by daniilsan on 25.08.2022.
//

#include "Root.h"
#include "Widget.h"
#include "rfui.h"

#include <fmt/format.h>

using fmt::print;

rfui::Root::Root(int lines, int cols, int fgColor, int bgColor) {
    this->lines = lines;
    this->columns = cols;
    this->fgColor = fgColor;
    this->bgColor = bgColor;
    this->buffer = new BufferCell *[lines];
    for (int i = 0; i < lines; i++) {
        this->buffer[i] = new BufferCell[cols];
    }
}

rfui::Root::~Root() {
    for (auto& widget : this->widgets) {
        delete widget;
    }
    for (int i = 0; i < this->lines; i++) {
        delete[] this->buffer[i];
    }
    delete[] this->buffer;
}

void rfui::Root::addWidget(Widget* widget) {
    if (!widget->getBgColor()) widget->setBgColor(this->bgColor);
    if (!widget->getFgColor()) widget->setFgColor(this->fgColor);
    this->widgets.push_back(widget);
}

//void rfui::Root::draw() {
//    // Draw root
//    // Move cursor and set colours
//    rfui::moveCursorToTop();
//    rfui::setBgColor(this->bgColor);
//    rfui::setFgColor(this->fgColor);
//    // Draw background
//    for (int i = 0; i < this->lines; i++) {
//        print("\x1B[1G";
//        for (int j = 0; j < this->columns; j++) print(' ';
//        print(std::endl;
//    }
//    rfui::resetTextFeatures();
//    // Draw widgets
//    for (auto widget : this->widgets) {
//        widget->draw();
//    }
//    rfui::moveCursorToBottom();
//}

void rfui::BufferCell::reset() {
    this->bold = false;
    this->italic = false;
    this->underlined = false;
    this->dim = false;
    this->inverse = false;
    this->fgColor = 0;
    this->bgColor = 0;
    this->symbol = " ";
}

void rfui::Root::draw() {
    // Fill buffer with Root colours
    for (int i = 0; i < this->lines; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->buffer[i][j].reset();
            this->buffer[i][j].bgColor = this->bgColor;
            this->buffer[i][j].fgColor = this->fgColor;
        }
    }

    // Call Widgets drawing function
    for (auto wid:this->widgets) {
        wid->draw(this->buffer);
    }

    // Draw buffer on screen
    rfui::hideCursor(true);
    rfui::moveCursorToTop();
    BufferCell prevCell;
    for (int i = 0; i < this->lines; i++) {
        print("\x1B[1G");
        for (int j = 0; j < this->columns; j++) {
            if (i == 0 && j == 0) {
                prevCell = this->buffer[i][j];
                rfui::setFgColor(prevCell.fgColor);
                rfui::setBgColor(prevCell.bgColor);
                rfui::setTextFeatures(prevCell.bold, prevCell.italic, prevCell.underlined,
                                      prevCell.dim, prevCell.inverse);
            } else {
                if (prevCell.fgColor != this->buffer[i][j].fgColor) rfui::setFgColor(this->buffer[i][j].fgColor);
                if (prevCell.bgColor != this->buffer[i][j].bgColor) rfui::setBgColor(this->buffer[i][j].bgColor);
                if (prevCell.bold != this->buffer[i][j].bold) rfui::setBold(this->buffer[i][j].bold);
                if (prevCell.italic != this->buffer[i][j].italic) rfui::setItalic(this->buffer[i][j].italic);
                if (prevCell.underlined != this->buffer[i][j].underlined) rfui::setUnderlined(this->buffer[i][j].underlined);
                if (prevCell.dim != this->buffer[i][j].dim) rfui::setDim(this->buffer[i][j].dim);
                if (prevCell.inverse != this->buffer[i][j].inverse) rfui::setInverse(this->buffer[i][j].inverse);
                prevCell = this->buffer[i][j];
            }
            print("{}", this->buffer[i][j].symbol);
        }
        if (i != this->lines - 1) std::putchar('\n');
    }
    rfui::hideCursor(false);
}

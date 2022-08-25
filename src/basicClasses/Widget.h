//
// Created by daniilsan on 25.08.2022.
//

#ifndef DSTUI_WIDGET_H
#define DSTUI_WIDGET_H

#include <iostream>
#include <vector>

#include "Label.h"

namespace rfui {

    class Widget {
    private:
        int height, width;
        int x, y;
        int bgColor, fgColor;
        bool visible;
        rfui::Label *title;
        std::vector<rfui::Label *> labels;
    public:
        Widget(int height, int width, int x, int y, std::string title, int bgColor = 0, int fgColor = 0);
        // Widget setters
        void setSize(int w, int h) {this->width = w; this->height = h; };
        void setPosition(int wX, int wY) { this->x = wX; this->y = wY; };
        void setBgColor(int color) { this->bgColor = color; };
        void setFgColor(int color) { this->fgColor = color; };
        void setVisible(bool isVisible) { this->visible = isVisible; };
        // Widget getters
        void getSize(int &w, int &h) {w = this->width; h = this->height; };
        void getPosition(int &wX, int &wY) { wX = this->x; wY = this->y; };
        [[nodiscard]] int getBgColor() const {return this->bgColor; };
        [[nodiscard]] int getFgColor() const {return this->fgColor; };
        bool isVisible() {return this->visible; };
        // Widget methods
        void draw();
        void addLabel(rfui::Label *label);

    };

} // rfui

#endif //DSTUI_WIDGET_H

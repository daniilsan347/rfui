//
// Created by daniilsan on 25.08.2022.
//

#ifndef DSTUI_WIDGET_H
#define DSTUI_WIDGET_H

#include <iostream>
#include <vector>

#include "Label.h"
#include "Input.h"
#include "Root.h"

namespace rfui {

    class Widget {
    private:
        int height, width;
        int x, y;
        int bgColor, fgColor;
        int rootBgColor;
        bool visible;
        Label *title;
        std::vector<Label *> labels;
        std::vector<InPrompt *> inPrompts;
    public:
        Widget(int height, int width, int x, int y, std::string title, int bgColor = 0, int fgColor = 0);
        ~Widget();
        // Widget setters
        void setRootBg(int c) { this->rootBgColor = c; };
        [[maybe_unused]] [[maybe_unused]] void setSize(int w, int h);
        [[maybe_unused]] [[maybe_unused]] void setPosition(int wX, int wY);
        [[maybe_unused]] void setBgColor(int color)       { this->bgColor = color;     this->draw(); };
        [[maybe_unused]] void setFgColor(int color)       { this->fgColor = color;     this->draw(); };
        [[maybe_unused]] void setVisible(bool isVisible);
        // Widget getters
        [[maybe_unused]] void getSize(int &w, int &h)       const { w = this->width; h = this->height; };
        [[maybe_unused]] void getPosition(int &wX, int &wY) const { wX = this->x; wY = this->y;        };
        [[maybe_unused]] [[nodiscard]] int getBgColor()     const { return this->bgColor;              };
        [[maybe_unused]] [[nodiscard]] int getFgColor()     const { return this->fgColor;              };
        [[maybe_unused]] [[nodiscard]] bool isVisible()     const { return this->visible;              };
        // Widget methods
        void draw();
        void drawBg() const;
        void erase() const;
        void addLabel(Label *label);
        [[maybe_unused]] void addInput(InPrompt *input);
//        void addInput(InField *input);

    };

} // rfui

#endif //DSTUI_WIDGET_H

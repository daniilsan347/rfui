//
// Created by daniilsan on 25.08.2022.
//

#ifndef DSTUI_WIDGET_H
#define DSTUI_WIDGET_H

#include <iostream>
#include <vector>

#include "Label.h"
#include "TextField.h"
#include "Input.h"
#include "Root.h"

namespace rfui {
    struct BufferCell;

    class Widget {
    private:
        int height, width;
        int x, y;
        int bgColor, fgColor;
        bool visible;
        Label *title;
        std::vector<Label *> labels;
        std::vector<TextField *> textFields;
        std::vector<InPrompt *> inPrompts;
        std::vector<InField *> inFields;
    public:
        Widget(int height, int width, int x, int y, std::string title, int fgColor = 0, int bgColor = 0);
        ~Widget();
        // Widget setters
        [[maybe_unused]] [[maybe_unused]] void setSize(int w, int h);
        [[maybe_unused]] [[maybe_unused]] void setPosition(int wX, int wY);
        [[maybe_unused]] void setBgColor(int color);
        [[maybe_unused]] void setFgColor(int color);
        [[maybe_unused]] void setTitle(std::string text) { this->title->setText(std::move(text)); };
        [[maybe_unused]] void setVisible(bool isVisible) { this->visible = isVisible; };
        // Widget getters
        [[maybe_unused]] void getSize(int &w, int &h)       const { w = this->width; h = this->height; };
        [[maybe_unused]] void getPosition(int &wX, int &wY) const { wX = this->x; wY = this->y;        };
        [[maybe_unused]] [[nodiscard]] int getBgColor()     const { return this->bgColor;              };
        [[maybe_unused]] [[nodiscard]] int getFgColor()     const { return this->fgColor;              };
        [[maybe_unused]] [[nodiscard]] bool isVisible()     const { return this->visible;              };
        // Widget methods
        void draw(BufferCell **buffer);

        [[maybe_unused]] void addLabel(Label *label);
        [[maybe_unused]] void addTextField(TextField *field);
        [[maybe_unused]] void addInput(InPrompt *input);
        [[maybe_unused]] void addInput(InField *input);

    };

} // rfui

#endif //DSTUI_WIDGET_H

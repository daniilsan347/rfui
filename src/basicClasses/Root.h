//
// Created by daniilsan on 25.08.2022.
//

#ifndef DSTUI_ROOT_H
#define DSTUI_ROOT_H

#include <vector>

#include "Widget.h"

namespace rfui {

    class Root {
    private:
        int lines, columns;
        std::vector<Widget *> widgets;
        int bgColor, fgColor;
    public:
        Root(int lines, int cols, int bgColor = 0, int fgColor = 0);
        ~Root();
        void addWidget(Widget *widget);
        void getSize(int &h, int &w) const {h = this->lines; w = this->columns; };
        void draw();
        auto operator[](int i) { return this->widgets[i]; };
    };

} // rfui

#endif //DSTUI_ROOT_H

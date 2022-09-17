//
// Created by daniilsan on 25.08.2022.
//

#ifndef DSTUI_ROOT_H
#define DSTUI_ROOT_H

#include <vector>
#include <string>

namespace rfui {
    class Widget;

    struct BufferCell {
        bool bold;
        bool italic;
        bool underlined;
        bool dim;
        bool inverse;
        int fgColor;
        int bgColor;
        std::string symbol;

        void reset();
    };

    class Root {
    private:
        int lines, columns;
        std::vector<Widget *> widgets;
        int bgColor, fgColor;
        BufferCell **buffer;
    public:
        Root(int lines, int cols, int fgColor = 0, int bgColor = 0);
        ~Root();
        void addWidget(Widget *widget);
        void getSize(int &h, int &w) const { h = this->lines; w = this->columns; };
        void draw();
        auto operator[](int i) { return this->widgets[i]; };
        BufferCell **accessBuffer() { return this->buffer; };
    };
} // rfui

#endif //DSTUI_ROOT_H

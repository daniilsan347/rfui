//
// Created by daniilsan on 01.09.2022.
//

#ifndef DSTUI_TEXTFIELD_H
#define DSTUI_TEXTFIELD_H

#include "Label.h"
#include <vector>

namespace rfui {
    struct BufferCell;

    class TextField {
    private:
        int x, y;
        int w, h;
        bool bold = false;
        bool italic = false;
        bool underlined = false;
        bool visible = true;
        int fgColor, bgColor;
        std::vector <std::string> lines;
    public:
        TextField();
        TextField(int x, int y, int w, int h, int fgColor = 0, int bgColor = 0);
        // Getters
        void getPosition(int &tfX, int &tfY) const {tfX = this->x; tfY = this->y;};
        [[nodiscard]] int getX() const {return this->x;};
        [[nodiscard]] int getY() const {return this->y;};
        [[nodiscard]] int getWidth() const {return this->w;};
        [[nodiscard]] int getHeight() const {return this->h;};
        [[nodiscard]] int getFgColor() const {return this->fgColor;};
        [[nodiscard]] int getBgColor() const {return this->bgColor;};
        std::vector<std::string> &getLines() {return this->lines;};
        // Setters
        void setVisible(bool isVisible) {this->visible = isVisible;};
        void setPosition(int tfX, int tfY) {this->x = tfX; this->y = tfY;};
        void setFgColor(int color) {this->fgColor = color;};
        void setBgColor(int color) {this->bgColor = color;};
        void setBold(bool isBold) {this->bold = isBold;};
        void setItalic(bool isItalic) {this->italic = isItalic;};
        void setUnderlined(bool isUnderline) {this->underlined = isUnderline;};
        void setWidth(int width) {this->w = width;};
        void setHeight(int height) {this->h = height;};
        // Methods
        void addStr(const std::string &str);
        void draw(BufferCell **buffer);
        std::string& operator[](size_t index) {return lines[index];};
    };
}

#endif //DSTUI_TEXTFIELD_H

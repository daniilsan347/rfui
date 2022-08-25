//
// Created by daniilsan on 23.08.2022.
//

#ifndef DSTUI_LABEL_H
#define DSTUI_LABEL_H

#include <string>
#include <utility>

namespace rfui {

    class Label {
    private:
        int x, y;
        bool bold;
        bool italic;
        bool underlined;
        bool visible;
        int fgColor;
        int bgColor;
        std::string text;
    public:
        Label(int x, int y, std::string text, int fgColor = 0, int bgColor = 0);
        // Getters
        void getPosition(int &lX, int &lY) const { lX = this->x; lY = this->y; };
        [[nodiscard]] int getX() const { return this->x; };
        [[nodiscard]] int getY() const { return this->y; };
        [[nodiscard]] int getFgColor() const { return this->fgColor; };
        [[nodiscard]] int getBgColor() const { return this->bgColor; };
        [[nodiscard]] std::string getText() const { return this->text; };
        // Setters
        void setPosition(int lX, int lY) { this->x = lX; this->y = lY; };
        void setFgColor(int color) { this->fgColor = color; };
        void setBgColor(int color) { this->bgColor = color; };
        void setBold(bool isBold) { this->bold = isBold; };
        void setItalic(bool isItalic) { this->italic = isItalic; };
        void setUnderlined(bool isUnderline) { this->underlined = isUnderline; };
        void setVisible(bool isVisible) { this->visible = isVisible; };
        void setText(std::string newText) { this->text = std::move(newText); };

        void print();
    };

} // rfui

#endif //DSTUI_LABEL_H

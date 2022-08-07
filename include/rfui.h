//
// Created by daniilsan on 24.07.2022.
//

#ifndef DSTUI_RFUI_H
#define DSTUI_RFUI_H

#include <string>

namespace rfui {
    void getTerminalSize(int &width, int &height);
    void getTerminalCursorPosition(int &x, int &y);
    void clearScreen();
    void moveCursorTo(int x, int y);
    void moveCursorToBottom();
    int setFgColor(int color);
    int setBgColor(int color);
    void setBold(bool bold);
    void setItalic(bool italic);
    void setUnderlined(bool underlined);
    void resetTextFeatures();

    // Color references
    namespace C {
        namespace BG {
            const int BLACK = 40;
            const int RED = 41;
            const int GREEN = 42;
            const int YELLOW = 43;
            const int BLUE = 44;
            const int MAGENTA = 45;
            const int CYAN = 46;
            const int WHITE = 47;
        }
        namespace FG {
            const int BLACK = 30;
            const int RED = 31;
            const int GREEN = 32;
            const int YELLOW = 33;
            const int BLUE = 34;
            const int MAGENTA = 35;
            const int CYAN = 36;
            const int WHITE = 37;
        }
    }

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
        Label(int x, int y, std::string text, int fgColor, int bgColor);
        void setBold(bool isBold) { this->bold = isBold;};
        void setItalic(bool isItalic) { this->italic = isItalic;};
        void setUnderlined(bool isUnderline) { this->underlined = isUnderline;};
        void setVisible(bool isVisible) { this->visible = isVisible;};

        void print();
    };

    class Widget {
    private:
        int height, width;
        int x, y;
        int bgColor, fgColor;
        bool visible;
        rfui::Label *title;
        rfui::Label *labels[];
    public:
        Widget(int height, int width, int x, int y, int bgColor, int fgColor, std::string title);
        // Widget setters
        void setSize(int w, int h) {this->width = w; this->height = h;};
        void setPosition(int wX, int wY) { this->x = wX; this->y = wY;};
        void setBgColor(int color) { this->bgColor = color;};
        void setFgColor(int color) { this->fgColor = color;};
        void setVisible(bool isVisible) { this->visible = isVisible;};
        // Widget getters
        void getSize(int &w, int &h) {w = this->width; h = this->height;};
        void getPosition(int &wX, int &wY) { wX = this->x; wY = this->y;};
        int  getBgColor() {return this->bgColor;};
        int  getFgColor() {return this->fgColor;};
        bool isVisible() {return this->visible;};
        // Widget methods
        void draw();
        void addLabel(rfui::Label *label);

    };



} // namespace rfui

#endif //DSTUI_RFUI_H

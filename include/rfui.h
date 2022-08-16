//
// Created by daniilsan on 24.07.2022.
//

#ifndef DSTUI_RFUI_H
#define DSTUI_RFUI_H

#include <string>
#include <vector>

namespace rfui {
    void init();
    void getTerminalSize(int &width, int &height);
    void getTerminalCursorPosition(int &x, int &y);
    void clearScreen();
    void moveCursorTo(int x, int y);
    void moveCursorToTop();
    void moveCursorToBottom();
    int setFgColor(int color);
    int setBgColor(int color);
    void setBold(bool bold);
    void setItalic(bool italic);
    void setUnderlined(bool underlined);
    void resetTextFeatures();
    void pause();

    // Color references
    namespace C {
        namespace BG {
            const int BLK = 40;
            const int RED = 41;
            const int GRN = 42;
            const int YEL = 43;
            const int BLU = 44;
            const int MAG = 45;
            const int CYN = 46;
            const int WHT = 47;
            const int NONE = 0;
        }
        namespace FG {
            const int BLK = 30;
            const int RED = 31;
            const int GRN = 32;
            const int YEL = 33;
            const int BLU = 34;
            const int MAG = 35;
            const int CYN = 36;
            const int WHT = 37;
            const int NONE = 0;
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
        Label(int x, int y, std::string text, int fgColor);
        Label(int x, int y, std::string text);
        // Getters
        void getPosition(int &lX, int &lY) const { lX = this->x; lY = this->y; };
        int getFgColor() { return this->fgColor; };
        int getBgColor() { return this->bgColor; };
        // Setters
        void setPosition(int lX, int lY) { this->x = lX; this->y = lY; };
        void setFgColor(int color) { this->fgColor = color; };
        void setBgColor(int color) { this->bgColor = color; };
        void setBold(bool isBold) { this->bold = isBold; };
        void setItalic(bool isItalic) { this->italic = isItalic; };
        void setUnderlined(bool isUnderline) { this->underlined = isUnderline; };
        void setVisible(bool isVisible) { this->visible = isVisible; };

        void print();
    };

    class Widget {
    private:
        int height, width;
        int x, y;
        int bgColor, fgColor;
        bool visible;
        rfui::Label *title;
        std::vector<rfui::Label *> labels;
    public:
        Widget(int height, int width, int x, int y, int bgColor, int fgColor, std::string title);
        // Widget setters
        void setSize(int w, int h) {this->width = w; this->height = h; };
        void setPosition(int wX, int wY) { this->x = wX; this->y = wY; };
        void setBgColor(int color) { this->bgColor = color; };
        void setFgColor(int color) { this->fgColor = color; };
        void setVisible(bool isVisible) { this->visible = isVisible; };
        // Widget getters
        void getSize(int &w, int &h) {w = this->width; h = this->height; };
        void getPosition(int &wX, int &wY) { wX = this->x; wY = this->y; };
        int  getBgColor() {return this->bgColor; };
        int  getFgColor() {return this->fgColor; };
        bool isVisible() {return this->visible; };
        // Widget methods
        void draw();
        void addLabel(rfui::Label *label);

    };

    class Root {
    private:
        int lines, columns;
        std::vector<Widget *> widgets;
        int bgColor, fgColor;
    public:
        Root(int lines, int cols, int bgColor = 0, int fgColor = 0);
        ~Root();
        void addWidget(Widget *widget);
        void draw();
    };


} // namespace rfui

#endif //DSTUI_RFUI_H

//
// Created by daniilsan on 24.07.2022.
//

#ifndef DSTUI_RFUI_H
#define DSTUI_RFUI_H

#include "../src/basicClasses.h"

namespace rfui {
    class Label;
    class Root;
    class Widget;

    void init();
    void getTerminalSize(int &width, int &height);
    void getTerminalCursorPosition(int &x, int &y);
    void clearScreen();
    void moveCursorTo(int x, int y);
    void moveCursorToTop();
    void moveCursorToBottom();
    void hideCursor(bool hide);
    int  setFgColor(int color);
    int  setBgColor(int color);
    void setBold(bool bold);
    void setDim(bool dim);
    void setItalic(bool italic);
    void setUnderlined(bool underlined);
    void setInverse(bool inverse);
    void resetTextFeatures();
    [[maybe_unused]] void pause(rfui::Root &root);
    int strLenUtf8(const std::string &str);

    // Color references
    namespace C {
        namespace BG {
            [[maybe_unused]] const int BLK = 40;
            [[maybe_unused]] const int RED = 41;
            [[maybe_unused]] const int GRN = 42;
            [[maybe_unused]] const int YEL = 43;
            [[maybe_unused]] const int BLU = 44;
            [[maybe_unused]] const int MAG = 45;
            [[maybe_unused]] const int CYN = 46;
            [[maybe_unused]] const int WHT = 47;
            [[maybe_unused]] const int NONE = 0;
        }
        namespace FG {
            [[maybe_unused]] const int BLK = 30;
            [[maybe_unused]] const int RED = 31;
            [[maybe_unused]] const int GRN = 32;
            [[maybe_unused]] const int YEL = 33;
            [[maybe_unused]] const int BLU = 34;
            [[maybe_unused]] const int MAG = 35;
            [[maybe_unused]] const int CYN = 36;
            [[maybe_unused]] const int WHT = 37;
            [[maybe_unused]] const int NONE = 0;
        }
    }
} // namespace rfui

#endif //DSTUI_RFUI_H

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
    int  setFgColor(int color);
    int  setBgColor(int color);
    void setBold(bool bold);
    void setDim(bool dim);
    void setItalic(bool italic);
    void setUnderlined(bool underlined);
    void setInverse(bool inverse);
    void resetTextFeatures();
    void pause(rfui::Root &root);

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



} // namespace rfui

#endif //DSTUI_RFUI_H

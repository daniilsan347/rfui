// RedFox User Interface

#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <locale>
#endif
#include "rfui.h"

namespace rfui {
    // Initialisation function
    void init() {
        #ifdef _WIN32
            SetConsoleOutputCP(65001);
        #else
            std::locale::global(std::locale("en_US.UTF-8"));
        #endif
    }
    // Get terminal size
    void getTerminalSize(int &width, int &height) {
        #ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        #else
            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
            width = w.ws_col;
            height = w.ws_row;
        #endif
    }
    // Get terminal cursor position
    void getTerminalCursorPosition(int &x, int &y) {
        #ifdef _WIN32
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            x = csbi.dwCursorPosition.X;
            y = csbi.dwCursorPosition.Y;
        #else
            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
            x = w.ws_x;
            y = w.ws_y;
        #endif
    }
    // Clear screen
    void clearScreen() {
        std::cout << "\x1B[2J\x1B[H";
    }
    // Set terminal cursor position
    void moveCursorTo(int x, int y) {
        int tCol, tRow;
        getTerminalSize(tCol, tRow);

        if (x < 1) x = 1;
        else if (x > tCol) x = tCol;

        if (y < 1) y = 1;
        else if (y > tRow) y = tRow;

        std::cout << "\x1B[" << y << ";" << x << "f";
    }
    void moveCursorToTop() {
        moveCursorTo(1, 1);
    }
    void moveCursorToBottom() {
        int x, y;
        getTerminalSize(x, y);
        moveCursorTo(1, y);
    };
    // Set terminal color
    int setFgColor(int color) {
        if (color >= 30 && color <= 37) {
            std::cout << "\x1B[" << color << "m";
            return 0;
        } else {
            return 1;
        }
    }
    // Set terminal background color
    int setBgColor(int color) {
        if (color >= 40 && color <= 47) {
            std::cout << "\x1B[" << color << "m";
            return 0;
        } else {
            return 1;
        }
    }
    // Set terminal bold
    void setBold(bool bold) {
        if (bold) {
            std::cout << "\x1B[1m";
        }
    }
    // Set terminal italic
    void setItalic(bool italic) {
        if (italic) {
            std::cout << "\x1B[3m";
        }
    }
    // Set terminal underlined
    void setUnderlined(bool underlined) {
        if (underlined) {
            std::cout << "\x1B[4m";
        }
    }
    // Reset text features
    void resetTextFeatures() {
        std::cout << "\x1B[0m";
    }

    void pause() {
        do
        {
            std::cout << "Press [Enter] to continue...";
        } while (std::cin.get() != '\n');
    }

} // namespace rfui
// RedFox User Interface

#include <limits>

#include <fmt/format.h>
#include <cstdio>


#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <locale>
#endif
#include "rfui.h"

using fmt::print;

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
//    void getCursorPosition(int &x, int &y) {
//        #ifdef _WIN32
//            CONSOLE_SCREEN_BUFFER_INFO csbi;
//            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//            x = csbi.dwCursorPosition.X;
//            y = csbi.dwCursorPosition.Y;
//        #else
//            struct winsize w;
//            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
//            x = w.ws_x;
//            y = w.ws_y;
//        #endif
//    }
    // Clear screen
    void clearScreen() {
        print("\x1B[2J\x1B[H");
    }
    // Set terminal cursor position
    void moveCursorTo(int x, int y) {
        int tCol, tRow;
        getTerminalSize(tCol, tRow);

        if (x < 1) x = 1;
        else if (x > tCol) x = tCol;

        if (y < 1) y = 1;
        else if (y > tRow) y = tRow;

        print("\x1B[{};{}f", y, x);
    }
    // Move cursor to top left corner
    void moveCursorToTop() {
        moveCursorTo(1, 1);
    }
    // Move cursor to bottom left corner
    void moveCursorToBottom() {
        int x, y;
        getTerminalSize(x, y);
        moveCursorTo(1, y);
    }
    // Hide or show cursor
    void hideCursor(bool hide) {
        if (hide) print("\x1B[?25l");
        else print("\x1B[?25h");
    }

    // Set terminal colors
    // Set terminal color
    int setFgColor(int color) {
        if (color >= 30 && color <= 37) {
            print("\x1b[{}m", color);
            return 0;
        } else {
            return 1;
        }
    }
    // Set terminal background color
    int setBgColor(int color) {
        if (color >= 40 && color <= 47) {
            print("\x1b[{}m", color);
            return 0;
        } else {
            return 1;
        }
    }
    // Set terminal bold
    void setBold(bool bold) {
        if (bold) {
            print("\x1B[1m");
        } else {
            print("\x1B[22m");
        }
    }
    // Set terminal dim
    void setDim(bool dim) {
        if (dim) {
            print("\x1B[2m");
        } else {
            print("\x1B[22m");
        }
    }
    // Set terminal italic
    void setItalic(bool italic) {
        if (italic) {
            print("\x1B[3m");
        } else {
            print("\x1B[23m");
        }
    }
    // Set terminal underlined
    void setUnderlined(bool underlined) {
        if (underlined) {
            print("\x1B[4m");
        } else {
            print("\x1B[24m");
        }
    }
    // Set terminal inverse
    void setInverse(bool inverse) {
        if (inverse) {
            print("\x1B[7m");
        } else {
            print("\x1B[27m");
        }
    }
    // Set text features in one function
    void setTextFeatures(bool bold, bool italic, bool underlined, bool dim, bool inverse) {
        setBold(bold);
        setItalic(italic);
        setUnderlined(underlined);
        setDim(dim);
        setInverse(inverse);
    }

    // Reset text features
    void resetTextFeatures() {
        print("\x1B[0m");
    }

    [[maybe_unused]] void pause(rfui::Root &root) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int h, w;
        root.getSize(h, w);
        rfui::moveCursorTo(1, h+1);
        do
        {
            print("Press [Enter] to continue...");
        } while (std::cin.get() != '\n');
    }

    int strLenUtf8(const std::string &str) {
        int size = 0;
        // Get size of unicode encoded string
        for (char i : str) {
            if ((i & 0xC0) != 0x80) {
                size++;
            }
        }
        return size;
    }
    std::vector<std::string> splitUtf8(const std::string &str) {
        std::vector<std::string> result;
        std::string temp;
        // Split unicode encoded string
        for (char i : str) {
            if ((i & 0xC0) != 0x80) {
                if (!temp.empty()) {
                    result.push_back(temp);
                    temp.clear();
                }
            }
            temp += i;
        }
        if (!temp.empty()) {
            result.push_back(temp);
        }
        return result;
    }

    void clearArea(int x, int y, int width, int height, int color) {
        int tCol, tRow;
        getTerminalSize(tCol, tRow);

        // Check if area is out of bounds
        if (x < 1) x = 1;
        else if (x > tCol) x = tCol;

        if (y < 1) y = 1;
        else if (y > tRow) y = tRow;

        if (width < 1) width = 1;
        else if (width > tCol) width = tCol;

        if (height < 1) height = 1;
        else if (height > tRow) height = tRow;

        // Set cursor properties
        setBgColor(color);
        moveCursorTo(x, y);

        // Draw area
        for (int i = 0; i < height; i++) {
            moveCursorTo(x, y+i);
            for (int j = 0; j < width; j++) std::putchar(' ');
        }
        moveCursorToBottom();
    }

} // namespace rfui
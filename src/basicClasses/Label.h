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
        int len;
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
        void getPosition(int &lX, int &lY)  const { lX = this->x; lY = this->y; };
        [[nodiscard]] int getX()            const { return this->x;             };
        [[nodiscard]] int getY()            const { return this->y;             };
        [[nodiscard]] int getLen()          const { return this->len;           };
        [[nodiscard]] int getFgColor()      const { return this->fgColor;       };
        [[nodiscard]] int getBgColor()      const { return this->bgColor;       };
        [[nodiscard]] std::string getText() const { return this->text;          };
        // Setters
        void setPosition(int lX, int lY);
        void setFgColor(int color)           { this->fgColor    = color;       this->print();    };
        void setBgColor(int color)           { this->bgColor    = color;       this->print();    };
        void setBold(bool isBold)            { this->bold       = isBold;      this->print();    };
        void setItalic(bool isItalic)        { this->italic     = isItalic;    this->print();    };
        void setUnderlined(bool isUnderline) { this->underlined = isUnderline; this->print();    };
        void setVisible(bool isVisible);
        void setText(std::string newText)    { this->text = std::move(newText); this->print(); };

        // Methods
        void print();
        void erase() const;
    };

} // rfui

#endif //DSTUI_LABEL_H

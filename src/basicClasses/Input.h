//
// Created by daniilsan on 25.08.2022.
//

#ifndef DSTUI_INPUT_H
#define DSTUI_INPUT_H

#include <string>
#include <utility>
#include <vector>

#include "Label.h"
#include "TextField.h"

namespace rfui {
    struct BufferCell;
    class Root;

    class InContainer {
    private:
        std::string inputString;
    public:
        InContainer() = default;
        explicit InContainer(std::string inputString) : inputString(std::move(inputString)) {};
        InContainer& operator=(std::string str) { this->inputString = std::move(str); return *this;};
        // Getters for result
        [[maybe_unused]] [[nodiscard]] int getInt() const { return std::stoi(this->inputString); };
        [[maybe_unused]] [[nodiscard]] long getLong() const { return std::stol(this->inputString); };
        [[maybe_unused]] [[nodiscard]] long long getLongLong() const { return std::stoll(this->inputString); };
        [[maybe_unused]] [[nodiscard]] float getFloat() const { return std::stof(this->inputString); };
        [[maybe_unused]] [[nodiscard]] double getDouble() const { return std::stod(this->inputString); };
        [[maybe_unused]] [[nodiscard]] long double getLongDouble() const { return std::stold(this->inputString); };
        [[maybe_unused]] [[nodiscard]] bool getBool() const { return std::stoi(this->inputString) != 0; };
        [[maybe_unused]] [[nodiscard]] std::string getString() const { return this->inputString; };

    };

    class InPrompt {
    private:
        int x, y;
        Label *promptLabel;
        Label *input;
        InContainer data;
        int bgColor, fgColor;
        bool visible;
    public:
        InPrompt(int x, int y, std::string prompt = ">", int fgColor = 0, int bgColor = 0);
        ~InPrompt();
        // Setters
        [[maybe_unused]] void setPosition(int xPos, int yPos);
        [[maybe_unused]] void setPrompt(std::string prompt) { this->promptLabel->setText(std::move(prompt)); };
        [[maybe_unused]] void setBgColor(int color) { this->bgColor = color; promptLabel->setBgColor(color); input->setBgColor(color); };
        [[maybe_unused]] void setFgColor(int color) { this->fgColor = color; promptLabel->setFgColor(color); input->setFgColor(color); };
        [[maybe_unused]] void setVisible(bool isVisible) { this->visible = isVisible; };
        // Getters
        [[maybe_unused]] void getPosition(int &xPos, int &yPos) const { xPos = this->x; yPos = this->y; };
        [[maybe_unused]] [[nodiscard]] int getBgColor() const { return this->bgColor; };
        [[maybe_unused]] [[nodiscard]] int getFgColor() const { return this->fgColor; };
        [[maybe_unused]] [[nodiscard]] bool isVisible() const { return this->visible; };
        [[nodiscard]] int getX()                        const { return this->x;       };
        [[nodiscard]] int getY()                        const { return this->y;       };
        [[maybe_unused]] auto getData() {return this->data;};
        // Methods
        void draw(BufferCell **buffer);
        [[maybe_unused]] void reset() { this->input->setText(""); this->data = InContainer(); };
        [[maybe_unused]] InContainer getInput();
    };

    class InField {
    private:
        int x, y;
        int width, height;
        int bgColor, fgColor;
        bool visible = true;
        rfui::TextField display;
        std::vector<InContainer> data;
        void getEndPos(int &xPos, int &yPos);
    public:
        InField(int x, int y, int w, int h, int fgColor = 0, int bgColor = 0);
        // Setters
        void setPosition(int posX, int posY);
        void setBgColor(int color) { this->bgColor = color; this->display.setBgColor(color); };
        void setFgColor(int color) { this->fgColor = color; this->display.setFgColor(color); };
        void setWidth(int w) { this->width = w; this->display.setWidth(w); };
        void setHeight(int h) { this->height = h; this->display.setHeight(h); };
        void setVisible(bool isVisible) { this->visible = isVisible; };
        // Getters
        [[maybe_unused]] [[nodiscard]] int  getX()       const { return this->x;       };
        [[maybe_unused]] [[nodiscard]] int  getY()       const { return this->y;       };
        [[maybe_unused]] [[nodiscard]] int  getWidth()   const { return this->width;   };
        [[maybe_unused]] [[nodiscard]] int  getHeight()  const { return this->height;  };
        [[maybe_unused]] [[nodiscard]] int  getBgColor() const { return this->bgColor; };
        [[maybe_unused]] [[nodiscard]] int  getFgColor() const { return this->fgColor; };
        [[maybe_unused]] [[nodiscard]] bool isVisible()  const { return this->visible; };
        [[maybe_unused]] [[nodiscard]] std::vector<InContainer> getData() const { return this->data; };
        //Methods
        void addStr(const std::string& str) { this->display.addStr(str);};
        void draw(BufferCell **buffer);
        [[maybe_unused]] void reset();
        [[maybe_unused]] std::vector<InContainer> getInput(int entries, Root *root);

    };

} // rfui

#endif //DSTUI_INPUT_H

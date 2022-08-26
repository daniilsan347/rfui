//
// Created by daniilsan on 25.08.2022.
//

#ifndef DSTUI_INPUT_H
#define DSTUI_INPUT_H

#include <string>
#include <utility>
#include <vector>

#include "Label.h"

namespace rfui {

    class InContainer {
    private:
        std::string inputString;
    public:
        InContainer() = default;
        explicit InContainer(std::string inputString) : inputString(std::move(inputString)) {};
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
        InPrompt(int x, int y, std::string prompt = ">", int bgColor = 0, int fgColor = 0);
        ~InPrompt();
        // Setters
        [[maybe_unused]] void setPosition(int xPos, int yPos);
        [[maybe_unused]] void setPrompt(std::string prompt) { this->promptLabel->setText(std::move(prompt)); };
        [[maybe_unused]] void setBgColor(int color) { this->bgColor = color; };
        [[maybe_unused]] void setFgColor(int color) { this->fgColor = color; };
        [[maybe_unused]] void setVisible(bool isVisible);
        // Getters
        [[maybe_unused]] void getPosition(int &xPos, int &yPos) const { xPos = this->x; yPos = this->y; };
        [[maybe_unused]] [[nodiscard]] int getBgColor() const { return this->bgColor; };
        [[maybe_unused]] [[nodiscard]] int getFgColor() const { return this->fgColor; };
        [[maybe_unused]] [[nodiscard]] bool isVisible() const { return this->visible; };
        [[nodiscard]] int getX()                        const { return this->x;       };
        [[nodiscard]] int getY()                        const { return this->y;       };
        // Methods
        [[maybe_unused]] void print();
        [[maybe_unused]] InContainer getInput();
        // Input conversions
        [[maybe_unused]] [[nodiscard]] int getInt() const { return this->data.getInt(); };
        [[maybe_unused]] [[nodiscard]] long getLong() const { return this->data.getLong(); };
        [[maybe_unused]] [[nodiscard]] long long getLongLong() const { return this->data.getLongLong(); };
        [[maybe_unused]] [[nodiscard]] float getFloat() const { return this->data.getFloat(); };
        [[maybe_unused]] [[nodiscard]] double getDouble() const { return this->data.getDouble(); };
        [[maybe_unused]] [[nodiscard]] long double getLongDouble() const { return this->data.getLongDouble(); };
        [[maybe_unused]] [[nodiscard]] bool getBool() const { return this->data.getBool(); };
        [[maybe_unused]] [[nodiscard]] std::string getString() const { return this->data.getString(); };

    };

    class InField {

    };

} // rfui

#endif //DSTUI_INPUT_H

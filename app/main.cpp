#include "rfui.h"
#include <cmath>
#include <vector>




int main() {
    rfui::init();
    rfui::clearScreen();

    rfui::Root root(30, 120, rfui::C::BG::WHT, rfui::C::FG::BLK);
    auto header = new rfui::Widget(1, 120, 1, 1, "Тест", rfui::C::BG::RED);
    root.addWidget(header);

    auto inputs = new rfui::Widget(4, 120, 1, 2, "Ввід", rfui::C::BG::BLU);
    auto prompt = new rfui::InPrompt(0, 0, "Одностроковий:");
    auto field  = new rfui::InField(0,1,120,2);
    inputs->addInput(prompt); inputs->addInput(field);
    root.addWidget(inputs);

    auto outputs = new rfui::Widget(4, 120, 1, 7, "Вивід", rfui::C::BG::GRN);
    auto aLabel = new rfui::Label(0, 0, "Prompt: ");
    auto textField = new rfui::TextField(0, 1, 120, 2);
    outputs->addLabel(aLabel); outputs->addTextField(textField);
    root.addWidget(outputs);

    root.draw();

    auto promptResult = prompt->getInput().getInt();
    aLabel->setText("Prompt: " + std::to_string(promptResult));
    aLabel->draw();

    auto fieldResult = field->getInput(4); // fix me: cursed InField draw
    for (auto &i : fieldResult) {
        textField->addText(i.getString());
    }
    return 0;
}

#include "Banner.hpp"
#include "Application.hpp"

int app::Application::getLuckyNumber() const {
    return this->luckyNumber;
}

void app::Application::doSth(int somenumber) {
    std::cout << "Hello people!" << std::endl;
}
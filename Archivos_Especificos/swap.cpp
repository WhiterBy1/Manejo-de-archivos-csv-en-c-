#include <iostream>
#include <utility>  // Necesario para usar swap

int main() {
    int x = 5;
    int y = 10;
    std::swap(x, y);
    std::cout << "x = " << x << ", y = " << y << std::endl;  // x = 10, y = 5
    return 0;
}
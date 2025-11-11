#include <iostream>
#include <string>

int main() {
    std::string input;
    
    while (true) {
        // Чтение строки
        std::getline(std::cin, input);
        
        // Печать введенной строки
        std::cout << input << std::endl;
        
        // Выход если введено "exit"
        if (input == "exit") {
            break;
        }
    }
    
    return 0;
}
#include <iostream>
#include <string>

int main() {
    std::string input;
    
    std::cout << "Введите строки (Ctrl+D для выхода):" << std::endl;
    
    while (true) {
        
        std::cout << "> ";
        
        
        if (!std::getline(std::cin, input)) {
            
            break;
        }
        
        
        std::cout << input << std::endl;
    }
    
    std::cout << "Выход из программы" << std::endl;
    return 0;
}
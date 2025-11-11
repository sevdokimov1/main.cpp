#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

class ShellWithHistory {
private:
    std::vector<std::string> history;
    std::string history_file;

public:
    ShellWithHistory() {
        const char* home_dir = getenv("HOME");
        if (home_dir) {
            history_file = std::string(home_dir) + "/.kubsh_history";
        } else {
            history_file = ".kubsh_history";
        }
        loadHistory();
    }

    void run() {
        std::string input;
        
        std::cout << "Введите строки (\\q или Ctrl+D для выхода):" << std::endl;
        
        while (true) {
            std::cout << "> ";
            
            if (!std::getline(std::cin, input)) {
                break;
            }
            
            if (input == "\\q") {
                break;
            }
            
            if (input.find("echo ") == 0) {
                processEcho(input);
            } else if (!input.empty()) {
                addToHistory(input);
                std::cout << input << std::endl;
            }
        }
        
        saveHistory();
        std::cout << "Выход из программы" << std::endl;
    }

private:
    void processEcho(const std::string& input) {
        std::string text = input.substr(5);
        
        if ((text.front() == '"' && text.back() == '"') || 
            (text.front() == '\'' && text.back() == '\'')) {
            text = text.substr(1, text.length() - 2);
        }
        
        addToHistory(input);
        std::cout << text << std::endl;
    }
    
    void addToHistory(const std::string& command) {
        history.push_back(command);
    }
    
    void loadHistory() {
        std::ifstream file(history_file);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty()) {
                    history.push_back(line);
                }
            }
            file.close();
            std::cout << "Загружено " << history.size() << " команд из истории" << std::endl;
        }
    }
    
    void saveHistory() {
        std::ofstream file(history_file);
        if (file.is_open()) {
            for (const auto& command : history) {
                file << command << std::endl;
            }
            file.close();
            std::cout << "Сохранено " << history.size() << " команд в историю" << std::endl;
        } else {
            std::cerr << "Ошибка: не удалось сохранить историю в файл " << history_file << std::endl;
        }
    }
};

int main() {
    ShellWithHistory shell;
    shell.run();
    return 0;
}
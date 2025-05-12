#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <filesystem>

// ANSI Color Codes
namespace Color {
    const std::string Reset = "\033[0m";
    const std::string Red = "\033[31m";
    const std::string Green = "\033[32m";
    const std::string Yellow = "\033[33m";
    const std::string Blue = "\033[34m";
    const std::string Magenta = "\033[35m";
    const std::string Cyan = "\033[36m";
    const std::string White = "\033[37m";
}

class RandomStringGenerator {
private:
    const int MAX_LENGTH = 32;
    std::string configPath;

    // Generiert einen zufälligen String
    std::string generateRandomString(int length) {
        const std::string characters = 
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> distribution(0, characters.length() - 1);

        std::string randomStr;
        for (int i = 0; i < length; ++i) {
            randomStr += characters[distribution(generator)];
        }
        return randomStr;
    }

    // Speichert Konfiguration
    void saveConfig(const std::string& key, int value) {
        std::filesystem::path appDataPath = std::filesystem::path(std::getenv("APPDATA")) / "CamGen";
        std::filesystem::create_directories(appDataPath);
        
        // Temporäre Datei zum Speichern der Konfiguration
        std::filesystem::path tempPath = appDataPath / "temp_config.txt";
        std::ofstream tempFile(tempPath);
        
        // Vorhandene Konfiguration lesen und aktualisieren
        std::ifstream configFile(appDataPath / "config.txt");
        std::string line;
        bool keyFound = false;
        
        while (std::getline(configFile, line)) {
            size_t delimPos = line.find('=');
            if (delimPos != std::string::npos) {
                std::string configKey = line.substr(0, delimPos);
                if (configKey == key) {
                    // Schlüssel gefunden, neuen Wert speichern
                    tempFile << key << "=" << value << std::endl;
                    keyFound = true;
                } else {
                    // Andere Schlüssel unverändert übernehmen
                    tempFile << line << std::endl;
                }
            }
        }
        
        // Wenn Schlüssel nicht gefunden, neuen Schlüssel hinzufügen
        if (!keyFound) {
            tempFile << key << "=" << value << std::endl;
        }
        
        tempFile.close();
        configFile.close();
        
        // Temporäre Datei durch Konfigurationsdatei ersetzen
        std::filesystem::rename(tempPath, appDataPath / "config.txt");
    }

    // Liest Konfiguration
    int readConfig(const std::string& key, int defaultValue) {
        std::filesystem::path appDataPath = std::filesystem::path(std::getenv("APPDATA")) / "CamGen" / "config.txt";
        
        // Überprüfen, ob Konfigurationsdatei existiert
        if (!std::filesystem::exists(appDataPath)) {
            return defaultValue;
        }
        
        std::ifstream configFile(appDataPath);
        std::string line;
        while (std::getline(configFile, line)) {
            size_t delimPos = line.find('=');
            if (delimPos != std::string::npos) {
                std::string configKey = line.substr(0, delimPos);
                int configValue = std::stoi(line.substr(delimPos + 1));
                if (configKey == key) {
                    return configValue;
                }
            }
        }
        return defaultValue;
    }

public:
    RandomStringGenerator() {
        configPath = (std::filesystem::path(std::getenv("APPDATA")) / "CamGen" / "config.txt").string();
    }

    // Option 1: Name mit zufälligem String
    void generateNameWithRandomString() {
        int randomLength = readConfig("nameRandomLength", -1);
        
        if (randomLength == -1) {
            std::cout << Color::Cyan << "Enter the length of the random string (max. " << MAX_LENGTH << "): " << Color::Reset;
            std::cin >> randomLength;
            saveConfig("nameRandomLength", randomLength);
        }

        // Correct length if too large
        randomLength = std::min(randomLength, MAX_LENGTH);

        std::string userName;
        std::cout << Color::Cyan << "Enter cam name: " << Color::Reset;
        std::cin >> userName;

        std::string randomStr = generateRandomString(randomLength);
        
        // Ensure total length does not exceed 32 characters
        if (userName.length() + randomStr.length() > MAX_LENGTH) {
            randomStr = randomStr.substr(0, MAX_LENGTH - userName.length());
        }

        std::string result = userName + randomStr;
        std::cout << Color::Green << "Generated string: " << result << Color::Reset << std::endl;
    }

    // Option 2: Nur zufälliger String
    void generateOnlyRandomString() {
        int randomLength = readConfig("onlyRandomLength", -1);
        
        if (randomLength == -1) {
            std::cout << Color::Cyan << "Enter the length of the random string (max. " << MAX_LENGTH << "): " << Color::Reset;
            std::cin >> randomLength;
            saveConfig("onlyRandomLength", randomLength);
        }

        // Correct length if too large
        randomLength = std::min(randomLength, MAX_LENGTH);

        std::string randomStr = generateRandomString(randomLength);
        std::cout << Color::Green << "Generated string: " << randomStr << Color::Reset << std::endl;
    }

    // Option 3: Konfiguration ändern
    void modifyConfiguration() {
        int choice;
        std::cout << Color::Yellow << "What would you like to change?\n";
        std::cout << "1. Length for name with random string\n";
        std::cout << "2. Length for only random string\n";
        std::cout << "Your choice: " << Color::Reset;
        std::cin >> choice;

        int newLength;
        std::cout << Color::Cyan << "Enter the new length (max. " << MAX_LENGTH << "): " << Color::Reset;
        std::cin >> newLength;

        if (choice == 1) {
            saveConfig("nameRandomLength", newLength);
            std::cout << Color::Green << "Length for name with random string updated.\n" << Color::Reset;
        } else if (choice == 2) {
            saveConfig("onlyRandomLength", newLength);
            std::cout << Color::Green << "Length for only random string updated.\n" << Color::Reset;
        } else {
            std::cout << Color::Red << "Invalid selection.\n" << Color::Reset;
        }
    }

    // Option 4: Name mit zufälligem String (ohne Speicherung)
    void generateNameWithRandomStringNoSave() {
        int randomLength;
        std::cout << Color::Cyan << "Enter the length of the random string (max. " << MAX_LENGTH << "): " << Color::Reset;
        std::cin >> randomLength;

        // Correct length if too large
        randomLength = std::min(randomLength, MAX_LENGTH);

        std::string userName;
        std::cout << Color::Cyan << "Enter cam name: " << Color::Reset;
        std::cin >> userName;

        std::string randomStr = generateRandomString(randomLength);
        
        // Ensure total length does not exceed 32 characters
        if (userName.length() + randomStr.length() > MAX_LENGTH) {
            randomStr = randomStr.substr(0, MAX_LENGTH - userName.length());
        }

        std::string result = userName + randomStr;
        std::cout << Color::Green << "Generated string: " << result << Color::Reset << std::endl;
    }

    // Option 5: Only random string (without saving)
    void generateOnlyRandomStringNoSave() {
        int randomLength;
        std::cout << Color::Cyan << "Enter the length of the random string (max. " << MAX_LENGTH << "): " << Color::Reset;
        std::cin >> randomLength;

        // Correct length if too large
        randomLength = std::min(randomLength, MAX_LENGTH);

        std::string randomStr = generateRandomString(randomLength);
        std::cout << Color::Green << "Generated string: " << randomStr << Color::Reset << std::endl;
    }
};

int main() {
    RandomStringGenerator generator;
    int choice;

    while (true) {
        std::cout << Color::Magenta << "\n--- CamGen ---\n";
        std::cout << "1. Name with random string (saved)\n";
        std::cout << "2. Only random string (saved)\n";
        std::cout << "3. Modify configuration\n";
        std::cout << "4. Name with random string (without saving)\n";
        std::cout << "5. Only random string (without saving)\n";
        std::cout << "0. Exit\n";
        std::cout << "Your choice: " << Color::Reset;
        std::cin >> choice;

        switch (choice) {
            case 1: generator.generateNameWithRandomString(); break;
            case 2: generator.generateOnlyRandomString(); break;
            case 3: generator.modifyConfiguration(); break;
            case 4: generator.generateNameWithRandomStringNoSave(); break;
            case 5: generator.generateOnlyRandomStringNoSave(); break;
            case 0: 
                std::cout << Color::Yellow << "Program terminated.\n" << Color::Reset;
                return 0;
            default:
                std::cout << Color::Red << "Invalid selection. Please try again.\n" << Color::Reset;
        }
    }

    return 0;
}

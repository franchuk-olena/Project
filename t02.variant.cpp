#include <iostream>
#include <variant>

// Структура для представлення вартості в гривнях та копійках
struct HryvniasAndKopecks {
    int hryvnias; // Гривні
    int kopecks;  // Копійки (0-99)
};

// Структура для представлення вартості лише в копійках
struct TotalKopecks {
    int totalKopecks; // Загальна кількість копійок
};

// Тип для універсального грошового представлення
using Money = std::variant<HryvniasAndKopecks, TotalKopecks>;

// Функція для перетворення з гривень і копійок у копійки
int toTotalKopecks(const HryvniasAndKopecks& money) {
    return money.hryvnias * 100 + money.kopecks;
}

// Функція для перетворення з копійок у гривні та копійки
HryvniasAndKopecks toHryvniasAndKopecks(int totalKopecks) {
    HryvniasAndKopecks result;
    result.hryvnias = totalKopecks / 100;
    result.kopecks = totalKopecks % 100;
    return result;
}

// Функція для виведення грошової вартості
void printMoney(const Money& money, bool inKopecks = false) {
    if (inKopecks) {
        // Якщо потрібно вивести в копійках
        if (std::holds_alternative<TotalKopecks>(money)) {
            std::cout << "Вартість: " << std::get<TotalKopecks>(money).totalKopecks << " коп.\n";
        } else {
            int kopecks = toTotalKopecks(std::get<HryvniasAndKopecks>(money));
            std::cout << "Вартість: " << kopecks << " коп.\n";
        }
    } else {
        // Якщо потрібно вивести в гривнях та копійках
        if (std::holds_alternative<HryvniasAndKopecks>(money)) {
            const auto& h = std::get<HryvniasAndKopecks>(money);
            std::cout << "Вартість: " << h.hryvnias << " грн " << h.kopecks << " коп.\n";
        } else {
            HryvniasAndKopecks h = toHryvniasAndKopecks(std::get<TotalKopecks>(money).totalKopecks);
            std::cout << "Вартість: " << h.hryvnias << " грн " << h.kopecks << " коп.\n";
        }
    }
}

int main() {
    // Введення вартості у гривнях та копійках
    std::cout << "Введіть вартість у гривнях та копійках (наприклад, 5 75): ";
    HryvniasAndKopecks inputHryvnias;
    std::cin >> inputHryvnias.hryvnias >> inputHryvnias.kopecks;

    // Збереження у типі Money
    Money money1 = inputHryvnias;

    // Виведення у гривнях та копійках
    printMoney(money1);

    // Виведення у копійках
    printMoney(money1, true);

    // Введення вартості у копійках
    std::cout << "Введіть вартість у копійках (наприклад, 575): ";
    int inputKopecks;
    std::cin >> inputKopecks;

    // Збереження у типі Money
    Money money2 = TotalKopecks{inputKopecks};

    // Виведення у гривнях та копійках
    printMoney(money2);

    // Виведення у копійках
    printMoney(money2, true);

    return 0;
}

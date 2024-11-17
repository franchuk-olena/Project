#include <stdio.h>

typedef struct {
    int hryvnias; // Гривні
    int kopecks;  // Копійки (0-99)
} HryvniasAndKopecks;

typedef struct {
    int totalKopecks; // Загальна кількість копійок
} TotalKopecks;

typedef union {
    HryvniasAndKopecks asHryvnias; // Представлення у гривнях та копійках
    TotalKopecks asKopecks;        // Представлення лише у копійках
} Money;

// Функція перетворення з гривень і копійок у копійки
int toTotalKopecks(int hryvnias, int kopecks) {
    return hryvnias * 100 + kopecks;
}

// Функція перетворення з копійок у гривні та копійки
HryvniasAndKopecks toHryvniasAndKopecks(int totalKopecks) {
    HryvniasAndKopecks result;
    result.hryvnias = totalKopecks / 100;
    result.kopecks = totalKopecks % 100;
    return result;
}

// Виведення грошової вартості
void printMoney(const Money* money, int asKopecks) {
    if (asKopecks) {
        printf("Вартість: %d коп.\n", money->asKopecks.totalKopecks);
    } else {
        printf("Вартість: %d грн %d коп.\n", money->asHryvnias.hryvnias, money->asHryvnias.kopecks);
    }
}

int main() {
    Money money;

    // Введення вартості у гривнях і копійках
    int hryvnias, kopecks;
    printf("Введіть вартість у форматі гривні та копійки (наприклад, 5 75): ");
    scanf("%d %d", &hryvnias, &kopecks);

    // Перевірка коректності введених копійок
    if (kopecks < 0 || kopecks >= 100) {
        printf("Помилка: копійки повинні бути від 0 до 99.\n");
        return 1;
    }

    // Зберігаємо дані у `union` у вигляді гривень і копійок
    money.asHryvnias.hryvnias = hryvnias;
    money.asHryvnias.kopecks = kopecks;

    // Виведення у гривнях і копійках
    printMoney(&money, 0);

    // Перетворення у копійки
    money.asKopecks.totalKopecks = toTotalKopecks(hryvnias, kopecks);

    // Виведення у копійках
    printMoney(&money, 1);

    // Введення вартості у копійках
    int totalKopecks;
    printf("Введіть вартість у копійках (наприклад, 575): ");
    scanf("%d", &totalKopecks);

    // Перетворення у гривні та копійки
    money.asHryvnias = toHryvniasAndKopecks(totalKopecks);

    // Виведення у гривнях і копійках
    printMoney(&money, 0);

    return 0;
}

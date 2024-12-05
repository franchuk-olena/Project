//У цій задачі визначається тип, що дозволяє зберігати число або будь-якого числового типу (double, int, unsigned,...) або рядки «Нескінченість» та
//«Невизначеність». Реалізовуються арифметичні операції для цього типу які коректно працюють з діленням та іншими операціями для всіх можливих
//комбінаціях значень та типів. За допомогою variant.
#include <iostream>
#include <variant>
#include <string>
#include <optional>
#include <ctime>  // Для вимірювання часу

// Визначаємо тип даних, який може містити різні числові типи або рядки
using Number = std::variant<int, double, unsigned, std::string>;

// Функція для зчитування числа з консолі
Number readNumber() {
    int typeChoice;
    std::cout << "Оберіть тип числа:\n"
              << "1 - Int\n2 - Double\n3 - Unsigned\n4 - Спеціальне значення\n";
    std::cin >> typeChoice;

    switch(typeChoice) {
        case 1: {
            int value;
            std::cout << "Введіть ціле число: ";
            std::cin >> value;
            return value;
        }
        case 2: {
            double value;
            std::cout << "Введіть дробове число: ";
            std::cin >> value;
            return value;
        }
        case 3: {
            unsigned value;
            std::cout << "Введіть беззнакове число: ";
            std::cin >> value;
            return value;
        }
        case 4: {
            std::string value;
            std::cout << "Введіть значення (Нескінченість/Невизначеність): ";
            std::cin >> value;
            return value;
        }
        default:
            return std::string("Невизначеність");
    }
}

// Функція для виведення числа
struct NumberPrinter {
    void operator()(int value) const { std::cout << value; }
    void operator()(double value) const { std::cout << value; }
    void operator()(unsigned value) const { std::cout << value; }
    void operator()(const std::string& value) const { std::cout << value; }
};

// Функція для отримання числового значення
struct NumberGetter {
    std::optional<double> operator()(int value) const { return value; }
    std::optional<double> operator()(double value) const { return value; }
    std::optional<double> operator()(unsigned value) const { return value; }
    std::optional<double> operator()(const std::string&) const { return std::nullopt; }
};

// Функція для виконання арифметичної операції
Number performOperation(const Number& a, const Number& b, char operation) {
    auto val1 = std::visit(NumberGetter{}, a);
    auto val2 = std::visit(NumberGetter{}, b);

    if (!val1 || !val2) {
        return std::string("Невизначеність");
    }

    switch(operation) {
        case '+':
            return *val1 + *val2;
        case '-':
            return *val1 - *val2;
        case '*':
            return *val1 * *val2;
        case '/':
            if (*val2 == 0) {
                return std::string("Нескінченість");
            }
            return *val1 / *val2;
        default:
            return std::string("Невизначеність");
    }
}

int main() {

    // Початок вимірювання часу
    clock_t start_time = clock();

    std::cout << "Введіть перше число:\n";
    Number a = readNumber();

    char operation;
    std::cout << "Введіть операцію (+, -, *, /): ";
    std::cin >> operation;

    std::cout << "Введіть друге число:\n";
    Number b = readNumber();

    Number result = performOperation(a, b, operation);

    std::cout << "Результат: ";
    std::visit(NumberPrinter{}, result);
    std::cout << '\n';

    // Кінець вимірювання часу
    clock_t end_time = clock();

    // Обчислення часу виконання
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Час виконання: %.6f секунд\n", time_taken);

    return 0;
}

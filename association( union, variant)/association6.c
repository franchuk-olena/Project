//У цій задачі визначається тип, що дозволяє зберігати число або будь-якого числового типу (double, int, unsigned,...) або рядки «Нескінченість» та
//«Невизначеність». Реалізовуються арифметичні операції для цього типу які коректно працюють з діленням та іншими операціями для всіх можливих
//комбінаціях значень та типів. За допомогою union.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>  // Для вимірювання часу

// Оголошення типів значень
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_UNSIGNED,
    TYPE_STRING
} ValueType;


// Структура для зберігання різних типів значень
typedef struct {
    ValueType type;
    union {
        int i;  // Для цілого числа
        double d; // Для дробового числа
        unsigned u; // Для беззнакового числа
        char str[50]; // Для рядка (максимум 49 символів)
    } value;
} Number;


// Функція для введення числа з консолі
Number readNumber() {
    Number num;
    int typeChoice;

    printf("Оберіть тип числа:\n");
    printf("1 - Int\n2 - Double\n3 - Unsigned\n4 - Спеціальне значення\n");
    scanf("%d", &typeChoice);

    switch(typeChoice) {
        case 1:
            num.type = TYPE_INT;
            printf("Введіть ціле число: ");
            scanf("%d", &num.value.i);
            break;
        case 2:
            num.type = TYPE_DOUBLE;
            printf("Введіть дробове число: ");
            scanf("%lf", &num.value.d);
            break;
        case 3:
            num.type = TYPE_UNSIGNED;
            printf("Введіть беззнакове число: ");
            scanf("%u", &num.value.u);
            break;
        case 4:
            num.type = TYPE_STRING;
            printf("Введіть значення (Нескінченість/Невизначеність): ");
            scanf("%49s", num.value.str);  // Обмежуємо введення для запобігання переповнення
            break;
    }
    return num;
}

void printNumber(Number num) {
    switch(num.type) {
        case TYPE_INT:
            printf("%d", num.value.i);
            break;
        case TYPE_DOUBLE:
            printf("%f", num.value.d);
            break;
        case TYPE_UNSIGNED:
            printf("%u", num.value.u);
            break;
        case TYPE_STRING:
            printf("%s", num.value.str);
            break;
    }
}

Number performOperation(Number a, Number b, char operation) {
    Number result;

    // Якщо хоча б одне значення - рядок
    if (a.type == TYPE_STRING || b.type == TYPE_STRING) {
        result.type = TYPE_STRING;
        strncpy(result.value.str, "Невизначеність", 49);
        result.value.str[49] = '\0';  // Забезпечуємо нуль-термінацію
        return result;
    }

    // Конвертуємо все в double для спрощення операцій
    double val1, val2;

    switch(a.type) {
        case TYPE_INT: val1 = (double)a.value.i; break;
        case TYPE_DOUBLE: val1 = a.value.d; break;
        case TYPE_UNSIGNED: val1 = (double)a.value.u; break;
        default: val1 = 0;
    }

    switch(b.type) {
        case TYPE_INT: val2 = (double)b.value.i; break;
        case TYPE_DOUBLE: val2 = b.value.d; break;
        case TYPE_UNSIGNED: val2 = (double)b.value.u; break;
        default: val2 = 0;
    }

    double res;
    switch(operation) {
        case '+':
            res = val1 + val2;
            break;
        case '-':
            res = val1 - val2;
            break;
        case '*':
            res = val1 * val2;
            break;
        case '/':
            if (val2 == 0) {
                result.type = TYPE_STRING;
                strncpy(result.value.str, "Нескінченість", 49);
                result.value.str[49] = '\0';
                return result;
            }
            res = val1 / val2;
            break;
        default:
            result.type = TYPE_STRING;
            strncpy(result.value.str, "Невизначеність", 49);
            result.value.str[49] = '\0';
            return result;
    }

    // Результат зберігаємо як double
    result.type = TYPE_DOUBLE;
    result.value.d = res;
    return result;
}

int main() {
    Number a, b, result;
    char operation;

    // Початок вимірювання часу
    clock_t start_time = clock();

    printf("Введіть перше число:\n");
    a = readNumber();

    printf("Введіть операцію (+, -, *, /): ");
    scanf(" %c", &operation);

    printf("Введіть друге число:\n");
    b = readNumber();

    result = performOperation(a, b, operation);

    printf("Результат: ");
    printNumber(result);
    printf("\n");

    // Кінець вимірювання часу
    clock_t end_time = clock();

    // Обчислення часу виконання
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Час виконання: %.6f секунд\n", time_taken);

    return 0;
}

//� ��� ������ ����������� ���, �� �������� �������� ����� ��� ����-����� ��������� ���� (double, int, unsigned,...) ��� ����� ������������� ��
//���������������. ������������� ���������� �������� ��� ����� ���� �� �������� �������� � ������� �� ������ ���������� ��� ��� ��������
//���������� ������� �� ����. �� ��������� variant.
#include <iostream>
#include <variant>
#include <string>
#include <optional>
#include <ctime>  // ��� ���������� ����

// ��������� ��� �����, ���� ���� ������ ��� ������ ���� ��� �����
using Number = std::variant<int, double, unsigned, std::string>;

// ������� ��� ���������� ����� � ������
Number readNumber() {
    int typeChoice;
    std::cout << "������ ��� �����:\n"
              << "1 - Int\n2 - Double\n3 - Unsigned\n4 - ���������� ��������\n";
    std::cin >> typeChoice;

    switch(typeChoice) {
        case 1: {
            int value;
            std::cout << "������ ���� �����: ";
            std::cin >> value;
            return value;
        }
        case 2: {
            double value;
            std::cout << "������ ������� �����: ";
            std::cin >> value;
            return value;
        }
        case 3: {
            unsigned value;
            std::cout << "������ ���������� �����: ";
            std::cin >> value;
            return value;
        }
        case 4: {
            std::string value;
            std::cout << "������ �������� (�����������/�������������): ";
            std::cin >> value;
            return value;
        }
        default:
            return std::string("�������������");
    }
}

// ������� ��� ��������� �����
struct NumberPrinter {
    void operator()(int value) const { std::cout << value; }
    void operator()(double value) const { std::cout << value; }
    void operator()(unsigned value) const { std::cout << value; }
    void operator()(const std::string& value) const { std::cout << value; }
};

// ������� ��� ��������� ��������� ��������
struct NumberGetter {
    std::optional<double> operator()(int value) const { return value; }
    std::optional<double> operator()(double value) const { return value; }
    std::optional<double> operator()(unsigned value) const { return value; }
    std::optional<double> operator()(const std::string&) const { return std::nullopt; }
};

// ������� ��� ��������� ����������� ��������
Number performOperation(const Number& a, const Number& b, char operation) {
    auto val1 = std::visit(NumberGetter{}, a);
    auto val2 = std::visit(NumberGetter{}, b);

    if (!val1 || !val2) {
        return std::string("�������������");
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
                return std::string("�����������");
            }
            return *val1 / *val2;
        default:
            return std::string("�������������");
    }
}

int main() {

    // ������� ���������� ����
    clock_t start_time = clock();

    std::cout << "������ ����� �����:\n";
    Number a = readNumber();

    char operation;
    std::cout << "������ �������� (+, -, *, /): ";
    std::cin >> operation;

    std::cout << "������ ����� �����:\n";
    Number b = readNumber();

    Number result = performOperation(a, b, operation);

    std::cout << "���������: ";
    std::visit(NumberPrinter{}, result);
    std::cout << '\n';

    // ʳ���� ���������� ����
    clock_t end_time = clock();

    // ���������� ���� ���������
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    printf("��� ���������: %.6f ������\n", time_taken);

    return 0;
}

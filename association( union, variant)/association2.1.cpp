// � ��� ������ ��������������� ������������ �������� ���, �� ���� ������������ ������� ��� � ������� �� �������, ��� ���� � ������� �� ��������� ���������� variant

// ������� ������������

//������ ������� � ������ ����� �� ������ (���������, 5 75): 5 75
//�������: 5 ��� 75 ���.
//�������: 575 ���.

//������ ������� � ������� (���������, 575): 575
//�������: 5 ��� 75 ���.



#include <iostream>
#include <variant>
#include <ctime> // ��� ���������� ����

// ��������� ��� ������������� ������� � ������� �� �������
struct HryvniasAndKopecks {
    int hryvnias; // �����
    int kopecks;  // ������ (0-99)
};

// ��������� ��� ������������� ������� ���� � �������
struct TotalKopecks {
    int totalKopecks; // �������� ������� ������
};

// ��� ��� ������������� ��������� �������������
using Money = std::variant<HryvniasAndKopecks, TotalKopecks>;

// ������� ��� ������������ � ������� � ������ � ������
int toTotalKopecks(const HryvniasAndKopecks& money) {
    return money.hryvnias * 100 + money.kopecks;
}

// ������� ��� ������������ � ������ � ����� �� ������
HryvniasAndKopecks toHryvniasAndKopecks(int totalKopecks) {
    HryvniasAndKopecks result;
    result.hryvnias = totalKopecks / 100;
    result.kopecks = totalKopecks % 100;
    return result;
}

// ������� ��� ��������� ������� �������
void printMoney(const Money& money, bool inKopecks = false) {
    if (inKopecks) {
        // ���� ������� ������� � �������
        if (std::holds_alternative<TotalKopecks>(money)) {
            std::cout << "�������: " << std::get<TotalKopecks>(money).totalKopecks << " ���.\n";
        } else {
            int kopecks = toTotalKopecks(std::get<HryvniasAndKopecks>(money));
            std::cout << "�������: " << kopecks << " ���.\n";
        }
    } else {
        // ���� ������� ������� � ������� �� �������
        if (std::holds_alternative<HryvniasAndKopecks>(money)) {
            const auto& h = std::get<HryvniasAndKopecks>(money);
            std::cout << "�������: " << h.hryvnias << " ��� " << h.kopecks << " ���.\n";
        } else {
            HryvniasAndKopecks h = toHryvniasAndKopecks(std::get<TotalKopecks>(money).totalKopecks);
            std::cout << "�������: " << h.hryvnias << " ��� " << h.kopecks << " ���.\n";
        }
    }
}

int main() {

    // ������� ���������� ����
    clock_t start_time = clock();

    // �������� ������� � ������� �� �������
    std::cout << "������ ������� � ������� �� ������� (���������, 5 75): ";
    HryvniasAndKopecks inputHryvnias;
    std::cin >> inputHryvnias.hryvnias >> inputHryvnias.kopecks;

    // ���������� � ��� Money
    Money money1 = inputHryvnias;

    // ��������� � ������� �� �������
    printMoney(money1);

    // ��������� � �������
    printMoney(money1, true);

    // �������� ������� � �������
    std::cout << "������ ������� � ������� (���������, 575): ";
    int inputKopecks;
    std::cin >> inputKopecks;

    // ���������� � ��� Money
    Money money2 = TotalKopecks{inputKopecks};

    // ��������� � ������� �� �������
    printMoney(money2);

    // ��������� � �������
    printMoney(money2, true);

    // ʳ���� ���������� ����
    clock_t end_time = clock();

    // ���������� ���� ���������
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "��� ����������: " << time_taken << " ������\n";

    return 0;
}

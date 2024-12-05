// � ��� ������ ��������������� ������������ �������� ���, �� ���� ������������ ������� ��� � ������� �� �������, ��� ���� � ������� �� ��������� union

// ������� ������������

//������ ������� � ������ ����� �� ������ (���������, 5 75): 5 75
//�������: 5 ��� 75 ���.
//�������: 575 ���.

//������ ������� � ������� (���������, 575): 575
//�������: 5 ��� 75 ���.



#include <stdio.h>
#include <time.h> // ��� ���������� ����

typedef struct {
    int hryvnias; // �����
    int kopecks;  // ������ (0-99)
} HryvniasAndKopecks;

typedef struct {
    int totalKopecks; // �������� ������� ������
} TotalKopecks;

typedef union {
    HryvniasAndKopecks asHryvnias; // ������������� � ������� �� �������
    TotalKopecks asKopecks;        // ������������� ���� � �������
} Money;

// ������� ������������ � ������� � ������ � ������
int toTotalKopecks(int hryvnias, int kopecks) {
    return hryvnias * 100 + kopecks;
}

// ������� ������������ � ������ � ����� �� ������
HryvniasAndKopecks toHryvniasAndKopecks(int totalKopecks) {
    HryvniasAndKopecks result;
    result.hryvnias = totalKopecks / 100;
    result.kopecks = totalKopecks % 100;
    return result;
}

// ��������� ������� �������
void printMoney(const Money* money, int asKopecks) {
    if (asKopecks) {
        printf("�������: %d ���.\n", money->asKopecks.totalKopecks);
    } else {
        printf("�������: %d ��� %d ���.\n", money->asHryvnias.hryvnias, money->asHryvnias.kopecks);
    }
}

int main() {
    Money money;

    // ������� ���������� ���� ��� ����������
    clock_t start_time = clock();

    // �������� ������� � ������� � �������
    int hryvnias, kopecks;
    printf("������ ������� � ������ ����� �� ������ (���������, 5 75): ");
    scanf("%d %d", &hryvnias, &kopecks);

    // �������� ���������� �������� ������
    if (kopecks < 0 || kopecks >= 100) {
        printf("�������: ������ ������ ���� �� 0 �� 99.\n");
        return 1;
    }

    // �������� ��� � `union` � ������ ������� � ������
    money.asHryvnias.hryvnias = hryvnias;
    money.asHryvnias.kopecks = kopecks;

    // ��������� � ������� � �������
    printMoney(&money, 0);

    // ������������ � ������
    money.asKopecks.totalKopecks = toTotalKopecks(hryvnias, kopecks);

    // ��������� � �������
    printMoney(&money, 1);

    // �������� ������� � �������
    int totalKopecks;
    printf("������ ������� � ������� (���������, 575): ");
    scanf("%d", &totalKopecks);

    // ������������ � ����� �� ������
    money.asHryvnias = toHryvniasAndKopecks(totalKopecks);

    // ��������� � ������� � �������
    printMoney(&money, 0);

    // ʳ���� ���������� ���� ��� ����������
    clock_t end_time = clock();

    //  ���
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("��� ����������: %.6f ������\n", time_taken);

    return 0;
}

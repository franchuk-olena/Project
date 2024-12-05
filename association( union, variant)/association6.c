//� ��� ������ ����������� ���, �� �������� �������� ����� ��� ����-����� ��������� ���� (double, int, unsigned,...) ��� ����� ������������� ��
//���������������. ������������� ���������� �������� ��� ����� ���� �� �������� �������� � ������� �� ������ ���������� ��� ��� ��������
//���������� ������� �� ����. �� ��������� union.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>  // ��� ���������� ����

// ���������� ���� �������
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_UNSIGNED,
    TYPE_STRING
} ValueType;


// ��������� ��� ��������� ����� ���� �������
typedef struct {
    ValueType type;
    union {
        int i;  // ��� ������ �����
        double d; // ��� ��������� �����
        unsigned u; // ��� ������������ �����
        char str[50]; // ��� ����� (�������� 49 �������)
    } value;
} Number;


// ������� ��� �������� ����� � ������
Number readNumber() {
    Number num;
    int typeChoice;

    printf("������ ��� �����:\n");
    printf("1 - Int\n2 - Double\n3 - Unsigned\n4 - ���������� ��������\n");
    scanf("%d", &typeChoice);

    switch(typeChoice) {
        case 1:
            num.type = TYPE_INT;
            printf("������ ���� �����: ");
            scanf("%d", &num.value.i);
            break;
        case 2:
            num.type = TYPE_DOUBLE;
            printf("������ ������� �����: ");
            scanf("%lf", &num.value.d);
            break;
        case 3:
            num.type = TYPE_UNSIGNED;
            printf("������ ���������� �����: ");
            scanf("%u", &num.value.u);
            break;
        case 4:
            num.type = TYPE_STRING;
            printf("������ �������� (�����������/�������������): ");
            scanf("%49s", num.value.str);  // �������� �������� ��� ���������� ������������
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

    // ���� ���� � ���� �������� - �����
    if (a.type == TYPE_STRING || b.type == TYPE_STRING) {
        result.type = TYPE_STRING;
        strncpy(result.value.str, "�������������", 49);
        result.value.str[49] = '\0';  // ����������� ����-���������
        return result;
    }

    // ���������� ��� � double ��� ��������� ��������
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
                strncpy(result.value.str, "�����������", 49);
                result.value.str[49] = '\0';
                return result;
            }
            res = val1 / val2;
            break;
        default:
            result.type = TYPE_STRING;
            strncpy(result.value.str, "�������������", 49);
            result.value.str[49] = '\0';
            return result;
    }

    // ��������� �������� �� double
    result.type = TYPE_DOUBLE;
    result.value.d = res;
    return result;
}

int main() {
    Number a, b, result;
    char operation;

    // ������� ���������� ����
    clock_t start_time = clock();

    printf("������ ����� �����:\n");
    a = readNumber();

    printf("������ �������� (+, -, *, /): ");
    scanf(" %c", &operation);

    printf("������ ����� �����:\n");
    b = readNumber();

    result = performOperation(a, b, operation);

    printf("���������: ");
    printNumber(result);
    printf("\n");

    // ʳ���� ���������� ����
    clock_t end_time = clock();

    // ���������� ���� ���������
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("��� ���������: %.6f ������\n", time_taken);

    return 0;
}

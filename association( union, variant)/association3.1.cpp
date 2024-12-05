//� ��� ������ ���������������  ������������ ���, �� �������� ������������ ������ � �� �� ����� �� �� ����� �� ������ �� ����� �����. ��������� ��� ������� ��
//������������ �� �������� ���� �� ��������� variant

//������ ���������� ����� ����� (x1 y1): 0 0
//������ ���������� ����� ����� (x2 y2): 1 1
//������ ���������� ������ ����� (x3 y3): 2 2
//������� ��������

//������ ���������� ����� ����� (x1 y1): 0 0
//������ ���������� ����� ����� (x2 y2): 1 1
//������ ���������� ������ ����� (x3 y3): 2 3
//������� �� ��������



#include <iostream>
#include <variant>
#include <cmath>
#include <ctime>  // ��� ���������� ����

// ��������� ��� �����
struct Point {
    float x, y;
};

// ������������ ��� ��� ����� ��� �������
using PointOrVector = std::variant<Point>;

// ������� ��� �������� ����������� ����� �����
bool areCollinear(const Point& p1, const Point& p2, const Point& p3) {
    float area = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    return std::fabs(area) < 1e-6;
}

int main() {
    // �������� ����� ����� ������������
    Point p1, p2, p3;

    // ������� ���������� ����
    clock_t start_time = clock();

    std::cout << "������ ���������� ����� ����� (x1 y1): ";
    std::cin >> p1.x >> p1.y;

    std::cout << "������ ���������� ����� ����� (x2 y2): ";
    std::cin >> p2.x >> p2.y;

    std::cout << "������ ���������� ������ ����� (x3 y3): ";
    std::cin >> p3.x >> p3.y;

    if (areCollinear(p1, p2, p3)) {
        std::cout << "������� ��������" << std::endl;
    } else {
        std::cout << "������� �� ��������" << std::endl;
    }

    // ʳ���� ���������� ����
    clock_t end_time = clock();

    // ���������� ���� ���������
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "��� ���������: " << time_taken << " ������" << std::endl;

    return 0;
}


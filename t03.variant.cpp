#include <iostream>
#include <variant>
#include <cmath>

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

    return 0;
}


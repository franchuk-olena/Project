// � ��� ������ ��������� ��� ����� �� ������������ �� ����� �� ��������. �� ��������� variant

#include <iostream>
#include <variant>
#include <cmath>
#include <ctime>  // ��� ���������� ����

struct Circle {
    double radius;
};

struct Square {
    double side;
};

struct Triangle {
    double a, b, c;
};

struct Rectangle {
    double length, width;
};

struct Trapezoid {
    double a, b, h;
};

using Shape = std::variant<Circle, Square, Triangle, Rectangle, Trapezoid>;
// ���������� ����
struct AreaVisitor {
    double operator()(const Circle& c) const {
        return M_PI * c.radius * c.radius;
    }

    double operator()(const Square& s) const {
        return s.side * s.side;
    }

    double operator()(const Triangle& t) const {
        double p = (t.a + t.b + t.c) / 2;
        return std::sqrt(p * (p - t.a) * (p - t.b) * (p - t.c));
    }

    double operator()(const Rectangle& r) const {
        return r.length * r.width;
    }

    double operator()(const Trapezoid& t) const {
        return 0.5 * (t.a + t.b) * t.h;
    }
};
// ��������� ���������
struct PerimeterVisitor {
    double operator()(const Circle& c) const {
        return 2 * M_PI * c.radius;
    }

    double operator()(const Square& s) const {
        return 4 * s.side;
    }

    double operator()(const Triangle& t) const {
        return t.a + t.b + t.c;
    }

    double operator()(const Rectangle& r) const {
        return 2 * (r.length + r.width);
    }

    double operator()(const Trapezoid& t) const {
        return t.a + t.b + 2 * std::sqrt(std::pow((t.b - t.a) / 2, 2) + std::pow(t.h, 2));
    }
};

int main() {
    int choice;
    Shape shape;

    // ������� ���������� ����
    clock_t start_time = clock();

    std::cout << "������� ������ ��� ����������:" << std::endl;
    std::cout << "1. ����" << std::endl;
    std::cout << "2. �������" << std::endl;
    std::cout << "3. ���������" << std::endl;
    std::cout << "4. �����������" << std::endl;
    std::cout << "5. ��������" << std::endl;
    std::cout << "��� ����: ";
    std::cin >> choice;

    switch (choice) {
        case 1: // ����
            {
                Circle c;
                std::cout << "������ ����� ����: ";
                std::cin >> c.radius;
                shape = c;
                break;
            }
        case 2: // �������
            {
                Square s;
                std::cout << "������ ������� ������� ��������: ";
                std::cin >> s.side;
                shape = s;
                break;
            }
        case 3: // ���������
            {
                Triangle t;
                std::cout << "������ ������� ���������� (a, b, c): ";
                std::cin >> t.a >> t.b >> t.c;
                shape = t;
                break;
            }
        case 4: // �����������
            {
                Rectangle r;
                std::cout << "������ ������� �� ������ ������������: ";
                std::cin >> r.length >> r.width;
                shape = r;
                break;
            }
        case 5: // ��������
            {
                Trapezoid t;
                std::cout << "������ ������ �� ������ �������� (a, b, h): ";
                std::cin >> t.a >> t.b >> t.h;
                shape = t;
                break;
            }
        default:
            std::cout << "������� ����.\n";
            return 1;
    }

    std::cout << "�����: " << std::visit(AreaVisitor{}, shape) << std::endl;
    std::cout << "��������: " << std::visit(PerimeterVisitor{}, shape) << std::endl;

    // ʳ���� ���������� ����
    clock_t end_time = clock();

    // ���������� ���� ���������
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "��� ���������: " << time_taken << " ������" << std::endl;

    return 0;
}


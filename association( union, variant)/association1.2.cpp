// � ��� ������ ������������ ������� �� ������� � ���������� �� �������� ����������� �� ��������� ���������� variant

// ������� ������������

//������� ��� ��������� (0 ��� ����������, 1 ��� ��������): 1
//������ ������ ���������� ����� ����� (r, theta): 5 1.57
//������ ������ ���������� ����� ����� (r, theta): 7 3.14
//³������ �� ������� (������ ����������): 12.295817

//������� ��� ��������� (0 ��� ����������, 1 ��� ��������): 0
//������ �������� ���������� ����� ����� (x, y): 3 4
//������ �������� ���������� ����� ����� (x, y): 6 8
//³������ �� ������� (�������� ����������): 5.000000



#include <iostream>
#include <cmath>
#include <variant>
#include <ctime>  // ��� ���������� ����

struct Cartesian {
    double x;
    double y;
};

struct Polar {
    double r;
    double theta;
};

using Point = std::variant<Cartesian, Polar>;

// ���������� ������ �� ������� � ���������� �����������
double distance_cartesian(const Cartesian& p1, const Cartesian& p2) {
    return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

// ���������� ������ �� ������� � �������� �����������
double distance_polar(const Polar& p1, const Polar& p2) {
    return std::sqrt(p1.r * p1.r + p2.r * p2.r - 2 * p1.r * p2.r * std::cos(p1.theta - p2.theta));
}

// ������� ��� ���������� ������ �� ����� �������, �� ����������� � variant
double distance(const Point& p1, const Point& p2, bool is_polar) {
    if (is_polar) {
        const Polar& polar1 = std::get<Polar>(p1);
        const Polar& polar2 = std::get<Polar>(p2);
        return distance_polar(polar1, polar2);
    } else {
        const Cartesian& cartesian1 = std::get<Cartesian>(p1);
        const Cartesian& cartesian2 = std::get<Cartesian>(p2);
        return distance_cartesian(cartesian1, cartesian2);
    }
}

int main() {
    Point p1, p2;
    bool is_polar;

    std::cout << "������� ��� ��������� (0 ��� ����������, 1 ��� ��������): ";
    std::cin >> is_polar;

    if (is_polar) {
        Polar p1_polar, p2_polar;
        std::cout << "������ ������ ���������� ����� ����� (r, theta(� �������)): ";
        std::cin >> p1_polar.r >> p1_polar.theta;
        std::cout << "������ ������ ���������� ����� ����� (r, theta(� �������)): ";
        std::cin >> p2_polar.r >> p2_polar.theta;
        p1 = p1_polar;
        p2 = p2_polar;

        // ������� ���������� ���� ��� ����������
        clock_t start_time = clock();
        double dist = distance(p1, p2, true);
        clock_t end_time = clock();

        // ³������ �� ���
        double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
        std::cout << "³������ �� ������� (������ ����������): " << dist << std::endl;
        std::cout << "��� ����������: " << time_taken << " ������" << std::endl;

    } else {
        Cartesian p1_cartesian, p2_cartesian;
        std::cout << "������ �������� ���������� ����� ����� (x, y): ";
        std::cin >> p1_cartesian.x >> p1_cartesian.y;
        std::cout << "������ �������� ���������� ����� ����� (x, y): ";
        std::cin >> p2_cartesian.x >> p2_cartesian.y;
        p1 = p1_cartesian;
        p2 = p2_cartesian;
    }

    // ������� ���������� ���� ��� ����������
        clock_t start_time = clock();
        double dist = distance(p1, p2, false);
        clock_t end_time = clock();

        // ³������ �� ���
        double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
        std::cout << "³������ �� ������� (�������� ����������): " << dist << std::endl;
        std::cout << "��� ����������: " << time_taken << " ������" << std::endl;

    return 0;
}

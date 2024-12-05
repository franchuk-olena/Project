//� ��� ������ ����������� ������������ ���, �� �������� ������������ ����� �
//������� � ���������, ������� �� ��������� �����������. ��������� ��
//����� �� ������������ ������� ������ �� ����� ������. �� ��������� variant

//������ ������� ��������� (1 - ���������, 2 - �������, 3 - ��������): 1
//������ x, y, z ��� ����� �����: 1 2 3
//������ x, y, z ��� ����� �����: 4 5 6
//³������: 5.20

//������ ������� ��������� (1 - ���������, 2 - �������, 3 - ��������): 2
//������ r, theta (� �������) ��� ����� �����: 2 1.5708
//������ r, theta (� �������) ��� ����� �����: 3 0
//³������: 3.00

//������ ������� ��������� (1 - ���������, 2 - �������, 3 - ��������): 3
//������ r, theta, phi (� �������) ��� ����� �����: 1 1.5708 0
//������ r, theta, phi (� �������) ��� ����� �����: 1 0 3.1416
//³������: 2.00


#include <iostream>
#include <variant>
#include <cmath>
#include <ctime>  // ��� ���������� ����

struct Cartesian {
    double x, y, z;
};

struct Polar {
    double r, theta; // r - �����, theta - ��� (� �������)
};

struct Spherical {
    double r, theta, phi; // r - �����, theta - ��� � ���� z, phi - ������������ ���
};

using Point = std::variant<Cartesian, Polar, Spherical>;

// ���������� ������ ��� ���������� ���������
double distance(const Cartesian& p1, const Cartesian& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// ���������� ������ ��� �������� ���������
double distance(const Polar& p1, const Polar& p2) {
    double x1 = p1.r * std::cos(p1.theta);
    double y1 = p1.r * std::sin(p1.theta);
    double x2 = p2.r * std::cos(p2.theta);
    double y2 = p2.r * std::sin(p2.theta);
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// ���������� ������ ��� ��������� ���������
double distance(const Spherical& p1, const Spherical& p2) {
    auto toCartesian = [](const Spherical& p) {
        return Cartesian{
            p.r * std::sin(p.theta) * std::cos(p.phi),
            p.r * std::sin(p.theta) * std::sin(p.phi),
            p.r * std::cos(p.theta)};
    };
    return distance(toCartesian(p1), toCartesian(p2));
}

int main() {

    // ������� ���������� ����
    clock_t start_time = clock();

    int system;
    std::cout << "������ ������� ��������� (1 - ���������, 2 - �������, 3 - ��������): ";
    std::cin >> system;

    if (system == 1) {
        Cartesian p1, p2;
        std::cout << "������ x, y, z ��� ����� �����: ";
        std::cin >> p1.x >> p1.y >> p1.z;
        std::cout << "������ x, y, z ��� ����� �����: ";
        std::cin >> p2.x >> p2.y >> p2.z;
        std::cout << "³������: " << distance(p1, p2) << std::endl;
    } else if (system == 2) {
        Polar p1, p2;
        std::cout << "������ r, theta (� �������) ��� ����� �����: ";
        std::cin >> p1.r >> p1.theta;
        std::cout << "������ r, theta (� �������) ��� ����� �����: ";
        std::cin >> p2.r >> p2.theta;
        std::cout << "³������: " << distance(p1, p2) << std::endl;
    } else if (system == 3) {
        Spherical p1, p2;
        std::cout << "������ r, theta, phi (� �������) ��� ����� �����: ";
        std::cin >> p1.r >> p1.theta >> p1.phi;
        std::cout << "������ r, theta, phi (� �������) ��� ����� �����: ";
        std::cin >> p2.r >> p2.theta >> p2.phi;
        std::cout << "³������: " << distance(p1, p2) << std::endl;
    } else {
        std::cout << "������������ ���� ������� ���������!" << std::endl;
    }

     // ʳ���� ���������� ����
    clock_t end_time = clock();

    // ���������� ���� ���������
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "��� ���������: " << time_taken << " ������" << std::endl;

    return 0;
}

#include <iostream>
#include <variant>
#include <cmath>

struct Cartesian {
    double x, y, z;
};

struct Polar {
    double r, theta; // r - радіус, theta - кут (у радіанах)
};

struct Spherical {
    double r, theta, phi; // r - радіус, theta - кут з віссю z, phi - азимутальний кут
};

using Point = std::variant<Cartesian, Polar, Spherical>;

// Обчислення відстані для декартових координат
double distance(const Cartesian& p1, const Cartesian& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// Обчислення відстані для полярних координат
double distance(const Polar& p1, const Polar& p2) {
    double x1 = p1.r * std::cos(p1.theta);
    double y1 = p1.r * std::sin(p1.theta);
    double x2 = p2.r * std::cos(p2.theta);
    double y2 = p2.r * std::sin(p2.theta);
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Обчислення відстані для сферичних координат
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
    int system;
    std::cout << "Оберіть систему координат (1 - декартова, 2 - полярна, 3 - сферична): ";
    std::cin >> system;

    if (system == 1) {
        Cartesian p1, p2;
        std::cout << "Введіть x, y, z для першої точки: ";
        std::cin >> p1.x >> p1.y >> p1.z;
        std::cout << "Введіть x, y, z для другої точки: ";
        std::cin >> p2.x >> p2.y >> p2.z;
        std::cout << "Відстань: " << distance(p1, p2) << std::endl;
    } else if (system == 2) {
        Polar p1, p2;
        std::cout << "Введіть r, theta (у радіанах) для першої точки: ";
        std::cin >> p1.r >> p1.theta;
        std::cout << "Введіть r, theta (у радіанах) для другої точки: ";
        std::cin >> p2.r >> p2.theta;
        std::cout << "Відстань: " << distance(p1, p2) << std::endl;
    } else if (system == 3) {
        Spherical p1, p2;
        std::cout << "Введіть r, theta, phi (у радіанах) для першої точки: ";
        std::cin >> p1.r >> p1.theta >> p1.phi;
        std::cout << "Введіть r, theta, phi (у радіанах) для другої точки: ";
        std::cin >> p2.r >> p2.theta >> p2.phi;
        std::cout << "Відстань: " << distance(p1, p2) << std::endl;
    } else {
        std::cout << "Неправильний вибір системи координат!" << std::endl;
    }

    return 0;
}

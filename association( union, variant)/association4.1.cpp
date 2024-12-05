//У цій задачі визначається універсальний тип, що дозволяє представляти точку в
//просторі в декартовій, полярній та сферичних координатах. Вводиться дві
//точки та обчислюється довжина відрізку на даних точках. За допомогою variant

//Оберіть систему координат (1 - декартова, 2 - полярна, 3 - сферична): 1
//Введіть x, y, z для першої точки: 1 2 3
//Введіть x, y, z для другої точки: 4 5 6
//Відстань: 5.20

//Оберіть систему координат (1 - декартова, 2 - полярна, 3 - сферична): 2
//Введіть r, theta (у радіанах) для першої точки: 2 1.5708
//Введіть r, theta (у радіанах) для другої точки: 3 0
//Відстань: 3.00

//Оберіть систему координат (1 - декартова, 2 - полярна, 3 - сферична): 3
//Введіть r, theta, phi (у радіанах) для першої точки: 1 1.5708 0
//Введіть r, theta, phi (у радіанах) для другої точки: 1 0 3.1416
//Відстань: 2.00


#include <iostream>
#include <variant>
#include <cmath>
#include <ctime>  // Для вимірювання часу

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

    // Початок вимірювання часу
    clock_t start_time = clock();

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

     // Кінець вимірювання часу
    clock_t end_time = clock();

    // Обчислення часу виконання
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Час виконання: " << time_taken << " секунд" << std::endl;

    return 0;
}

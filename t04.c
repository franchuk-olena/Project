#include <stdio.h>
#include <math.h>

// ������������ ��� ��� ������������� �����
typedef struct {
    enum { CARTESIAN, POLAR, SPHERICAL } type;
    union {
        struct { double x, y, z; } cartesian;       // ���������
        struct { double r, theta; } polar;         // �������
        struct { double r, theta, phi; } spherical; // ��������
    } coord;
} Point;

// ���������� ������ �� ������� � ��������� ������
double distance_cartesian(Point p1, Point p2) {
    double dx = p1.coord.cartesian.x - p2.coord.cartesian.x;
    double dy = p1.coord.cartesian.y - p2.coord.cartesian.y;
    double dz = p1.coord.cartesian.z - p2.coord.cartesian.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

// ���������� ������ �� ������� � ������� ������
double distance_polar(Point p1, Point p2) {
    double x1 = p1.coord.polar.r * cos(p1.coord.polar.theta);
    double y1 = p1.coord.polar.r * sin(p1.coord.polar.theta);
    double x2 = p2.coord.polar.r * cos(p2.coord.polar.theta);
    double y2 = p2.coord.polar.r * sin(p2.coord.polar.theta);
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// ���������� ������ �� ������� � �������� ������
double distance_spherical(Point p1, Point p2) {
    double x1 = p1.coord.spherical.r * sin(p1.coord.spherical.theta) * cos(p1.coord.spherical.phi);
    double y1 = p1.coord.spherical.r * sin(p1.coord.spherical.theta) * sin(p1.coord.spherical.phi);
    double z1 = p1.coord.spherical.r * cos(p1.coord.spherical.theta);

    double x2 = p2.coord.spherical.r * sin(p2.coord.spherical.theta) * cos(p2.coord.spherical.phi);
    double y2 = p2.coord.spherical.r * sin(p2.coord.spherical.theta) * sin(p2.coord.spherical.phi);
    double z2 = p2.coord.spherical.r * cos(p2.coord.spherical.theta);

    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}

int main() {
    // �������� ���� �����
    Point p1, p2;

    int system;
    printf("������ ������� ��������� (1 - ���������, 2 - �������, 3 - ��������): ");
    scanf("%d", &system);

    if (system == 1) { // ���������
        p1.type = CARTESIAN;
        p2.type = CARTESIAN;
        printf("������ x, y, z ��� ����� �����: ");
        scanf("%lf %lf %lf", &p1.coord.cartesian.x, &p1.coord.cartesian.y, &p1.coord.cartesian.z);
        printf("������ x, y, z ��� ����� �����: ");
        scanf("%lf %lf %lf", &p2.coord.cartesian.x, &p2.coord.cartesian.y, &p2.coord.cartesian.z);
        printf("³������: %.2f\n", distance_cartesian(p1, p2));
    } else if (system == 2) { // �������
        p1.type = POLAR;
        p2.type = POLAR;
        printf("������ r, theta (� �������) ��� ����� �����: ");
        scanf("%lf %lf", &p1.coord.polar.r, &p1.coord.polar.theta);
        printf("������ r, theta (� �������) ��� ����� �����: ");
        scanf("%lf %lf", &p2.coord.polar.r, &p2.coord.polar.theta);
        printf("³������: %.2f\n", distance_polar(p1, p2));
    } else if (system == 3) { // ��������
        p1.type = SPHERICAL;
        p2.type = SPHERICAL;
        printf("������ r, theta, phi (� �������) ��� ����� �����: ");
        scanf("%lf %lf %lf", &p1.coord.spherical.r, &p1.coord.spherical.theta, &p1.coord.spherical.phi);
        printf("������ r, theta, phi (� �������) ��� ����� �����: ");
        scanf("%lf %lf %lf", &p2.coord.spherical.r, &p2.coord.spherical.theta, &p2.coord.spherical.phi);
        printf("³������: %.2f\n", distance_spherical(p1, p2));
    } else {
        printf("������������ ���� ������� ���������!\n");
    }

    return 0;
}

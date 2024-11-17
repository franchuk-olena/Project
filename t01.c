#include <stdio.h>
#include <math.h>

typedef union {
    struct {
        double x;
        double y;
    } cartesian;  // �������� ����������
    struct {
        double r;
        double theta;
    } polar;  // ������ ����������
} Point;

// ���������� ������ �� ������� � ���������� �����������
double distance_cartesian(Point p1, Point p2) {
    return sqrt((p2.cartesian.x - p1.cartesian.x) * (p2.cartesian.x - p1.cartesian.x) +
                (p2.cartesian.y - p1.cartesian.y) * (p2.cartesian.y - p1.cartesian.y));
}

// ���������� ������ �� ������� � �������� �����������
double distance_polar(Point p1, Point p2) {
    return sqrt(p1.polar.r * p1.polar.r + p2.polar.r * p2.polar.r -
                2 * p1.polar.r * p2.polar.r * cos(p1.polar.theta - p2.polar.theta));
}

int main() {
    Point p1, p2;
    int is_polar;

    printf("������� ��� ��������� (0 ��� ����������, 1 ��� ��������): ");
    scanf("%d", &is_polar);

    if (is_polar) {
        printf("������ ������ ���������� ����� ����� (r, theta): ");
        scanf("%lf %lf", &p1.polar.r, &p1.polar.theta);
        printf("������ ������ ���������� ����� ����� (r, theta): ");
        scanf("%lf %lf", &p2.polar.r, &p2.polar.theta);

        // ³������ ��� �������� ���������
        printf("³������ �� ������� (������ ����������): %lf\n", distance_polar(p1, p2));
    } else {
        printf("������ �������� ���������� ����� ����� (x, y): ");
        scanf("%lf %lf", &p1.cartesian.x, &p1.cartesian.y);
        printf("������ �������� ���������� ����� ����� (x, y): ");
        scanf("%lf %lf", &p2.cartesian.x, &p2.cartesian.y);

        // ³������ ��� ���������� ���������
        printf("³������ �� ������� (�������� ����������): %lf\n", distance_cartesian(p1, p2));
    }

    return 0;
}


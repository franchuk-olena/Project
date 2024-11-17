#include <stdio.h>
#include <math.h>

typedef union {
    struct { double radius; } circle;
    struct { double side; } square;
    struct { double a, b, c; } triangle;
    struct { double length, width; } rectangle;
    struct { double a, b, h; } trapezoid;
} Shape;

typedef enum {
    CIRCLE,
    SQUARE,
    TRIANGLE,
    RECTANGLE,
    TRAPEZOID
} ShapeType;

double area(Shape shape, ShapeType type) {
    switch (type) {
        case CIRCLE:
            return M_PI * shape.circle.radius * shape.circle.radius;
        case SQUARE:
            return shape.square.side * shape.square.side;
        case TRIANGLE:
            double s = (shape.triangle.a + shape.triangle.b + shape.triangle.c) / 2;
            return sqrt(s * (s - shape.triangle.a) * (s - shape.triangle.b) * (s - shape.triangle.c));
        case RECTANGLE:
            return shape.rectangle.length * shape.rectangle.width;
        case TRAPEZOID:
            return 0.5 * (shape.trapezoid.a + shape.trapezoid.b) * shape.trapezoid.h;
        default:
            return 0;
    }
}

double perimeter(Shape shape, ShapeType type) {
    switch (type) {
        case CIRCLE:
            return 2 * M_PI * shape.circle.radius;
        case SQUARE:
            return 4 * shape.square.side;
        case TRIANGLE:
            return shape.triangle.a + shape.triangle.b + shape.triangle.c;
        case RECTANGLE:
            return 2 * (shape.rectangle.length + shape.rectangle.width);
        case TRAPEZOID:
            return shape.trapezoid.a + shape.trapezoid.b + 2 * sqrt(pow((shape.trapezoid.b - shape.trapezoid.a) / 2, 2) + pow(shape.trapezoid.h, 2));
        default:
            return 0;
    }
}

int main() {
    Shape shape;
    ShapeType type;
    int choice;

    printf("������� ������ ��� ����������:\n");
    printf("1. ����\n2. �������\n3. ���������\n4. �����������\n5. ��������\n");
    printf("��� ����: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: // ����
            printf("������ ����� ����: ");
            scanf("%lf", &shape.circle.radius);
            type = CIRCLE;
            break;
        case 2: // �������
            printf("������ ������� ������� ��������: ");
            scanf("%lf", &shape.square.side);
            type = SQUARE;
            break;
        case 3: // ���������
            printf("������ ������� ���������� (a, b, c): ");
            scanf("%lf %lf %lf", &shape.triangle.a, &shape.triangle.b, &shape.triangle.c);
            type = TRIANGLE;
            break;
        case 4: // �����������
            printf("������ ������� �� ������ ������������: ");
            scanf("%lf %lf", &shape.rectangle.length, &shape.rectangle.width);
            type = RECTANGLE;
            break;
        case 5: // ��������
            printf("������ ������ �� ������ �������� (a, b, h): ");
            scanf("%lf %lf %lf", &shape.trapezoid.a, &shape.trapezoid.b, &shape.trapezoid.h);
            type = TRAPEZOID;
            break;
        default:
            printf("������� ����.\n");
            return 1;
    }

    printf("�����: %.2f\n", area(shape, type));
    printf("��������: %.2f\n", perimeter(shape, type));

    return 0;
}

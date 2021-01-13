/*
    Гребенков Д. И.
    Группа М8О-207Б-19
    Вариант 12

Разработать шаблоны классов согласно варианту задания.  Параметром шаблона должен являться скалярный тип данных
задающий тип данных для оси координат. Классы должны иметь только публичные поля. В классах не должно быть методов, 
только поля. Фигуры являются фигурами вращения (равнобедренными), за исключением трапеции и прямоугольника. 
Для хранения координат фигур необходимо использовать шаблон  std::pair.
Необходимо реализовать две шаблонных функции:
1. Функция print печати фигур на экран std::cout  (печататься должны координаты вершин фигур). Функция должна 
принимать на вход std::tuple с фигурами, согласно варианту задания (минимум по одной каждого класса).
2. Функция square вычисления суммарной площади фигур. Функция должна принимать на вход std::tuple с фигурами, 
согласно варианту задания (минимум по одной каждого класса).
Создать программу, которая позволяет:
· Создает набор фигур согласно варианту задания (как минимум по одной фигуре каждого типа с координатами типа int
и координатами типа double).
· Сохраняет фигуры в std::tuple
· Печатает на экран содержимое std::tuple с помощью шаблонной функции print.
· Вычисляет суммарную площадь фигур в std::tuple и выводит значение на экран.
	Вариант задания: Трапеция, ромб, пятиугольник.
*/

#include <iostream>
#include <tuple>
#include <cmath>

const double pi = 3.14159;

template <typename T>
class Trapezoid {
    public:
        using type = T;
        std::pair <T, T> left_top, left_bottom, right_bottom;
        Trapezoid (T ltx, T lty, T lbx, T lby, T rbx, T rby) {
            left_top.first = ltx;
            left_top.second = lty;
            left_bottom.first = lbx;
            left_bottom.second = lby;
            right_bottom.first = rbx;
            right_bottom.second = rby;
        };
};

template <typename T>
class Rhombus {
    public:
        using type = T;
        std::pair <T, T> left, bottom;
        Rhombus (T lx, T ly, T bx, T by) {
            left.first = lx;
            left.second = ly;
            bottom.first = bx;
            bottom.second = by;
        };
};

template <typename T>
class Pentagon {
    public:
        using type = T;
        std::pair <T, T> center;
        T radius;
        Pentagon (T cx, T cy, T r) {
            center.first = cx;
            center.second = cy;
            radius = r;
        };
};

template <int i = 0, class... Ts>
void vertices (std::tuple <Ts ...> t) {
    if constexpr (i < std::tuple_size <decltype (t)>::value) {
        std::cout << std::endl;
        std::cout << " Figure [" << i << "]:" << std::endl;
        verticesN (std::get <i> (t));
        vertices < i + 1, Ts ... > (t);
    }
}

template <int i = 0, class... Ts>
void squares (std::tuple <Ts ...> t, double sq) {
    if constexpr (i < std::tuple_size <decltype (t)>::value){
        sq += figure_square (std::get <i> (t));
        squares < i + 1, Ts ... > (t, sq);
    }
    else {
        std::cout << std::endl;
        std::cout << "Sum of squares of all figures in tuple: " << sq << std::endl;
    }
}

template <typename T>
T figure_square (Trapezoid <T> tr) {
    return ((tr.right_bottom.first - tr.left_top.first) * (tr.left_top.second - tr.left_bottom.second));
}

template <typename T>
T figure_square (Rhombus <T> rh) {
    return (2 * (rh.bottom.first - rh.left.first) * (rh.left.second - rh.bottom.second));
}

template <typename T>
T figure_square (Pentagon <T> pg) {
    return (5 * pow (pg.radius, 2) * sin (72 * pi / 180.0) / 2.0);
}

template <typename T>
void verticesN (Trapezoid <T> tr) {
    std::cout << "(" << tr.left_top.first << ", " << tr.left_top.second << ")" << std::endl;
    std::cout << "(" << tr.left_bottom.first << ", " << tr.left_bottom.second << ")" << std::endl;
    std::cout << "(" << tr.right_bottom.first << ", " << tr.right_bottom.second << ")" << std::endl;
    std::cout << "(" << tr.right_bottom.first - tr.left_top.first + tr.left_bottom.first << 
    ", " << tr.left_top.second << ")" << std::endl;
}

template <typename T>
void verticesN (Rhombus <T> rh) {
    std::cout << "(" << rh.left.first << ", " << rh.left.second << ")" << std::endl;
    std::cout << "(" << rh.bottom.first << ", " << rh.bottom.second << ")" << std::endl;
    std::cout << "(" << 2 * rh.bottom.first - rh.left.first << ", " << rh.left.second << ")" << std::endl;
    std::cout << "(" << rh.bottom.first << ", " << 2 * rh.left.second - rh.bottom.second << ")" << std::endl;
}

template <typename T>
void verticesN (Pentagon <T> pg) {
    std::cout << "(" << pg.center.first - pg.radius * sin (72 * pi / 180) 
    << ", " << pg.center.second + pg.radius * cos (72 * pi / 180) << ")" << std::endl;
    std::cout << "(" << pg.center.first << ", " << pg.center.second + pg.radius << ")" << std::endl;
    std::cout << "(" << pg.center.first + pg.radius * sin (72 * pi / 180) 
    << ", " << pg.center.second + pg.radius * cos (72 * pi / 180) << ")" << std::endl;
    std::cout << "(" << pg.center.first + pg.radius * sin (36 * pi / 180) 
    << ", " << pg.center.second - pg.radius * cos (36 * pi / 180) << ")" << std::endl;
    std::cout << "(" << pg.center.first - pg.radius * sin (36 * pi / 180) 
    << ", " << pg.center.second - pg.radius * cos (36 * pi / 180) << ")" << std::endl;
}

int main () {
    Trapezoid <int> tr1 (1, 2, 0, 0, 4, 0);
    Trapezoid <double> tr2 (3.25, 4.25, 1.25, 1.25, 8.25, 1.25);
    Rhombus <int> rh1 (-1, 0, 0, -1);
    Rhombus <double> rh2 (-0.75, 1.0, 2.0, -0.5);
    Pentagon <int> pg1 (5, 4, 9);
    Pentagon <double> pg2 (3.72, 8.04, 1.36);
    std::tuple < Trapezoid <int>, Trapezoid <double>, Rhombus <int>, Rhombus <double>, 
    Pentagon <int>, Pentagon <double> > tupl {tr1, tr2, rh1, rh2, pg1, pg2};
    vertices (tupl);
    squares (tupl, 0);
    return 0;
}
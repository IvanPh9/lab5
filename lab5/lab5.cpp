#include <iostream>
#include <cmath>
#include <locale.h>

using namespace std;

class Dot {
public:
    double x;
    double y;

    double calculate_z() {
        return pow(x, 2) + x * y + pow(y, 2) - 6 * x - 9 * y;
    }

    void print_dot() {
        double z = calculate_z();
        cout << "x= " << x << "; y= " << y << "; F(x, y)= " << z << endl;
    }

    Dot copy() {
        Dot copy = *this; // створюємо копію об'єкта
        return copy;
    }
};
int* znak(Dot& dot, double del) {
    static int a[2] = { 0, 0 };
    Dot dot_i = dot.copy(), dot_j = dot.copy();
    double f_initial = dot.calculate_z();

    dot_i.x -= del;
    dot_j.x += del; 
    dot_i.print_dot();
    dot_j.print_dot();
    double f_left = dot_i.calculate_z();
    double f_right = dot_j.calculate_z();

    if (f_initial > f_left || f_initial > f_right) {
        if (f_left < f_right) {
            a[0] = -1; 
            dot.x -= del;
        }
        else if (f_left > f_right) {
            a[0] = 1; 
            dot.x += del;
        }
        
    }
    else a[0] = 0;

    dot_i = dot.copy(); dot_j = dot.copy();
    dot_i.y -= del;
    dot_j.y += del;
    dot_i.print_dot();
    dot_j.print_dot();
    f_initial = dot.calculate_z();
    double f_down = dot_i.calculate_z();
    double f_up = dot_j.calculate_z();

    if (f_initial > f_down || f_initial > f_up) {
        if (f_down < f_up) {
            a[1] = -1;
            dot.y -= del;
        }
        else if (f_down > f_up) {
            a[1] = 1;
            dot.y += del;
        }
        
    }
    else a[1] = 0;
    return a;
}


int main() {
    setlocale(LC_CTYPE, "ukr"); // Українізація
    int c = 0;
    double eps, delt = 2;
    cout << "Введiть значення епсiлон" << endl;
    cin >> eps;
    //Перевірка епсілон
    if (eps <= 0 || eps > 1) {
        cout << "Епсiлон не вiрно вказаний";
        return 1;
    }
    cout << "Введiть значення кроку" << endl;
    cin >> delt;
    //Перевірка епсілон
    if (delt <= 0) {
        cout << "Крок не вiрно вказаний";
        return 1;
    }
    double x, y;
    cout << "x:" << endl;
    cin >> x;
    cout << "y:" << endl;
    cin >> y;
    cout << endl;
    Dot now_dot; now_dot.x = x; now_dot.y = y;
    Dot last_t_dot;
    while (true) {
        c++;
        cout << "Iтерацiя " << c << endl << "Крок " << delt << endl << "Базисна Точка" << endl;  
        last_t_dot = now_dot.copy();
        last_t_dot.print_dot();        
        cout << "------------------" << endl;
        int* result = znak(now_dot, delt);   
        cout << "------------------" << endl;
        cout << "Знак x: "; if (result[0] == 1) cout << "+"; else if (result[0] == -1) cout << "-"; else cout << "0"; 
        cout << "; Знак y: "; if (result[1] == 1) cout << "+" << endl; else if (result[1] == -1) cout << "-" << endl; else cout << "0" << endl;
        now_dot.print_dot();
        if (last_t_dot.calculate_z() > now_dot.calculate_z()) {
            while (last_t_dot.calculate_z() >= now_dot.calculate_z()) {
                last_t_dot = now_dot.copy();
                now_dot.x += result[0] * delt;
                now_dot.y += result[1] * delt;
                now_dot.print_dot();
            }
            now_dot = last_t_dot.copy();
            cout << "Нова Базисна Точка" << endl;
            now_dot.print_dot();
            cout << endl;
        }
        else if (delt >= eps) {
            delt = delt / 2;
            cout << endl;
        }
        else break;
    }
    cout << endl << "=====================" << endl;
    cout << "Результат:" << endl << "Програма за " << c << " iтерацiй, досягнула результату з точнiстю до епсiлон в заданiй точцi:" << endl;
    now_dot.print_dot();
}
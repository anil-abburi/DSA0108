#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Complex {
    double re;
    double im;

public:
    Complex(double r = 0.0, double i = 0.0) : re(r), im(i) {}

    double real() const { return re; }
    double imag() const { return im; }
    double magnitude() const { return std::hypot(re, im); }

    Complex operator+(const Complex& o) const { return Complex(re + o.re, im + o.im); }
    Complex operator-(const Complex& o) const { return Complex(re - o.re, im - o.im); }
    Complex operator*(const Complex& o) const {
        return Complex(re * o.re - im * o.im, re * o.im + im * o.re);
    }

    Complex operator/(const Complex& o) const {
        double denom = o.re * o.re + o.im * o.im;
        if (denom == 0.0) {
            throw std::domain_error("Division by zero impedance");
        }
        return Complex((re * o.re + im * o.im) / denom, (im * o.re - re * o.im) / denom);
    }

    bool operator==(const Complex& o) const {
        return std::fabs(re - o.re) < 1e-9 && std::fabs(im - o.im) < 1e-9;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& z) {
        os << std::fixed << std::setprecision(4) << z.re
           << (z.im >= 0 ? " + j" : " - j") << std::fabs(z.im);
        return os;
    }
};

int main() {
    const double pi = 3.14159265358979323846;
    const double freq = 50.0;
    const double omega = 2.0 * pi * freq;

    const double R = 100.0;
    const double L = 0.2;
    const double C = 100e-6;

    Complex zR(R, 0.0);
    Complex zL(0.0, omega * L);
    Complex zC(0.0, -1.0 / (omega * C));

    Complex zSeries = zR + zL + zC;
    Complex zRL = (zR * zL) / (zR + zL);
    Complex zParallel = (zRL * zC) / (zRL + zC);

    std::cout << "Z_R        = " << zR << " | |Z| = " << zR.magnitude() << " Ohm\n";
    std::cout << "Z_L        = " << zL << " | |Z| = " << zL.magnitude() << " Ohm\n";
    std::cout << "Z_C        = " << zC << " | |Z| = " << zC.magnitude() << " Ohm\n";
    std::cout << "Z_Series   = " << zSeries << " | |Z| = " << zSeries.magnitude() << " Ohm\n";
    std::cout << "Z_Parallel = " << zParallel << " | |Z| = " << zParallel.magnitude() << " Ohm\n";

    try {
        Complex zZero(0.0, 0.0);
        Complex bad = zR / zZero;
        std::cout << bad << '\n';
    } catch (const std::domain_error& e) {
        std::cout << "Zero division handled: " << e.what() << '\n';
    }
    return 0;
}

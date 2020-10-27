#include <iostream>
#include <cmath>
#include <random>
#include <ctime>

double used_f(double x) {
    return 2 * cos(x) + log10(x);
}

double used_g(double x) {
    return sin(5 * x) * used_f(x);
}

void SA(double func(double x))
{
    double a = 1.5;
    double b = 5;
    const double Tmax = 10000;
    const double Tmin = 0.1;
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<double> urd(a, b);
    std::uniform_real_distribution<double> pr(0, 1);
    double x1 = urd(gen);
    double f_x1 = used_f(x1);
    double Ti = Tmax;
    int N = 1;
    std::cout << "N    T         x         f(x)\n";
    std::cout << N << "  " << Ti << "    " << x1 << "    " << func(x1) << "\n";
    while (Ti > Tmin)
    {
        double xi = urd(gen);
        double f_xi = used_f(xi);
        double delta_f = f_xi - f_x1;
        if (delta_f <= 0)
        {
            x1 = xi;
            f_x1 = f_xi;
        }
        else
        {
            double P = exp(-delta_f / Ti);
            double p = pr(gen);
            if (p < P)
            {
                x1 = xi;
                f_x1 = f_xi;
            }
        }
        Ti *= 0.95;
        N++;
        std::cout << N << "  " << Ti << "    " << x1 << "    " << func(x1) << "\n";
    }
}

int main()
{
    SA(used_f);
    std::cout << std::endl;
    SA(used_g);
}


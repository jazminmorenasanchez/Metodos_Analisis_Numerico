#include <iostream> 
#include <vector>
#include <iomanip>

using namespace std;

struct Spline {
    double a, b, c, d, x;
};

// Función para calcular las trazadoras cúbicas condicionadas
vector<Spline> calcularTrazadorasCubicasCondicionadas(const vector<double>& X, const vector<double>& Y, double derivadaInicio, double derivadaFin) {
    int n = X.size() - 1;
    vector<double> h(n), alpha(n+1), l(n+1), mu(n+1), z(n+1);
    vector<Spline> splines(n);

    for (int i = 0; i < n; i++) {
        h[i] = X[i+1] - X[i];
    }

    // Condiciones en los extremos (derivadas dadas)
    alpha[0] = 3.0 * (Y[1] - Y[0]) / h[0] - 3.0 * derivadaInicio;
    alpha[n] = 3.0 * derivadaFin - 3.0 * (Y[n] - Y[n-1]) / h[n-1];

    for (int i = 1; i < n; i++) {
        alpha[i] = (3.0/h[i]) * (Y[i+1] - Y[i]) - (3.0/h[i-1]) * (Y[i] - Y[i-1]);
    }

    l[0] = 2.0 * h[0];
    mu[0] = 0.5;
    z[0] = alpha[0] / l[0];

    for (int i = 1; i < n; i++) {
        l[i] = 2.0 * (X[i+1] - X[i-1]) - h[i-1] * mu[i-1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i];
    }

    l[n] = h[n-1] * (2.0 - mu[n-1]);
    z[n] = (alpha[n] - h[n-1] * z[n-1]) / l[n];
    splines[n-1].c = z[n];

    for (int j = n-1; j >= 0; j--) {
        splines[j].c = z[j] - mu[j] * splines[j+1].c;
        splines[j].b = (Y[j+1] - Y[j]) / h[j] - h[j] * (splines[j+1].c + 2.0 * splines[j].c) / 3.0;
        splines[j].d = (splines[j+1].c - splines[j].c) / (3.0 * h[j]);
        splines[j].a = Y[j];
        splines[j].x = X[j];
    }

    return splines;
}

// Función para mostrar las trazadoras cúbicas
void mostrarTrazadorasCubicasCondicionadas(const vector<Spline>& splines, const vector<double>& X) {
    cout << "Formula General: Si(x) = ai + bi(x - xi) + ci(x - xi)^2 + di(x - xi)^3\n\n";
    
    for (int i = 0; i < splines.size(); i++) {
        cout << "Spline " << i << ":\n";
        cout << "S" << i << "(x) = " << fixed << setprecision(4) << splines[i].a << " + " 
             << splines[i].b << "(x - " << splines[i].x << ") + "
             << splines[i].c << "(x - " << splines[i].x << ")^2 + " 
             << splines[i].d << "(x - " << splines[i].x << ")^3\n";
        
        // Mostrar valores de a, b, c, d con el valor de i correspondiente
        cout << "a" << i << " = " << splines[i].a << endl;
        cout << "b" << i << " = " << splines[i].b << endl;
        cout << "c" << i << " = " << splines[i].c << endl;
        cout << "d" << i << " = " << splines[i].d << endl;
        
        // Mostrar el intervalo válido para el polinomio
        cout << "Polinomio valido en el intervalo [" << X[i] << ", " << X[i+1] << "]\n\n";
    }
}

int main() {
    // Valores X e Y dados (se pueden modificar)
    vector<double> X = {0.0, 1.0, 2.0, 3.0};  // Puntos X dados
    vector<double> Y = {1.0, 2.7182, 7.3891, 20.0855};  // Puntos Y dados

    // Derivadas en los extremos
    double derivadaInicio = 1.0;  // Derivada en X[0]
    double derivadaFin = 10.0;    // Derivada en X[n]

    // Calcular las trazadoras cúbicas condicionadas
    vector<Spline> splines = calcularTrazadorasCubicasCondicionadas(X, Y, derivadaInicio, derivadaFin);

    // Mostrar las trazadoras cúbicas y los coeficientes
    mostrarTrazadorasCubicasCondicionadas(splines, X);

    return 0;
}
/*
Natural: No se especifican las derivadas primeras en los extremos, 
y las derivadas segundas en los extremos son cero.
Esto significa que la curva tiene un comportamiento más "suave" en los extremos,
es decir, que la curva es lineal (recta) en los puntos inicial y final.

Condicionada: Se especifican las pendientes (derivadas primeras) en los extremos, 
lo que permite mayor control sobre la forma de la curva en los bordes.
se imponen condiciones adicionales sobre las derivadas primeras en los extremos, 
es decir, se conoce la pendiente en los puntos inicial y final del intervalo. 
Estas condiciones permiten un mayor control sobre la forma de la curva en los extremos.
*/
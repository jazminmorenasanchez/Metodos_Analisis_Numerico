#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Spline {
    double a, b, c, d, x;
};

// Función para calcular las trazadoras cúbicas naturales
vector<Spline> calcularTrazadorasCubicas(const vector<double>& X, const vector<double>& Y) {
    int n = X.size() - 1;
    vector<double> h(n), alpha(n), l(n+1), mu(n+1), z(n+1);
    vector<Spline> splines(n);

    for (int i = 0; i < n; i++) {
        h[i] = X[i+1] - X[i];
        alpha[i] = (3.0/h[i]) * (Y[i+1] - Y[i]) - (3.0/h[i-1]) * (Y[i] - Y[i-1]);
    }

    // Condiciones de frontera naturales
    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;

    for (int i = 1; i < n; i++) {
        l[i] = 2.0 * (X[i+1] - X[i-1]) - h[i-1] * mu[i-1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i];
    }

    l[n] = 1.0;
    z[n] = 0.0;
    splines[n-1].c = 0.0;

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
void mostrarTrazadorasCubicas(const vector<Spline>& splines, const vector<double>& X) {
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

    // Calcular las trazadoras cúbicas
    vector<Spline> splines = calcularTrazadorasCubicas(X, Y);

    // Mostrar las trazadoras cúbicas y los coeficientes
    mostrarTrazadorasCubicas(splines, X);

    return 0;
}
/*
formula: S_i(x) = ai + bi(x- xi) + ci(x -xi)^2 + di(x - xi)^3 

Este método utiliza polinomios cúbicos por tramos (splines) para interpolar los datos. 
En lugar de un único polinomio global que pase por todos los puntos, se construye un polinomio
cúbico diferente para cada subintervalo entre puntos adyacentes.

Como se usan polinomios cúbicos por tramos, cada polinomio solo afecta a un intervalo específico.
Esto significa que, si se modifica un punto, solo se verá afectado el polinomio cúbico asociado
a ese intervalo, y no a toda la curva.

Natural: No se especifican las derivadas primeras en los extremos, 
y las derivadas segundas en los extremos son cero, resultando en una curva que termina de forma "suave".

Condicionada: Se especifican las pendientes (derivadas primeras) en los extremos, 
lo que permite mayor control sobre la forma de la curva en los bordes.
*/
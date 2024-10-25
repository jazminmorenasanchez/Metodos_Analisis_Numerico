#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// Función para calcular las diferencias divididas
void calcularDiferenciasDivididas(vector<vector<double>>& tabla, const vector<double>& x, const vector<double>& y, int n) {
    for (int i = 0; i < n; i++) {
        tabla[i][0] = y[i];
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            tabla[i][j] = (tabla[i + 1][j - 1] - tabla[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
}

// Función para mostrar la tabla de diferencias divididas
void mostrarTabla(const vector<vector<double>>& tabla, const vector<double>& x, int n) {
    cout << left << setw(10) << "X" << setw(10) << "Y";

    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << x[i];
        for (int j = 0; j < n - i; j++) {
            cout << setw(10) << fixed << setprecision(4) << tabla[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Función para generar el polinomio de Newton
void generarPolinomio(const vector<vector<double>>& tabla, const vector<double>& x, int n) {
    cout << "\nf_" << n-1 << "(x) = " << fixed << setprecision(4) << tabla[0][0];
    for (int i = 1; i < n; i++) {
        cout << " + " << tabla[0][i] << " ";
        for (int j = 0; j < i; j++) {
            cout << "(x - " << x[j] << ")";
        }
    }
    cout << endl;
}

int main() {
    int n = 4;
    
    // Valores de X e Y (puedes modificarlos para otros ejercicios)
    vector<double> x = {0.0, 1.0, 2.0, 3.0};
    vector<double> y = {1.0, 2.7182, 7.3891, 20.0855};

    // Crear tabla para diferencias divididas
    vector<vector<double>> tabla(n, vector<double>(n, 0.0));

    // Calcular diferencias divididas
    calcularDiferenciasDivididas(tabla, x, y, n);

    // Mostrar la tabla de diferencias divididas
    cout << "Tabla de diferencias divididas:" << endl;
    mostrarTabla(tabla, x, n);

    // Mostrar el polinomio de Newton
    cout << "Polinomio de interpolacion de Newton:" << endl;
    cout << "fn(x) = f(x0) + f[x1; x0](x - x0) + f[x2; x1; x0](x - x0)(x - x1) + f[x3; x2; x1; x0](x - x0)(x - x1)(x - x2)...." << endl;
    generarPolinomio(tabla, x, n);

    return 0;
}
/*
fn(x) = f(x0) + f[x1; x0](x - x0) + f[x2; x1; x0](x - x0)(x - x1) + .... + f[xn; xn-1; ... x0](x - x0)(x - x1) ... (x - xn-1)
la f(x) original quedaria f(x) = fn(x) + E

f[x1 - x0] = [f(x1) - f(x0)] / [x1 - x0]

tabla de diefrencias divididas:
 x     y
x0    y0   f[x1 ; x0]   f[x2 ; x1 ; x0]   f[x3 ; x2 ; x1 ; x0]
x1    y1   f[x2 ; X1]   f[x3 ; x2 ; x1]
x2    y2   f[x3 ; x2]
x3    y3


*/
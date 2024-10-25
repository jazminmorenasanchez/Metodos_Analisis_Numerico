#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept> // Para lanzar excepciones

using namespace std;

// Función para calcular regresión lineal por mínimos cuadrados
void regresionLineal(const vector<double>& X, const vector<double>& Y) {
    int n = X.size();
    double sumX = 0, sumY = 0, sumX2 = 0, sumXY = 0;

    // Cálculo de las sumas
    for (int i = 0; i < n; i++) {
        sumX += X[i];
        sumY += Y[i];
        sumX2 += X[i] * X[i];
        sumXY += X[i] * Y[i];
    }

    // Verificar el denominador para la pendiente a1
    double denominador = (n * sumX2 - sumX * sumX);

    try {
        // Verificamos si el denominador es cero
        if (denominador == 0) {
            throw runtime_error("Error: Division por cero en el cálculo de la pendiente (a1). Los valores de X son idénticos.");
        }

        // Cálculo de los coeficientes a1 (pendiente) y a0 (intersección)
        double a1 = (n * sumXY - sumX * sumY) / denominador;
        double a0 = (sumY - a1 * sumX) / n;

        // Mostrar la fórmula general
        cout << "Regresion lineal por minimos cuadrados: y = a1 * x + a0\n";

        // Mostrar los coeficientes a1 y a0
        cout << "a1 (pendiente) = " << fixed << setprecision(4) << a1 << endl;
        cout << "a0 (interseccion) = " << fixed << setprecision(4) << a0 << endl << endl;

        // Mostrar la tabla con los valores Xi, Yi, Xi^2, XiYi
        cout << left << setw(10) << "Xi" << setw(10) << "Yi" << setw(10) << "Xi^2" << setw(10) << "XiYi" << endl;
        cout << "---------------------------------------" << endl;

        for (int i = 0; i < n; i++) {
            cout << left << setw(10) << X[i] << setw(10) << Y[i] << setw(10) << X[i] * X[i] << setw(10) << X[i] * Y[i] << endl;
        }

        // Mostrar los totales
        cout << "---------------------------------------" << endl;
        cout << left << setw(10) << sumX << setw(10) << sumY << setw(10) << sumX2 << setw(10) << sumXY << endl;
    }
    catch (const runtime_error& e) {
        // Capturar la excepción si el denominador es 0
        cerr << e.what() << endl;
    }
}

int main() {
    // Ejemplo proporcionado
    vector<double> X = {1, 2, 3, 4, 5, 6, 7};
    vector<double> Y = {0.5, 2.5, 2.0, 4.0, 3.5, 6.0, 5.5};

    // Calcular y mostrar la regresión lineal
    regresionLineal(X, Y);

    return 0;
}
/*
técnica para encontrar la línea recta que mejor ajusta un conjunto de datos. 
El objetivo es modelar la relación entre dos variables: una independiente X y una dependiente Y,
y determinar cómo los cambios en X influyen en Y.

La ecuación de la recta que representa esta relación es:
y = a1 * x + a0

El método de mínimos cuadrados busca minimizar la suma de los cuadrados de las diferencias entre los valores observados de 
𝑌
Y (los puntos en la tabla) y los valores 
𝑌
Y que predice la recta ajustada.

Funcionamiento del Método de Mínimos Cuadrados:
Datos de entrada: Tenemos un conjunto de puntos (Xi ,Yi), que representan las observaciones de las variables X e Y
calcular los coeficientes a0 (intercepcion) y a1 (pendiente).

a1 = [n * sumatoria (xi*yi) - sumatoria (xi) * sumatoria (yi)] / [n * sumatoria (xi)^2 - (sumatoria (xi))^2]
a0 = [sumatoria (yi) - a1 * sumatoria (xi)] / n 

n es el número de puntos de datos.
Con los valores de a0 y a1, podemos escribir la ecuación de la recta de regresión que mejor se ajusta a los datos.
*/
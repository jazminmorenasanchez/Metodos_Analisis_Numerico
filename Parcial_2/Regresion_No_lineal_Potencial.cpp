#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath> // Para usar log y pow
#include <stdexcept> // Para lanzar excepciones

using namespace std;

// Función para calcular regresión lineal por mínimos cuadrados
void regresionLineal(const vector<double>& X, const vector<double>& Y) {
    int n = X.size();
    double sumLogX = 0, sumLogY = 0, sumLogX2 = 0, sumLogXY = 0;

    // Cálculo de las sumas con las transformaciones logarítmicas
    vector<double> logX(n), logY(n);
    for (int i = 0; i < n; i++) {
        logX[i] = log10(X[i]);
        logY[i] = log10(Y[i]);
        sumLogX += logX[i];
        sumLogY += logY[i];
        sumLogX2 += logX[i] * logX[i];
        sumLogXY += logX[i] * logY[i];
    }

    // Verificar el denominador para la pendiente a1
    double denominador = (n * sumLogX2 - sumLogX * sumLogX);

    try {
        // Verificamos si el denominador es cero
        if (denominador == 0) {
            throw runtime_error("Error: División por cero en el cálculo de la pendiente (a1). Los valores de log(X) son idénticos.");
        }

        // Cálculo de los coeficientes a1 (pendiente) y a0 (intersección)
        double a1 = (n * sumLogXY - sumLogX * sumLogY) / denominador;
        double a0 = (sumLogY - a1 * sumLogX) / n;

        // Cálculo de A (se necesita hacer 10^a0 para deshacer la transformación logarítmica)
        double A = pow(10, a0);

        // Mostrar la fórmula general
        cout << "Modelo potencial: y = A * x^b\n";
        cout << "A (interseccion) = " << fixed << setprecision(4) << A << endl;
        cout << "b (pendiente) = " << fixed << setprecision(4) << a1 << endl << endl;

        // Mostrar los valores de a0 y a1
        cout << "a0 (interseccion en escala logaritmica) = " << fixed << setprecision(4) << a0 << endl;
        cout << "a1 (pendiente en escala logaritmica) = " << fixed << setprecision(4) << a1 << endl << endl;

        // Mostrar la tabla con los valores Xi, Yi, log(Xi), log(Yi), log(Xi)^2 y log(Xi)*log(Yi)
        cout << left << setw(10) << "Xi" << setw(10) << "Log Xi" << setw(10) << "Yi" << setw(10) << "Log Yi"
             << setw(10) << "LogXi^2" << setw(10) << "LogXi*LogYi" << endl;
        cout << "---------------------------------------------------------------" << endl;

        for (int i = 0; i < n; i++) {
            cout << left << setw(10) << X[i] << setw(10) << logX[i] << setw(10) << Y[i] << setw(10) << logY[i]
                 << setw(10) << logX[i] * logX[i] << setw(10) << logX[i] * logY[i] << endl;
        }

        // Mostrar los totales
        cout << "---------------------------------------------------------------" << endl;
        cout << left << setw(10) << sumLogX << setw(10) << sumLogY << setw(10) << " " << setw(10) << " "
             << setw(10) << sumLogX2 << setw(10) << sumLogXY << endl;
    }
    catch (const runtime_error& e) {
        // Capturar la excepción si el denominador es 0
        cerr << e.what() << endl;
    }
}

int main() {
    // Ejemplo proporcionado
    vector<double> X = {1, 2, 3, 4, 5};
    vector<double> Y = {0.5, 1.7, 3.4, 5.7, 8.4};

    // Calcular y mostrar la regresión lineal adaptada para el modelo potencial
    regresionLineal(X, Y);
    cout << "Recordar que la fila de sumatorias se encuentra mal ubicada, los valores corresponden a Log xi, log yi, xi^2, xiyi.\n\n";
    return 0;
}

/*
y=A*x^b
A es una constante
b= es el exponente que queremos encontrar

aplicamos logaritmo base 10 de ambos lados y asi obtenemos una forma lineal:
log(y)=log(A*x^b)
por prop. de los logaritmos:
log(y)= log(A)+b*log(x)

es una ecuacion lineal en terminos de log(x) y log(y)
y= log(y)
x=log(x)

calculamos la regresion lineal transformando los datos originales (xi, yi) en (log(xi), log(yi))
log(y)= a1 * log(x) + a0

a0= log(A)    --------> A = 10^a0
a1= b

Resultado final: Después de realizar la regresión sobre los datos transformados, volvemos a obtener
A y b, que son los parámetros del modelo original y=A⋅x^b
*/
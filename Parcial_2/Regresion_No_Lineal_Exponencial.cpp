#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>      // Para log y exp
#include <stdexcept>  // Para lanzar excepciones

using namespace std;

// Función para calcular regresión exponencial
void regresionExponencial(const vector<double>& X, const vector<double>& Y) {
    int n = X.size();
    double sumX = 0, sumLnY = 0, sumX2 = 0, sumXLnY = 0;

    // Cálculo de las sumas (transformamos Y usando logaritmo natural)
    for (int i = 0; i < n; i++) {
        if (Y[i] <= 0) {
            cerr << "Error: Los valores de Y deben ser positivos para aplicar el logaritmo natural." << endl;
            return;
        }
        double lnY = log(Y[i]);
        sumX += X[i];
        sumLnY += lnY;
        sumX2 += X[i] * X[i];
        sumXLnY += X[i] * lnY;
    }

    // Verificar el denominador para la pendiente a1
    double denominador = (n * sumX2 - sumX * sumX);

    try {
        // Verificamos si el denominador es cero
        if (denominador == 0) {
            throw runtime_error("Error: División por cero en el cálculo de la pendiente (a1). Los valores de X son idénticos.");
        }

        // Cálculo de los coeficientes a1 (pendiente) y a0 (intersección) para el modelo linealizado
        double a1 = (n * sumXLnY - sumX * sumLnY) / denominador;
        double a0 = (sumLnY - a1 * sumX) / n;

        // Convertir a los coeficientes del modelo exponencial
        double A = exp(a0);  // A = e^a0
        double b = a1;       // b es directamente a1

        // Mostrar la fórmula general del modelo exponencial
        cout << "Modelo exponencial ajustado: y = " << fixed << setprecision(4) << A << " * e^(" << b << " * x)" << endl;

        // Mostrar los coeficientes A y b
        cout << "A (factor) = " << fixed << setprecision(4) << A << endl;
        cout << "b (exponente) = " << fixed << setprecision(4) << b << endl << endl;

        // Mostrar la tabla con los valores Xi, Yi, ln(Yi), Xi^2, Xi*ln(Yi)
        cout << left << setw(10) << "Xi" << setw(10) << "Yi" << setw(10) << "ln(Yi)" << setw(10) << "Xi^2" << setw(15) << "Xi*ln(Yi)" << endl;
        cout << "---------------------------------------------------------" << endl;

        for (int i = 0; i < n; i++) {
            double lnY = log(Y[i]);
            cout << left << setw(10) << X[i] << setw(10) << Y[i] << setw(10) << lnY << setw(10) << X[i] * X[i] << setw(15) << X[i] * lnY << endl;
        }

        // Mostrar los totales
        cout << "---------------------------------------------------------" << endl;
        cout << left << setw(10) << sumX << setw(10) << sumLnY << setw(10) << sumX2 << setw(10) << sumXLnY << endl;
    }
    catch (const runtime_error& e) {
        // Capturar la excepción si el denominador es 0
        cerr << e.what() << endl;
    }
}

int main() {
    // Ejemplo proporcionado
    vector<double> X = {1, 2, 3, 4, 5, 6, 7};
    vector<double> Y = {0.50, 2.50, 2, 4, 3.5, 6, 5.5};

    // Calcular y mostrar la regresión exponencial
    regresionExponencial(X, Y);
    cout <<"\nla columna yi no tiene sumatoria total, el resultado que aparece hay que dezplazarlo a la derecha.\n\n";
    return 0;
}
/*
A es el valor de 𝑦 cuando x=0 (es decir, es la intersección en el eje y, ya que 𝑒^0=1).
b determina la tasa de crecimiento o decrecimiento exponencial. Si 𝑏>0, el modelo muestra crecimiento exponencial; si 𝑏<0, muestra decaimiento exponencial.

y=Ae^bx, tomamos log de cada lado: ln(y)= ln(A)+bx, esa va a ser la forma linealizada.
ln(y) es la variable dependiente
x variable independiente
ln(A) es la interseccion, (ln(A)=a0 en un modelo lineal)
b es la pendiente de la recta (b=a1 en un modelo lineal)
por lo tanto (xi, yi)= (xi, ln(yi))

ln(y)=ln(A)+bx
ln(y)=a0 + a1 x

ln(A)=a0
b= a1

luego de eso debemos mostrar la forma exponencial original del modelo:
para obtener A, aplicamos la inversa del logaritmo, ln(A)=a0 <---> A=e^a0
el valor de b es directamente a1.

y=Ae^bx ------> A = e^a0
        ------> b = a1

y=(e^a0)* e^bx
*/
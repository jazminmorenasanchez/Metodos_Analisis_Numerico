#include <iostream>
#include <iomanip>

using namespace std;

double metodoTrapeciosConTabla(double x[], double y[], int n) {
    double h = x[1] - x[0];  // Suponemos que los puntos están equiespaciados
    double sum = 0.0;

    // Imprimir el valor de h
    cout << "Valor de h = " << h << endl << endl;

    // Imprimir la tabla
    cout << left << setw(10) << "X" << setw(10) << "Y" << endl;
    cout << "------------------------" << endl;
    for (int i = 0; i <= n; i++) {
        cout << left << setw(10) << fixed << setprecision(4) << x[i] << setw(10) << fixed << setprecision(4) << y[i] << endl;
        if (i == 0 || i == n) {
            sum += y[i];
        } else {
            sum += 2 * y[i];
        }
    }

    // Cálculo final
    double resultado = (h / 2) * sum;

    // Mostrar el cálculo de I_T
    cout << "\nCalculo de It:" << endl;
    cout << "It = [ h / 2 ] * [ f(x0) + 2 * sum f(xi) + f(xn)]" << endl;
    cout << "It = [" << h << "/ 2 ] * [ " << y[0] << " + 2 * sum f(xi) + " << y[n] << "]" << endl;
    cout << "It = " << resultado << endl;

    return resultado;
}

int main() {
    // Valores de X e Y dados
    double x[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5};
    double y[] = {1.0, 7.0, 4.0, 3.0, 5.0, 9.0};
    int n = 5;  // Número de intervalos (n = cantidad de puntos - 1)

    // Calcular la integral usando el método de los trapecios con tabla
    metodoTrapeciosConTabla(x, y, n);

    return 0;
}
/*
técnica de integración numérica que se utiliza para aproximar el valor de una integral definida. 
Se basa en aproximar la curva de la función mediante segmentos lineales, formando una serie de trapecios bajo la curva.

Funcionamiento del Método de Trapecios:
El método de trapecios divide el intervalo de integración [a,b] en varios subintervalos. 
Luego, cada par de puntos consecutivos se conecta mediante una línea recta, formando un trapecio. 
El área de cada trapecio se calcula y luego se suman todas esas áreas para obtener una aproximación de la integral.

Fórmula:
La fórmula del método de trapecios para aproximar una integral ∫𝑏𝑎 𝑓(𝑥)𝑑𝑥 es:
It = [(b - a) / (2 * n)] * [f(x0) + 2 * sum(f(xi)) + f(xn)]

Donde:
h = (b−a) / n es el ancho de cada subintervalo.
f(x0) y f(xn) son los valores de la función en los extremos del intervalo.
La suma 2 ∑ 𝑓(𝑥𝑖) incluye los valores de la función en todos los puntos interiores, multiplicados por 2, 
ya que estos puntos aparecen en dos trapecios.

Dividir el intervalo [a,b] en n subintervalos de igual tamaño, donde n puede ser par o impar.
Calcular los valores de la función f(x) en los extremos y en los puntos intermedios del intervalo.
Aplicar la fórmula del método de trapecios, que suma los valores de la función en los puntos inicial y final, y el doble de los valores en los puntos intermedios.
Multiplicar por h/2 para obtener la aproximación de la integral.
*/
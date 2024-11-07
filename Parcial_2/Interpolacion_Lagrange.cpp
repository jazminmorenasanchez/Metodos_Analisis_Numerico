#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

// Función auxiliar para calcular el producto de diferencias de x en el denominador
double calcularDenominador(const vector<double>& X, int i) {
    double producto = 1.0;
    for (int j = 0; j < X.size(); j++) {
        if (j != i) {
            producto *= (X[i] - X[j]);
        }
    }
    return producto;
}

// Función para construir el término L_i(x) expandido
string construirTerminoLagrangeExpandido(const vector<double>& X, int i) {
    double coeficiente = 1.0 / calcularDenominador(X, i);
    stringstream termino;
    termino << fixed << setprecision(4) << coeficiente;
    
    for (int j = 0; j < X.size(); j++) {
        if (j != i) {
            termino << " * (x - " << X[j] << ")";
        }
    }
    return termino.str();
}

// Función para mostrar el polinomio de Lagrange en formato expandido
string construirPolinomioLagrange(const vector<double>& X, const vector<double>& Y) {
    stringstream polinomio;
    int n = X.size() - 1;
    polinomio << "f" << n << "(x) = ";
    
    // Crear los términos L_i(x) * y(x_i) en formato expandido
    for (int i = 0; i < X.size(); i++) {
        polinomio << "(L_" << i << "(x) * y(x_" << i << "))";
        if (i < X.size() - 1) {
            polinomio << " + ";
        }
    }
    polinomio << "\n\n";

    // Crear las fórmulas detalladas para cada L_i(x) y los valores de y(xi)
    for (int i = 0; i < X.size(); i++) {
        polinomio << "L_" << i << "(x) = " << construirTerminoLagrangeExpandido(X, i) << endl;
        polinomio << "y(x_" << i << ") = " << Y[i] << endl << endl;
    }

    return polinomio.str();
}

int main() {
    // Valores X e Y dados (se pueden modificar para cualquier número de puntos)
    vector<double> X = {-1, 0, 1, 2};  // Puntos X dados
    vector<double> Y = {2.0, -0.7183, 0, 0.8964};  // Puntos Y dados

    // Construir y mostrar el polinomio de Lagrange
    string polinomio = construirPolinomioLagrange(X, Y);
    cout << polinomio << endl;

    return 0;
}

/*
P(x)= sumatoria [ yi * L_i(x) ]
L_i(x) = multiplicacion [ (x - xi) / (xi - xj) ] para i=0 hasta n-1, donde i distinto j

Permite calcular el polinomio interpolante directamente utilizando los puntos dados. El polinomio de grado 
n−1 para n puntos se expresa como una suma de términos llamados polinomios base de Lagrange.

Es directo y no requiere cálculo de diferencias divididas ni ningún otro proceso intermedio.
La fórmula de Lagrange es simétrica, lo que significa que el orden de los puntos no afecta la forma del polinomio.
Produce un único polinomio que pasa por todos los puntos.
Requiere recalcular el polinomio completo si se añaden nuevos puntos.

ej: n=3 ; L_1(x) = [(x - x0) / (x1 - x0)] * [(x - x1) / (x2 - x1)]

RAZONES POR LAS CUALES EL PROGRAMA PUEDE FALLAR:
-> hay dos valores de x iguales.

-> Polinomios de orden muy alto

-> Extrapolación fuera del rango de los datos:
La interpolación está diseñada para ajustarse dentro del rango de los datos conocidos 
(es decir, entre los valores mínimos y máximos de x). 
Sin embargo, si intentas extrapolar más allá de este rango 
(calcular valores de y para un x que no está en el rango de los puntos de datos), 
el polinomio puede comportarse de manera errática y no confiable.

-> hay una discontinuidad:
Tipos de discontinuidades
Discontinuidad de salto (discontinuidad finita):
Sucede cuando el límite de la función cuando se aproxima al punto 
𝑥=𝑎 desde la izquierda y derecha existe pero no son iguales.
(lim 𝑥→𝑎 𝑓(𝑥))En otras palabras, la función “salta” de un valor a otro.
Ejemplo:
𝑓(𝑥)={2,si 𝑥<1  5, si 𝑥≥1
En 𝑥=1 hay una discontinuidad de salto porque 
f(x) cambia bruscamente de 2 a 5.

Discontinuidad infinita:
Ocurre cuando, al aproximarse a un punto x=a, los valores de la función se acercan a infinito positivo o negativo (
lim 𝑥→𝑎 𝑓(𝑥)=∞
Estas discontinuidades suelen aparecer en funciones racionales con asintotas verticales.
Ejemplo: La función 
𝑓(𝑥)=1/𝑥
tiene una discontinuidad infinita en 𝑥=0 ya que la función tiende a ∞
∞ a medida que 𝑥→0+ y −∞ cuando 𝑥→0-.

Discontinuidad evitable (o removible):
Sucede cuando el límite de la función en un punto 
x=a existe, 
pero la función no está definida en ese punto o está mal definida. 
La discontinuidad puede eliminarse simplemente definiendo correctamente el valor de la función en 
𝑥 y quitando dicho valor del dominio.

Discontinuidad oscilante:
Ocurre cuando la función oscila entre dos valores conforme se acerca al punto 
x=a, y no se puede asignar un límite finito. Un ejemplo clásico es la función 
𝑓(𝑥)=sin⁡(1/𝑥) que oscila cada vez más rápidamente cerca de 𝑥=0
y por tanto no tiene un valor límite definido en ese punto.*/
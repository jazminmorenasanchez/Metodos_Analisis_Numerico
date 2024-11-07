#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>       // Para verificar límites de doble precisión
#include <stdexcept>    // Para manejar excepciones

#define PRECISION 6     // Precisión de la tabla de valores
#define INTERVALOS 10   // Número de intervalos en la función tabuladora

using namespace std;

// Declaración de funciones
double biseccion(double a, double b, double E);  // Método de bisección para encontrar la raíz
double f(double x);                              // Función f(x) que se utilizará para encontrar la raíz
void tabula(double a, double b);                 // Función para tabular valores de f(x) en el intervalo

int main() {
    cout << fixed << setprecision(PRECISION);  // Configura la precisión para mostrar valores
    cout << "\nPrograma para encontrar el Intervalo Adecuado y calcular la Raiz utilizando metodo de la biseccion:\n";

    double a = 0;  // Límite inferior del intervalo
    double b = 1;  // Límite superior del intervalo
    double E = 1e-4;  // Tolerancia de error (0.001)

    cout << "Limite inferior del intervalo :" << a <<endl;
    cout << "Limite superior del intervalo :" << b <<endl;
    cout << "Tolerancia de error: " << E <<endl;

    // Mostramos una tabla de valores de f(x) en el intervalo [a, b]
    tabula(a, b);

    // Intentamos calcular la raíz usando el método de bisección y capturamos cualquier error
    try {
        double raiz = biseccion(a, b, E);
        cout << "\nLa raiz en el intervalo [" << a << "; " << b << "] es: " << raiz << endl;
    } catch (const invalid_argument& e) {
        cout << "Error de argumento: " << e.what() << endl;
    } catch (const overflow_error& e) {
        cout << "Error de desbordamiento: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Error inesperado: " << e.what() << endl;
    }

    return 0;
}

// Implementación del método de bisección
double biseccion(double a, double b, double E) {
    if (a >= b) {
        throw invalid_argument("El valor de 'a' debe ser menor que 'b'.");
    }

    if (E < numeric_limits<double>::epsilon()) {
        throw invalid_argument("El valor de E es demasiado pequeño para el tipo de dato.");
    }

    double fa = f(a);  // Valor de f en a
    double fb = f(b);  // Valor de f en b

    if (fa * fb > 0) {
        throw invalid_argument("La funcion no cambia de signo en el intervalo dado.");
    }

    double c = 0;  // Inicialización del punto medio
    double error = (b - a) / 2;  // Error inicial
    int max_iter = 1000;  // Límite máximo de iteraciones para evitar bucles infinitos
    int iter = 0;  // Contador de iteraciones

    // Encabezado de la tabla
    cout << "\nIteracion\t  a\t\t    b\t\t    c\t\t   f(c)\t\t  Error\n";
    cout << "---------------------------------------------------------------------\n";

    while (error > E && iter < max_iter) {
        c = (a + b) / 2;
        double fc = f(c);

        if (isinf(fc)) {
            throw overflow_error("Desbordamiento al evaluar f(c).");
        }

        // Mostrar los valores de cada iteración en la tabla
        cout << setw(5) << iter << "\t"
             << setw(12) << a << "\t"
             << setw(12) << b << "\t"
             << setw(12) << c << "\t"
             << setw(12) << fc << "\t"
             << setw(12) << error << endl;

        if (fabs(fc) < E) {
            return c;  // Raíz aproximada encontrada
        }

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }

        error = (b - a) / 2;
        iter++;
    }

    if (iter >= max_iter) {
        throw runtime_error("Se alcanzo el numero maximo de iteraciones sin converger.");
    }

    return c;
}

// Función f(x) que queremos encontrar la raíz
double f(double x) {
    if (x > 700 || x < -700) {
        throw overflow_error("Desbordamiento en f(x) debido a un valor extremo.");
    }
    return exp(-x) - x;  // Ejemplo de función; puedes cambiarla según tu problema
}

// Función para tabular valores de f(x) en un intervalo dado [a, b]
void tabula(double a, double b) {
    int puntos = INTERVALOS + 1;
    double ancho = (b - a) / INTERVALOS;

    cout << "\n\tx\t\tf(x) \n";
    for (int i = 0; i < puntos; i++) {
        cout << "\t" << a << "\t" << f(a) << endl;
        a += ancho;
    }
}

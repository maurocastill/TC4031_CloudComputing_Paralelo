#include <iostream>
#include <vector>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para generar una semilla aleatoria con time()
#include <omp.h>  // Librería OpenMP

#define mostrar 10

using namespace std;

// Función que imprime los elementos de un arreglo hasta un tamaño dado
void printArray(vector<int> array, int print_size) {
    for (int i = 0; i < print_size; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";
}

int main() {
    // Mensaje inicial y logo
    cout << "   ++\n";
    cout << "  ++++\n";
    cout << "   ++\n";
    cout << "Este programa realiza la suma de dos arreglos de números enteros utilizando paralelismo con OpenMP.\n\n";

    int size, option, pedazos;

    // Solicitar al usuario el tamaño de los arreglos
    cout << "Ingrese el tamaño de los arreglos: ";
    if (!(cin >> size) || size <= 0) {
        cout << "Entrada inválida. Debe ingresar un número entero positivo.\n";
        return 1;
    }

    // Solicitar al usuario el tamaño de los pedazos (chunk)
    cout << "Ingrese el tamaño de los pedazos (chunk) para cada hilo: ";
    if (!(cin >> pedazos) || pedazos <= 0) {
        cout << "Entrada inválida. Debe ingresar un número entero positivo.\n";
        return 1;
    }

    // Crear arreglos dinámicos con el tamaño definido por el usuario
    vector<int> array1(size);
    vector<int> array2(size);
    vector<int> result(size);

    // Solicitar al usuario la opción de generación de datos
    cout << "\nSeleccione una opción:\n";
    cout << "1. Crear los arreglos con valores aleatorios\n";
    cout << "2. Ingresar los valores manualmente\n";
    cout << "Opción: ";
    cin >> option;

    if (option == 1) {
        // Generar valores aleatorios para los arreglos
        srand(time(0)); // Semilla para los valores aleatorios
        for (int i = 0; i < size; i++) {
            array1[i] = rand() % 100; // Valores entre 0 y 99
            array2[i] = rand() % 100; // Valores entre 0 y 99
        }
        cout << "Arreglos generados con valores aleatorios.\n";
    }
    else if (option == 2) {
        // Solicitar al usuario que ingrese los valores manualmente
        cout << "Ingrese los valores para el arreglo 1:\n";
        for (int i = 0; i < size; i++) {
            cout << "Elemento " << i + 1 << ": ";
            while (!(cin >> array1[i])) {
                cout << "Entrada inválida. Ingrese un número entero: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cout << "Ingrese los valores para el arreglo 2:\n";
        for (int i = 0; i < size; i++) {
            cout << "Elemento " << i + 1 << ": ";
            while (!(cin >> array2[i])) {
                cout << "Entrada inválida. Ingrese un número entero: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    else {
        cout << "Opción inválida. Saliendo del programa.\n";
        return 1;
    }

    // Variables para control del paralelismo
    int i;

    // Realizar la suma de los arreglos usando paralelismo con OpenMP
#pragma omp parallel for \
        shared(array1, array2, result, pedazos) private(i) \
        schedule(static, pedazos)
    for (i = 0; i < size; i++) {
        result[i] = array1[i] + array2[i];
    }

    // Imprimir los arreglos y el resultado (solo los primeros "mostrar" elementos si son muy grandes)
    int print_size = min(size, mostrar);
    cout << "\nPrimeros " << print_size << " elementos de los arreglos:\n";

    cout << "Arreglo 1: ";
    printArray(array1, print_size);

    cout << "Arreglo 2: ";
    printArray(array2, print_size);

    cout << "Resultado: ";
    printArray(result, print_size);

    return 0;
}
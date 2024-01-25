// SolucionSumaArreglosParalela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.


#include <iostream>
#include <omp.h>
#include <cstdlib> //Librería para  llamar funciones para generar numeros aleatorios.
#include <ctime> // librería para funciones de cálculo de tiempo de ejecución

void imprimeArreglo(float *d, int size);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    //float a[N], b[N], c[N];
    int i;
    // Solicitar la cantidad de elementos N al usuario
    int N;
    std::cout << "Ingrese la cantidad de elementos N: ";
    std::cin >> N;
    // Solicitar la cantidad de pedazos al usuario
    int chunk;
    std::cout << "Ingrese la cantidad  de pedazos (chunk): ";
    std::cin >> chunk;
    // Solicitar la cantidad de elementos a mostrar al usuario
    int mostrar;
    std::cout << "Ingrese la cantidad  de elementos a mostrar: ";
    std::cin >> mostrar;

    // Inicializar la semilla para generar números aleatorios
    std::srand(std::time(0));

    // Generar arreglos aleatorios para a y b
    float* a = new float[N];
    float* b = new float[N];
    float* c = new float[N];

    for (i = 0; i < N; i++)
    {
        a[i] = std::rand() % 1000;  // Números aleatorios entre 0 y 999
        b[i] = std::rand() % 1000;
        //a[i] = i * 10;
        //b[i] = (i + 3) * 3.7;
    }
    int pedazos = chunk;
    double start_time = omp_get_wtime(); //Inicio de tiempo de ejecución
    
    #pragma omp parallel for shared(a,b,c,pedazos) private(i) schedule (static,pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
   
    double end_time = omp_get_wtime(); //Fin de tiempo de ejecución
    double execution_time = end_time - start_time;  // Cálculo de la diferencia
    
    std::cout << "Tiempo de ejecución: " << execution_time << " segundos" << std::endl; // Impresión del tiempo de ejecución
    std:: cout << "Imprimiendo los primero " << mostrar << " valores del arreglo a:" << std::endl;
    imprimeArreglo(a,mostrar);
    std::cout << "Imprimiendo los primero " << mostrar << " valores del arreglo b:" << std::endl;
    imprimeArreglo(b,mostrar);
    std::cout << "Imprimiendo los primero " << mostrar << " valores del arreglo c:" << std::endl;
    imprimeArreglo(c,mostrar);
     
    // Liberar la memoria asignada dinámicamente
    delete[] a;
    delete[] b;
    delete[] c;

}
void imprimeArreglo(float *d, int size)
{
    for (int x = 0; x < size; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}

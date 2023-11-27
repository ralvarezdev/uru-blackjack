#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::string;

// --- Prototipos de funciones
void ingreseEnterParaContinuar();
bool seleccionSimple(string mensaje);
void limpiarTerminal();
void encabezado(string titulo);

// Función para detener el flujo del programa hasta que el usuario ingrese Enter
void ingreseEnterParaContinuar()
{
    string temp;

    cout << "\n\nPresione 'Enter' para Continuar: ";
    getline(cin, temp);
}

// Función para permitir que el usuario seleccione entre dos opciones
bool seleccionSimple(string mensaje)
{
    string entrada;
    char c;

    do
    {
        cout << mensaje << " [y/N]: ";
        cin >> entrada;

        c = tolower(entrada[0]);
        if (c == 'y')
            return true;
        else if (c == 'n')
            return false;
    } while (true);
}

// Función para limpiar el terminal
void limpiarTerminal()
{
#ifdef _WIN32 // Para Windows
    system("cls");
#else // Para Linux
    system("clear");
#endif
}

// Función para imprimir un encabezado
void encabezado(string titulo)
{
    limpiarTerminal();
    cout << titulo << "\n";
}
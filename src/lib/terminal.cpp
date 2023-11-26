#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

void ingreseEnterParaContinuar()
{
    cout << "\n\nPresione 'Enter' para Continuar: ";
    cin.get();
}

// Funcion para permitir que el usuario seleccione entre dos opciones
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

// Limpia el terminal, e imprime un encabezado
void limpiarTerminal()
{
#ifdef _WIN32 // Para Windows
    system("cls");
#else // Para Linux
    system("clear");
#endif
}

void encabezado(string titulo)
{
    limpiarTerminal();
    cout << titulo << "\n";
}
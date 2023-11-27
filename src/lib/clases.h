#include <vector>
#include <string>

using std::string;
using std::vector;

#ifndef CLASES_H
#define CLASES_H

// Clase de la mesa
class Mesa
{
public:
    bool out;
    int numeroAs, sumaCartas;
    vector<int> apuestas, cartas;

    void reiniciarDatos();

    // Constructor
    Mesa()
    {
        out = numeroAs = sumaCartas = 0;
    }
};

// Clase de los jugadores
class Jugador
{
public:
    bool out, stand, ganador, empate, bancarrota;
    int dinero, numeroAs, sumaCartas;
    vector<int> cartas;

    void reiniciarDatos();

    // Constructor
    Jugador()
    {
        out = stand = ganador = empate = bancarrota = dinero = numeroAs = sumaCartas = 0;
    }
};

// Clase del tablero
class Tablero
{
public:
    int cartasUsadas, ronda, numeroMazo;
    int numeroJugadores, duplicarApuesta, apuestaInicial, dineroInicial;

    void imprimirStats(string titulo, vector<int> *apuestas, vector<Jugador> *jugadoresStats);
    void imprimirCartas(int n, vector<int> *cartas, int *sumaCartas);
    void imprimirTablero(vector<Jugador> *jugadoresStats);

    // Constructor
    Tablero()
    {
        cartasUsadas = numeroMazo = 0;
        ronda = 1;
    }
};

#endif
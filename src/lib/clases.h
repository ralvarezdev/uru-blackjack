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
    vector<int> apuestas,  cartas;

    void reiniciarDatos();

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

    Jugador()
    {
        out = stand = ganador = empate = bancarrota = dinero = numeroAs = sumaCartas = 0;
    }
};

class Tablero
{
public:
    int cartasUsadas, ronda, numeroMazo;
    int numeroJugadores, duplicarApuesta, apuestaInicial, dineroInicial;

    void imprimirStats(string titulo, vector<int> apuestas, vector<Jugador> jugadoresStats);
    void imprimirCartas(int n, vector<int> &cartas, int &sumaCartas);
    void imprimirTablero(vector<Jugador> &jugadoresStats);

    Tablero()
    {
        cartasUsadas = numeroMazo = 0;
        ronda = 1;
    }
};

#endif
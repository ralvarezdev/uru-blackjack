#include<vector>
#include<string>

using std::vector;
using std::string;

#ifndef CLASES_H
#define CLASES_H

    class Mesa{ // Clase de la mesa
        public:
            bool out = false;
            int numeroAs = 0, sumaCartas = 0;
            vector<int> apuestas;
            vector<int> cartas;
            
            void reiniciarDatos();
    };

    class Jugador{ // Clase de los jugadores
        public:
            bool out = false, stand = false, ganador = false, empate = false, bancarrota = false;
            int dinero = 0, numeroAs = 0, sumaCartas = 0;
            vector<int> cartas;

            void reiniciarDatos();
    };

    class Tablero{
        public:
            int cartasUsadas = 0, ronda = 1, numeroMazo = 0;
            int numeroJugadores, duplicarApuesta, apuestaInicial, dineroInicial;

            void imprimirStats(string titulo, vector<int> apuestas, vector<Jugador> jugadoresStats);
            void imprimirCartas(int n, vector<int>& cartas, int& sumaCartas);
            void imprimirTablero(vector<Jugador>& jugadoresStats);
    };

#endif
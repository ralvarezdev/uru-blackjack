#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "lib/cartas.h"
#include "lib/clases.h"
#include "lib/terminal.h"

using std::cin;
using std::cout;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::vector;

int main()
{
    random_device rd; // Genera la semilla

    int x, y, n, carta, dinero;
    vector<int> mazo;
    string temp, titulo;

    Mesa mesaStats = Mesa();
    vector<Jugador> jugadoresStats;
    Tablero tablero = Tablero();

    titulo = "****** Blackjack ******\nRealizado por: ralvarezdev";

    chequearMazo(&mazo, &tablero.cartasUsadas, &tablero.numeroMazo);
    encabezado(titulo);

    cout << "\n*** NOTA ***\nCuando se reparten las cartas, las abreviaciones de los palos son las siguientes\n"
         << "- Corazon\t'C'\t\t- Diamante\t'D'\n- Trebol\t'T'\t\t- Picas\t\t'P'"
         << "\n\n*** CONFIGURACION ***\n";

    while (true)
        try
        {
            cout << "Ingrese cada cuantas rondas desea que la apuesta inicial se duplique [1-3]: ";
            cin >> temp;
            n = stoi(temp);

            if (n < 1 || n > 3)
                throw(-1);
            break;
        }
        catch (...)
        {
            // Para ignorar mal input
        }
    tablero.duplicarApuesta = n;

    while (true)
        try
        {
            cout << "Ingresa el numero de jugadores [1-8]: ";
            cin >> temp;
            n = stoi(temp);

            if (n < 1 || n > 8)
                throw(-1);
            break;
        }
        catch (...)
        {
            // Para ignorar mal input
        }
    tablero.numeroJugadores = n;

    jugadoresStats.resize(tablero.numeroJugadores);
    mesaStats.apuestas.resize(tablero.numeroJugadores);

    while (true)
        try
        {
            cout << "Ingresa el dinero incial de cada jugador [150-10000]: ";
            cin >> temp;
            n = stoi(temp);

            if (n < 150)
                n = 150;
            else if (n > 10000)
                n = 10000;
            break;
        }
        catch (...)
        {
            // Para ignorar mal input
        }
    tablero.dineroInicial = n;

    for (x = 0; x < tablero.numeroJugadores; x++)
        jugadoresStats[x].dinero = tablero.dineroInicial;

    ingreseEnterParaContinuar();
    while (true)
    {
        if (tablero.ronda != 1 && (tablero.ronda + 1) % tablero.duplicarApuesta == 0)
            tablero.apuestaInicial *= 2;
        else if (tablero.ronda == 1)
            tablero.apuestaInicial = tablero.dineroInicial / 15;

        if (tablero.apuestaInicial % 10 != 0)
            tablero.apuestaInicial += 10 - tablero.apuestaInicial % 10;

        for (x = 0; x < tablero.numeroJugadores; x++)
        {
            dinero = jugadoresStats[x].dinero;
            jugadoresStats[x].bancarrota = (dinero == 0);

            if (dinero >= tablero.apuestaInicial)
            {
                jugadoresStats[x].dinero -= tablero.apuestaInicial;
                mesaStats.apuestas[x] = tablero.apuestaInicial;
            }
            else if (!jugadoresStats[x].bancarrota)
            {
                jugadoresStats[x].dinero = 0;
                mesaStats.apuestas[x] = dinero;
            }
        }
        tablero.imprimirStats(titulo, &mesaStats.apuestas, &jugadoresStats);
        ingreseEnterParaContinuar();

        for (y = 0; y < 2; y++)
        {
            uniform_int_distribution<int> dist(0, 51 - tablero.cartasUsadas);
            carta = revolverCarta(dist(rd), &mazo, &tablero.cartasUsadas, &tablero.numeroMazo);

            mesaStats.cartas.push_back(carta);
            puntajeCarta(carta, &mesaStats.numeroAs, &mesaStats.sumaCartas, &mesaStats.out);
        }

        for (x = 0; x < tablero.numeroJugadores; x++)
            if (!jugadoresStats[x].bancarrota)
            {
                tablero.imprimirStats(titulo, &mesaStats.apuestas, &jugadoresStats);

                cout << "\n\n*** Cartas del jugador " << x + 1 << " ***";
                for (y = 0; y < 2; y++)
                {
                    uniform_int_distribution<int> dist(0, 51 - tablero.cartasUsadas);
                    carta = revolverCarta(dist(rd), &mazo, &tablero.cartasUsadas, &tablero.numeroMazo);

                    jugadoresStats[x].cartas.push_back(carta);
                    puntajeCarta(carta, &jugadoresStats[x].numeroAs, &jugadoresStats[x].sumaCartas, &jugadoresStats[x].out);
                    imprimirCarta(true, carta);
                }
                cout << "\nTotal: " << jugadoresStats[x].sumaCartas;
                ingreseEnterParaContinuar();
            }

        y = 0;
        while (y <= tablero.numeroJugadores)
            for (x = 0; x < tablero.numeroJugadores; x++)
            {

                if (jugadoresStats[x].bancarrota || jugadoresStats[x].stand || jugadoresStats[x].out)
                {
                    y++;
                    continue;
                }

                tablero.imprimirStats(titulo, &mesaStats.apuestas, &jugadoresStats);

                cout << "\n\n*** Mesa ***";
                imprimirCarta(true, mesaStats.cartas[0]);
                cout << "\n- ??";

                tablero.imprimirCartas(x, &jugadoresStats[x].cartas, &jugadoresStats[x].sumaCartas);
                cout << "\n\n";

                jugadoresStats[x].out = (seleccionSimple("Desea retirarse?"));
                if (jugadoresStats[x].out)
                    continue;

                bool r;
                if (jugadoresStats[x].cartas.size() == 2 && jugadoresStats[x].dinero >= mesaStats.apuestas[x])
                    r = (seleccionSimple("Desea aumentar la apuesta?"));

                if (r)
                {
                    int apuesta = mesaStats.apuestas[x];
                    dinero = jugadoresStats[x].dinero;

                    while (true)
                        try
                        {
                            cout << "\nPuede aumentar su apuesta el doble o un monto mayor\n- Cuanto desea aumentar la apuesta: ";
                            cin >> temp;
                            n = stoi(temp);

                            if (n < apuesta || n > dinero)
                                continue;
                            break;
                        }
                        catch (...)
                        {
                            // Para ignorar mal input
                        }

                    cout << "\n";
                    mesaStats.apuestas[x] += n;
                    jugadoresStats[x].dinero -= n;
                }

                jugadoresStats[x].stand = !seleccionSimple("Desea agarrar mas cartas?");
                if (jugadoresStats[x].stand)
                    continue;

                uniform_int_distribution<int> dist(0, 51 - tablero.cartasUsadas);
                carta = revolverCarta(dist(rd), &mazo, &tablero.cartasUsadas, &tablero.numeroMazo);

                imprimirCarta(true, carta);
                jugadoresStats[x].cartas.push_back(carta);

                puntajeCarta(carta, &jugadoresStats[x].numeroAs, &jugadoresStats[x].sumaCartas, &jugadoresStats[x].out);
                cout << "\nTotal: " << jugadoresStats[x].sumaCartas;

                cin.ignore();
                ingreseEnterParaContinuar();
            }

        tablero.imprimirStats(titulo, &mesaStats.apuestas, &jugadoresStats);
        cout << "\n\nTodos los jugadores estan listos para mostrar sus cartas...";
        ingreseEnterParaContinuar();

        while (mesaStats.sumaCartas < 17)
        {
            uniform_int_distribution<int> dist(0, 51 - tablero.cartasUsadas);
            carta = revolverCarta(dist(rd), &mazo, &tablero.cartasUsadas, &tablero.numeroMazo);

            mesaStats.cartas.push_back(carta);
            puntajeCarta(carta, &mesaStats.numeroAs, &mesaStats.sumaCartas, &mesaStats.out);
        }

        int m = mesaStats.cartas.size();
        int sumaCartasMesa = mesaStats.sumaCartas;
        for (x = 0; x < tablero.numeroJugadores; x++)
        {
            if (jugadoresStats[x].bancarrota)
                continue;

            n = jugadoresStats[x].cartas.size();
            int sumaCartasJugador = jugadoresStats[x].sumaCartas;

            if (jugadoresStats[x].out)
                jugadoresStats[x].ganador = false;
            else if (mesaStats.out || sumaCartasJugador > sumaCartasMesa || (sumaCartasJugador == sumaCartasMesa && n < m))
                jugadoresStats[x].ganador = true;
            else
            {
                jugadoresStats[x].ganador = false;
                if (sumaCartasJugador == sumaCartasMesa && n == m)
                    jugadoresStats[x].empate = true;
            }

            if (jugadoresStats[x].ganador)
                jugadoresStats[x].dinero += 2 * mesaStats.apuestas[x];
            else if (jugadoresStats[x].empate)
                jugadoresStats[x].dinero += mesaStats.apuestas[x];

            mesaStats.apuestas[x] = 0;
        }
        tablero.imprimirStats(titulo, &mesaStats.apuestas, &jugadoresStats);

        cout << "\n\n*** Mesa ***";
        for (x = 0; x < mesaStats.cartas.size(); x++)
            imprimirCarta(true, mesaStats.cartas[x]);
        cout << "\nTotal: " << mesaStats.sumaCartas << "\n";

        tablero.imprimirTablero(&jugadoresStats);
        ingreseEnterParaContinuar();

        tablero.imprimirStats(titulo, &mesaStats.apuestas, &jugadoresStats);
        cout << "\n\nRonda culminada: Analizando jugadores que quedaron en bancarrota...";
        ingreseEnterParaContinuar();

        n = 0;
        for (x = 0; x < tablero.numeroJugadores; x++)
        {
            jugadoresStats[x].reiniciarDatos();

            if (jugadoresStats[x].dinero == 0)
                n++;
        }
        mesaStats.reiniciarDatos();

        if (n == tablero.numeroJugadores)
            break;
        else
            tablero.ronda++;
    }

    for (x = 0; x < tablero.numeroJugadores; x++)
        jugadoresStats[x].bancarrota = true;

    tablero.imprimirStats(titulo, &mesaStats.apuestas, &jugadoresStats);
    ingreseEnterParaContinuar();
    limpiarTerminal();
    cout << "Todos los jugadores quedaron en bancarrota...\n";
    mensajeFinal("LA CASA SIEMPRE GANA");
    ingreseEnterParaContinuar();
}
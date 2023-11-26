#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <chrono>
#include <thread>

#include "clases.h"
#include "terminal.h"

using std::cout;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::vector;

// Evalúa si la carta es un As
bool esUnAs(int carta)
{
    if (carta % 13 == 0)
        return true;
    else
        return false;
}

// Devuelve la cantidad de puntos de la carta
void puntajeCarta(int carta, int *numeroAsParticipante, int *sumaCartasParticipante, bool *outParticipante)
{
    int numero = carta % 13 + 1;

    if (esUnAs(carta))
    {
        *numeroAsParticipante += 1;
        *sumaCartasParticipante += 11;
    }
    else if (numero != 1 && numero < 11)
        *sumaCartasParticipante += numero;
    else
        *sumaCartasParticipante += 10;

    while (*sumaCartasParticipante > 21 && *numeroAsParticipante >= 1)
    {
        *sumaCartasParticipante -= 10;
        *numeroAsParticipante -= 1;
    };

    if (*sumaCartasParticipante > 21)
        *outParticipante = true;
}

// Según el número de la carta, imprime cuál es
void imprimirCarta(bool nuevaLinea, int carta)
{
    int x = carta / 13;
    carta -= 13 * x;

    if (nuevaLinea == true)
        cout << "\n";

    switch (x)
    {
    case 0:
        cout << "- C";
        break;
    case 1:
        cout << "- D";
        break;
    case 2:
        cout << "- T";
        break;
    case 3:
        cout << "- P";
        break;
    }

    if (carta == 0)
        cout << "A";
    else
        switch (carta)
        {
        case 10:
            cout << "J";
            break;
        case 11:
            cout << "Q";
            break;
        case 12:
            cout << "K";
            break;
        default:
            cout << carta + 1;
        }
}

// Chequea si quedan cartas en el mazo, de no haber generado un nuevo mazo
void chequearMazo(vector<int> *mazo, int *cartasUsadas, int *numeroMazo)
{
    if ((*mazo).size() == 0)
    {
        *cartasUsadas = 0;
        *numeroMazo++;

        for (int x = 0; x < 52; x++)
            (*mazo).push_back(x);
    }
}

// Saca una carta aleatoria del mazo
int revolverCarta(int numero, vector<int> *mazo, int *cartasUsadas, int *numeroMazo)
{
    int carta = (*mazo)[numero];
    (*mazo).erase((*mazo).begin() + numero);
    *cartasUsadas += 1;

    chequearMazo(mazo, cartasUsadas, numeroMazo);

    return carta;
}

void mensajeFinal(string mensaje)
{
    random_device rd;

    char c;
    int x, n, numero, vectorSize, mensajeSize, mensajeAleatorioDiff, mensajeAleatorioSize = 0;
    string mensajeAleatorio;

    mensajeSize = mensaje.size();

    vector<char> alfabeto{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    vector<char> simbolos{' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                          '+', '-', '*', '/', '!', '@', '$', '%', '&', '^', '?'};
    vector<char> caracteres, caracteresAleatorio;

    vectorSize = alfabeto.size();
    for (x = 0; x < vectorSize; x++)
        alfabeto.push_back(toupper(alfabeto[x]));

    caracteres.insert(caracteres.begin(), alfabeto.begin(), alfabeto.end());
    caracteres.insert(caracteres.end(), simbolos.begin(), simbolos.end());
    alfabeto.clear();
    simbolos.clear();
    vectorSize = caracteres.size();

    for (x = 0; x < vectorSize; x++)
    {
        n = x + 1;
        uniform_int_distribution<int> dist(0, vectorSize - n);
        numero = dist(rd);
        c = caracteres[numero];
        caracteres.erase(caracteres.begin() + numero);
        caracteresAleatorio.push_back(c);
    }

    mensajeAleatorioDiff = mensajeSize;
    do
    {
        for (x = 0; x < vectorSize; x++)
        {
            c = caracteresAleatorio[x];
            cout << "\r--- " << mensajeAleatorio << c << string(mensajeAleatorioDiff - 1, '#') << " ---";

            if (c == mensaje[mensajeAleatorioSize])
            {
                mensajeAleatorioSize++;
                mensajeAleatorioDiff--;
                mensajeAleatorio.append(string(1, c));
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

        if (mensajeAleatorioDiff == 0)
            break;
    } while (true);
}
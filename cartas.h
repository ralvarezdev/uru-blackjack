#include"clases.h"
#include<vector>
#include<string>

using std::vector;
using std::string;

#ifndef CARTAS_H
#define CARTAS_H

    bool esUnAs(int carta);
    void puntajeCarta(int carta, int& numeroAsParticipante, int& sumaCartasParticipante, bool& outParticipante);
    void imprimirCarta(bool nuevaLinea, int carta);
    void chequearMazo(vector<int>& mazo, int& cartasUsadas, int& numeroMazo);
    int revolverCarta(int numero, vector<int>& mazo, int& cartasUsadas, int& numeroMazo);
    void mensajeFinal(string mensaje);

#endif
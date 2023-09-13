#include"cartas.h"
#include"clases.h"
#include"ioTerminal.h"
#include<iostream>
#include<string>

using std::cout;
using std::string;

void Mesa::reiniciarDatos(){ // Método para eliminar los elementos del vector, asignar valor 0 a los enteros, y falso a los booleanos
    cartas.clear();
    numeroAs = 0; sumaCartas = 0;
    out = false;
}

void Jugador::reiniciarDatos(){
    cartas.clear();
    numeroAs = 0; sumaCartas = 0;
    out = false; stand = false; ganador = false; empate = false;
}

void Tablero::imprimirStats(string titulo, vector<int> apuestas, vector<Jugador> jugadoresStats){ // Imprime la apuesta y dinero de cada jugador
    int x, dinero, apuesta;
    
    encabezado(titulo);
    cout<<"\nRonda: "<<ronda<<"\t| Apuesta inicial: "<<apuestaInicial<<"\t| Mazos: "<<numeroMazo;
    cout<<"\n"<<string(65, '-');

    for(x=0;x<numeroJugadores;x++){
        dinero = jugadoresStats[x].dinero;
        apuesta = apuestas[x];

        cout<<"\nJugador "<<x+1;
        if(jugadoresStats[x].bancarrota==false){
            cout<<"\t| Dinero: "<<dinero;

            if(apuestaInicial!=0&&dinero!=0){
                cout<<"\t\t| Apuesta: "<<apuesta;
            }else if(dinero==0){
                cout<<"\t\t| Apuesta: "<<apuesta<<" ALL-IN";
            }
        }else{
            cout<<"\t| BANCARROTA\t\t|";
        }
    }
}

void Tablero::imprimirCartas(int n, vector<int>& cartas, int& sumaCartas){ // Imprime las cartas de un jugador en específico
    int x, carta;

    cout<<"\n\n*** Cartas del jugador "<<n+1<<" ***";
    for(x=0;x<cartas.size();x++){
        carta = cartas[x];
        imprimirCarta(true, carta);
    }
    cout<<"\nTotal: "<<sumaCartas;
}

void Tablero::imprimirTablero(vector<Jugador>& jugadoresStats){ // Imprime las cartas de todos los jugadores
    bool imprimirMas;
    int x, y, n, numeroJugadores, carta, filas, filasCartas, columnas;
    string separacion;
    vector<int> cantidadCartas;

    numeroJugadores = jugadoresStats.size();

    if(numeroJugadores%4==0){
        filas = numeroJugadores/4;
    }else{
        filas = numeroJugadores/4+1;
    }

    if(numeroJugadores<4){
        separacion = string(17*numeroJugadores-5, '-');
    }else{
        separacion = string(17*4-5, '-');
    }
        
    for(x=0;x<filas;x++){
        imprimirMas = true;
        filasCartas = 0;
        cantidadCartas.clear();

        if((numeroJugadores-4*x)>=4){
            columnas = 4;
        }else{
            columnas = numeroJugadores - (4*x);
        }
            
        cout<<"\n"<<separacion<<"\n";
        for(y=0;y<columnas;y++){
            n = 4*x+y;
            cantidadCartas.push_back(jugadoresStats[n].cartas.size());

            cout<<"Jug "<<n+1;
            if(jugadoresStats[n].out==true&&jugadoresStats[n].sumaCartas<=21){
                cout<<" [Ret]";
            }else if(jugadoresStats[n].ganador==true){
                cout<<" [Gan]";
            }else if(jugadoresStats[n].empate==true){
                cout<<" [Emp]";
            }else if(jugadoresStats[n].bancarrota==false){
                cout<<" [Per]";
            }else{
                cout<<" [Ban]";
            }

            if(y!=columnas-1){
                cout<<"\t| ";
            }
        }

        while(imprimirMas){
            for(y=0;y<columnas;y++){
                n = 4*x+y;

                if(jugadoresStats[n].bancarrota==false){
                    carta = jugadoresStats[n].cartas[filasCartas];

                    if(y==0){
                        if(filasCartas<cantidadCartas[y]){
                            imprimirCarta(true, carta);
                        }else if(filasCartas>=cantidadCartas[y]){
                            cout<<"\n";
                        }
                    }else if(filasCartas<cantidadCartas[y]){
                        imprimirCarta(false, carta);
                    }
                }else if(y==0&&filasCartas>=cantidadCartas[y]){
                    cout<<"\n";
                }

                if(y!=columnas-1){
                    cout<<"\t\t| ";
                }
            }
            filasCartas++;

            for(y=0;y<columnas;y++){
                if(filasCartas<cantidadCartas[y]){
                    imprimirMas = true;
                    break;
                }else{
                    imprimirMas = false;
                }
            }
        }

        for(y=0;y<columnas;y++){
            n = 4*x+y;

            if(jugadoresStats[n].bancarrota==false){
                if(y==0){
                    cout<<"\nTotal: "<<jugadoresStats[n].sumaCartas;
                }else{
                    cout<<"Total: "<<jugadoresStats[n].sumaCartas;
                }
            }else if(y==0){
                cout<<"\n\t";
            }else{
                cout<<"\t";
            }
                
            if(y!=columnas-1){
                cout<<"\t| ";
            }
        }        
    }
    cout<<"\n"<<separacion;
}
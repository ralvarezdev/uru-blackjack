#include"cartas.h"
#include"clases.h"
#include"ioTerminal.h"
#include<iostream>
#include<random>
#include<string>
#include<vector>

using std::random_device; using std::uniform_int_distribution;
using std::cout; using std::cin;
using std::string;
using std::vector;

int main(){
    random_device rd; // Genera la semilla

    int x, y, m, n, carta, apuesta, dinero, sumaCartasMesa, sumaCartasJugador;
    bool r;
    vector<int> mazo;
    string titulo;

    Mesa mesaStats;
    vector<Jugador> jugadoresStats;
    Tablero tablero;

    titulo = "****** Blackjack ******\nRealizado por: blackb0x2";

    chequearMazo(mazo, tablero.cartasUsadas, tablero.numeroMazo);
    encabezado(titulo);

    cout<<"\n*** NOTA ***\nCuando se reparten las cartas, las abreviaciones de los palos son las siguientes\n"
        <<"- Corazon\t'C'\t\t- Diamante\t'D'\n- Trebol\t'T'\t\t- Picas\t\t'P'"
        <<"\n\n*** CONFIGURACION ***";
    do{
        cout<<"\nIngrese cada cuantas rondas desea que la apuesta inicial se duplique [1-3]: ";
        cin>>n;
    }while(n<1||n>3);
    tablero.duplicarApuesta = n;

    do{
        cout<<"Ingresa el numero de jugadores [1-8]: ";
        cin>>n;
    }while(n<1||n>8);
    tablero.numeroJugadores = n;

    jugadoresStats.resize(tablero.numeroJugadores);
    mesaStats.apuestas.resize(tablero.numeroJugadores);

    cout<<"Ingresa el dinero incial de cada jugador [150-10000]: ";
    cin>>n;
    if(n<150){
        n = 150;
    }else if(x>10000){
        n = 10000;
    }
    tablero.dineroInicial = n;

    for(x=0;x<tablero.numeroJugadores;x++){
        jugadoresStats[x].dinero = tablero.dineroInicial;
    }

    do{
        if(tablero.ronda!=1&&(tablero.ronda+1)%tablero.duplicarApuesta==0){
            tablero.apuestaInicial*=2;
        }else if(tablero.ronda==1){
            tablero.apuestaInicial = tablero.dineroInicial/15;
        }

        if(tablero.apuestaInicial%10!=0){
            tablero.apuestaInicial+= 10-tablero.apuestaInicial%10;
        }

        for(x=0;x<tablero.numeroJugadores;x++){
            dinero = jugadoresStats[x].dinero;

            if(dinero!=0){
                if(dinero>=tablero.apuestaInicial){
                    jugadoresStats[x].dinero -= tablero.apuestaInicial;
                    mesaStats.apuestas[x] = tablero.apuestaInicial;
                }else{
                    jugadoresStats[x].dinero = 0;
                    mesaStats.apuestas[x] = dinero;
                }
            }else{
                jugadoresStats[x].bancarrota = true;
            }
        }
        tablero.imprimirStats(titulo, mesaStats.apuestas, jugadoresStats);
        ingreseEnterParaContinuar();

        for(y=0;y<2;y++){
            uniform_int_distribution<int> dist(0,51-tablero.cartasUsadas);
            carta = revolverCarta(dist(rd), mazo, tablero.cartasUsadas, tablero.numeroMazo);

            mesaStats.cartas.push_back(carta);
            puntajeCarta(carta, mesaStats.numeroAs, mesaStats.sumaCartas, mesaStats.out);
        }

        for(x=0;x<tablero.numeroJugadores;x++){
            if(jugadoresStats[x].bancarrota==false){
                tablero.imprimirStats(titulo, mesaStats.apuestas, jugadoresStats);

                cout<<"\n\n*** Cartas del jugador "<<x+1<<" ***";
                for(y=0;y<2;y++){
                    uniform_int_distribution<int> dist(0,51-tablero.cartasUsadas);
                    carta = revolverCarta(dist(rd), mazo, tablero.cartasUsadas, tablero.numeroMazo);

                    jugadoresStats[x].cartas.push_back(carta);
                    puntajeCarta(carta, jugadoresStats[x].numeroAs, jugadoresStats[x].sumaCartas, jugadoresStats[x].out);

                    if(tablero.numeroJugadores!=1){
                        imprimirCarta(true, carta);
                        if(y==1){
                            cout<<"\nTotal: "<<jugadoresStats[x].sumaCartas;
                            ingreseEnterParaContinuar();
                        }
                    }
                }
            }
        }

        do{
            y = 0;
            for(x=0;x<tablero.numeroJugadores;x++){
                if(jugadoresStats[x].bancarrota==false&&jugadoresStats[x].stand==false&&jugadoresStats[x].out==false){
                    tablero.imprimirStats(titulo, mesaStats.apuestas, jugadoresStats);

                    cout<<"\n\n*** Mesa ***";
                    imprimirCarta(true, mesaStats.cartas[0]);
                    cout<<"\n- ??";

                    tablero.imprimirCartas(x, jugadoresStats[x].cartas, jugadoresStats[x].sumaCartas);
                    cout<<"\n\n";

                    r = seleccionSimple("Desea retirarse?");
                    if(r==true){
                        jugadoresStats[x].out = true;
                    }else{
                        if(jugadoresStats[x].cartas.size()==2&&jugadoresStats[x].dinero>=mesaStats.apuestas[x]){
                            r = seleccionSimple("Desea aumentar la apuesta?");
                            if(r==true){
                                apuesta = mesaStats.apuestas[x];
                                dinero = jugadoresStats[x].dinero;

                                do{
                                    cout<<"\nPuede aumentar su apuesta el doble o un monto mayor\n- Cuanto desea aumentar la apuesta: ";
                                    cin>>n;
                                }while(n<apuesta||n>dinero);

                                cout<<"\n";
                                mesaStats.apuestas[x] += n;
                                jugadoresStats[x].dinero -= n;
                            }
                        }

                        r = seleccionSimple("Desea agarrar mas cartas?");
                        if(r==false){
                            jugadoresStats[x].stand = true;
                        }else{
                            uniform_int_distribution<int> dist(0,51-tablero.cartasUsadas);
                            carta = revolverCarta(dist(rd), mazo, tablero.cartasUsadas, tablero.numeroMazo);

                            imprimirCarta(true, carta);
                            jugadoresStats[x].cartas.push_back(carta);
                            puntajeCarta(carta, jugadoresStats[x].numeroAs, jugadoresStats[x].sumaCartas, jugadoresStats[x].out);
                            cout<<"\nTotal: "<<jugadoresStats[x].sumaCartas;

                            cin.ignore();
                            ingreseEnterParaContinuar();
                        }
                    }
                }else{
                    y++;
                }
            }

            if(y==tablero.numeroJugadores){
                tablero.imprimirStats(titulo, mesaStats.apuestas, jugadoresStats);
                cout<<"\n\nTodos los jugadores estan listos para mostrar sus cartas...";
                ingreseEnterParaContinuar();
                break;
            }
        }while(true);

        while(mesaStats.sumaCartas<17){
            uniform_int_distribution<int> dist(0,51-tablero.cartasUsadas);
            carta = revolverCarta(dist(rd), mazo, tablero.cartasUsadas, tablero.numeroMazo);

            mesaStats.cartas.push_back(carta);
            puntajeCarta(carta, mesaStats.numeroAs, mesaStats.sumaCartas, mesaStats.out);
        }

        m = mesaStats.cartas.size();
        sumaCartasMesa = mesaStats.sumaCartas;
        for(x=0;x<tablero.numeroJugadores;x++){
            if(jugadoresStats[x].bancarrota==false){
                n = jugadoresStats[x].cartas.size();                
                sumaCartasJugador = jugadoresStats[x].sumaCartas;
            
                if(jugadoresStats[x].out==true){
                    jugadoresStats[x].ganador = false;
                }else if(mesaStats.out==true||sumaCartasJugador>sumaCartasMesa||(sumaCartasJugador==sumaCartasMesa&&n<m)){
                    jugadoresStats[x].ganador = true;       
                }else{
                    jugadoresStats[x].ganador = false;
                    if(sumaCartasJugador==sumaCartasMesa&&n==m){
                        jugadoresStats[x].empate = true;
                    }
                }

                if(jugadoresStats[x].ganador==true){
                    jugadoresStats[x].dinero += 2*mesaStats.apuestas[x];
                }else if(jugadoresStats[x].empate==true){
                    jugadoresStats[x].dinero += mesaStats.apuestas[x];
                }
                mesaStats.apuestas[x] = 0;
            }
        }
        tablero.imprimirStats(titulo, mesaStats.apuestas, jugadoresStats);

        cout<<"\n\n*** Mesa ***";
        for(x=0;x<mesaStats.cartas.size();x++){
            imprimirCarta(true, mesaStats.cartas[x]);
        }
        cout<<"\nTotal: "<<mesaStats.sumaCartas<<"\n";
        
        tablero.imprimirTablero(jugadoresStats);
        ingreseEnterParaContinuar();

        tablero.imprimirStats(titulo, mesaStats.apuestas, jugadoresStats);
        cout<<"\n\nRonda culminada: Analizando jugadores que quedaron en bancarrota...";
        ingreseEnterParaContinuar();

        n = 0;
        for(x=0;x<tablero.numeroJugadores;x++){
            jugadoresStats[x].reiniciarDatos();

            if(jugadoresStats[x].dinero==0){
                n++;
            }
        }
        mesaStats.reiniciarDatos();
        
        if(n==tablero.numeroJugadores){
            break;
        }else{
            tablero.ronda++;
        }
    }while(true);

    for(x=0;x<tablero.numeroJugadores;x++){
        jugadoresStats[x].bancarrota = true;
    }

    tablero.imprimirStats(titulo, mesaStats.apuestas, jugadoresStats);
    ingreseEnterParaContinuar();
    limpiarTerminal();
    cout<<"Todos los jugadores quedaron en bancarrota...\n";
    mensajeFinal("LA CASA SIEMPRE GANA");
    ingreseEnterParaContinuar();
}
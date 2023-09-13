#include<iostream>
#include<string>

using std::cout; using std::cin;
using std::string;

void ingreseEnterParaContinuar(){
    cout<<"\n\nPresione 'Enter' para Continuar: ";
    cin.get();
}

bool seleccionSimple(string mensaje){ // Funcion para permitir que el usuario seleccione entre dos opciones
    string entrada;
    char c;

    do{
        cout<<mensaje<<" [y/N]: ";
        cin>>entrada;
        c = tolower(entrada[0]);

        if(c=='y'){
            return true;
        }else if(c=='n'){
            return false;
        }
    }while(true);
}

void limpiarTerminal(){ // Limpia el terminal, e imprime un encabezado
    #ifdef _WIN32 // Para Windows
        system("cls");
    #else // Para Linux
        system("clear");
    #endif
}

void encabezado(string titulo){
    limpiarTerminal();
    cout<<titulo<<"\n";
}
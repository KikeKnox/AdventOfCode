#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>

using std::string;
using std::cout;

bool bajoLimites(string lin, string colorBuscado, uint8_t maximo){
    std::size_t encont;
    string digitos;

    encont = lin.find(colorBuscado);
    while(encont!=string::npos){
        digitos = "";
        if(isdigit(lin[encont-4])) digitos += lin[encont-4];
        if(isdigit(lin[encont-3])) digitos += lin[encont-3];
        digitos += lin[encont-2];
        if(stoi(digitos)>maximo) return false;
        encont = lin.find(colorBuscado,encont+1);
    }

    return true;
}

uint8_t max(string lin,string color){
    uint8_t maximo{0};
    std::size_t encont;
    string digitos;

    encont = lin.find(color);
    while(encont!=string::npos){
        digitos = "";
        if(isdigit(lin[encont-4])) digitos += lin[encont-4];
        if(isdigit(lin[encont-3])) digitos += lin[encont-3];
        digitos += lin[encont-2];

        if(stoi(digitos)>maximo) maximo = stoi(digitos);
        encont = lin.find(color,encont+1);
    }
    return maximo; 
}

int main(){
    string linea;
    uint32_t potencias{0};
    uint8_t rojo{0};
    uint8_t verde{0};
    uint8_t azul{0};
    uint32_t validos{0};
    uint8_t i{1};
    bool flgRed{false};
    bool flgGre{false};
    bool flgBlu{false};

    const uint8_t M_RED{12};
    const uint8_t M_GRE{13};
    const uint8_t M_BLU{14};

    std::ifstream entrada("input.txt");
    while(std::getline(entrada, linea)){
        rojo = 0;
        verde = 0;
        azul = 0;
        flgRed = false;
        flgGre = false;
        flgBlu = false;

        flgRed = bajoLimites(linea,"red",M_RED);
        if(flgRed) flgGre = bajoLimites(linea,"green",M_GRE);
        if(flgRed && flgGre) flgBlu = bajoLimites(linea,"blue",M_BLU);
        if(flgBlu && flgGre && flgRed) validos += i;
        i++;
        rojo = max(linea,"red");
        if(0 < rojo) verde = max(linea,"green");
        if(0 < rojo && 0 < verde) azul = max(linea,"blue");
        potencias += rojo * verde * azul;
    }

    cout<<"Sumatorio de juegos validos: " <<validos<<"\n";
    cout<<"Sumatorio de potencias: " <<potencias<<"\n";
    return 0;
}
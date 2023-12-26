#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::string;
using std::cout;
using std::vector;




int main(){
    std::ifstream entrada("input.txt");
    string linea, instrucciones, mapaActual;
    std::unordered_map<string, vector<string>> mapa;
    uint16_t inst{0}, pasos{0};
    uint64_t mcm{0}, i{1};
    vector<string> mapaP2;
    vector<uint16_t> pasosP2;
    bool flgPrimeraLinea{true}, flgDerecha, flgAcabaZ{true};

    while(getline(entrada, linea)){
        if(flgPrimeraLinea){
            instrucciones = linea;
            flgPrimeraLinea = false;
        }else if(linea.empty()) continue;
        
        mapa[linea.substr(0,3)] = {linea.substr(7,3),linea.substr(12,3)};
        if('A' == linea[2]) mapaP2.push_back(linea.substr(0,3));
    }
    mapaActual = "AAA";
    while(mapaActual != "ZZZ"){
        if(instrucciones.size() == inst) inst = 0;
        flgDerecha = instrucciones[inst] == 'R';
        mapaActual = mapa[mapaActual][flgDerecha];
        pasos++;
        inst++;
    }
    cout<<"Pasos necesarios para ZZZ: "<<pasos<<"\n";
    for(string &mp : mapaP2){
        pasos = 0;
        inst = 0;
        mapaActual = mp;
        while(mapaActual[2] != 'Z'){
            if(instrucciones.size() == inst) inst = 0;
            flgDerecha = instrucciones[inst] == 'R';
            mapaActual = mapa[mapaActual][flgDerecha];
            pasos++;
            inst++;
        }
        pasosP2.push_back(pasos);
    }
    while(flgAcabaZ){
        flgAcabaZ = true;
        
    }
    cout<<"Pasos necesarios para todos Z: "<<mcm<<"\n";

    return 0;
}
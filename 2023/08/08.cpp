#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <vector>
#include <unordered_map>

using std::string;
using std::cout;
using std::vector;

int main(){
    std::ifstream entrada("input.txt");
    string linea, instrucciones, mapaActual;
    std::unordered_map<string, vector<string>> mapa;
    uint8_t idMaximo{0};
    uint16_t inst{0}, maximo{0};
    uint64_t pasos{0};
    vector<string> mapaP2;
    vector<uint16_t> pasZ;
    
    bool flgPrimeraLinea{true}, flgDerecha, flgAcabaZ{false};

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
    
    for(string &s : mapaP2){
        pasos = 0;
        inst = 0;

        while(s[2] != 'Z'){
            if(instrucciones.size() == inst) inst = 0;
            flgDerecha = instrucciones[inst] == 'R';
            s = mapa[s][flgDerecha];
            pasos++;
            inst++;
        }
        pasZ.push_back(pasos);
        if(maximo < pasos){
            maximo = pasos;
            idMaximo = pasZ.size()-1;
        }
    }
    
    for(uint64_t n{1}; n < UINT64_MAX && !flgAcabaZ; n++){
        pasos = pasZ[idMaximo] * n;
        flgAcabaZ = true;
        for(uint16_t pas : pasZ){
            if(pasos % pas != 0){
                flgAcabaZ = false;
                break;
            }
        }
    }
    cout<<"Pasos necesarios para todos Z: "<<pasos<<"\n";

    return 0;
}
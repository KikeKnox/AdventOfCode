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
    std::ofstream salida("output.txt");
    string linea, instrucciones, mapaActual;
    std::unordered_map<string, vector<string>> mapa;
    uint16_t inst{0};
    uint64_t pasos{0};
    vector<string> mapaP2;
    //vector<uint16_t> pasZ;
    bool flgPrimeraLinea{true}, flgDerecha, flgAcabaZ{false};

    while(getline(entrada, linea)){
        if(flgPrimeraLinea){
            instrucciones = linea;
            flgPrimeraLinea = false;
        }else if(linea.empty()) continue;
        
        mapa[linea.substr(0,3)] = {linea.substr(7,3),linea.substr(12,3)};
        if('A' == linea[2]) mapaP2.push_back(linea.substr(0,3));
    }
    mapaActual = mapaP2[0];
    do{
        if(instrucciones.size() == inst) inst = 0;
        flgDerecha = instrucciones[inst] == 'R';
        mapaActual = mapa[mapaActual][flgDerecha];
        pasos++;
        inst++;
        if(mapaActual[2] == 'Z' || mapaActual[2] == 'A'){
            salida<<pasos<<" -> "<<mapaActual<<"\n";
        }
    }while(mapaActual != mapaP2[0] && UINT64_MAX != pasos);

    cout<<"Pasos necesarios para ZZZ: "<<pasos<<"\n";
    // pasos = 0;
    // inst = 0;
    // while(!flgAcabaZ && UINT64_MAX != pasos){
    //     flgAcabaZ = true;
    //     if(instrucciones.size() == inst) inst = 0;
    //     flgDerecha = instrucciones[inst] == 'R';
    //     for(string &mp : mapaP2){
    //         mp = mapa[mp][flgDerecha];
    //         if(mp[2] != 'Z') flgAcabaZ = false;
    //     }
    //     pasos++;
    //     inst++;
    // }
    // cout<<"Pasos necesarios para todos Z: "<<pasos<<"\n";

    return 0;
}
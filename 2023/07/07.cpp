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

bool flgPrimeraParte{true};

void ordenar(vector<string> &cartas){
    std::sort(cartas.begin(), cartas.end(), [](string a, string b) {
        uint8_t posA{0}, posB{0};
        string diccionario = "AKQJT98765432";
        diccionario = flgPrimeraParte ? "AKQJT98765432" : "AKQT98765432J";
        for(uint8_t i{0}; i < 5; i++){
            posA = diccionario.find(a[i]);
            posB = diccionario.find(b[i]);
            if(posA != posB)return posA < posB;
        }
        return false;
    });
}

void primeraParte(vector<string> &cartas){
    vector<string> combinaciones[7]={{},{},{},{},{},{},{}};
    vector<uint8_t> cantidad={0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint16_t pos{0};
    vector<uint8_t> max={0,0};
    string diccionario = "AKQJT98765432";

    diccionario = flgPrimeraParte ? "AKQJT98765432" : "AKQT98765432J";

    for(string &mano : cartas){
        for(char &c : mano) cantidad[diccionario.find(c)]++;
        if(flgPrimeraParte){
            for(uint8_t u : cantidad){
                if(u >= max[0]){
                    max[1] = max[0];
                    max[0] = u;
                }else if(u > max[1]) max[1] = u;
            }
        }else{
            for(uint8_t u{0}; u < cantidad.size()-1; u++){
                if(cantidad[u] >= max[0]){
                    max[1] = max[0];
                    max[0] = cantidad[u];
                }else if(cantidad[u] > max[1]) max[1] = cantidad[u];
            }
            if(0 < cantidad[12]) max[0] += cantidad[12];
        }
        switch(max[0]){
            case 5:
                pos = 0;
                break;
            case 4:
                pos = 1;
                break;
            case 3:
                if(2 == max[1]) pos = 2;
                else pos = 3;
                break;
            case 2:
                if(2 == max[1]) pos = 4;
                else pos = 5;
                break;
            case 1:
                pos = 6;
                break;
        }
        combinaciones[pos].push_back(mano);
        cantidad = {0,0,0,0,0,0,0,0,0,0,0,0,0};
        max = {0,0};
    }
    for(uint8_t i{0}; i < 7; i++){
        ordenar(combinaciones[i]);
    }
    pos = 0;
    while(cartas.size() > pos){
        for(uint8_t i{0}; i < 7; i++){
            for(string &mano : combinaciones[i]){
                cartas[pos] = mano;
                pos++;
            }
        }
    }

}

int main(){
    std::ifstream entrada("input.txt");
    std::ofstream salida("output.txt");
    string linea, strDigitos;
    vector<string> cartas, ordenadas;
    std::unordered_map<string, uint16_t> apuesta;
    uint64_t total{0};


    while(getline(entrada, linea)){
        cartas.push_back(linea.substr(0, 5));
        for(uint8_t i{6}; i < linea.size(); i++){
            if(isdigit(linea[i])){
                strDigitos.push_back(linea[i]);
            }
        }
        apuesta[linea.substr(0, 5)] = stoi(strDigitos);
        strDigitos.clear();
    }
    ordenadas = cartas;
    primeraParte(ordenadas);

    for(uint16_t i{0}; i < cartas.size(); i++){
        total += apuesta[ordenadas[i]] * (cartas.size() - i);
    }
    
    cout << "Primera parte: " << total << "\n";
    return 0;
}
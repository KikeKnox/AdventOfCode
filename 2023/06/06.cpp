#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <vector>
#include <cmath>

using std::string;
using std::cout;
using std::vector;

uint32_t partePrimera(const vector<uint16_t> &tiempos, const vector<uint16_t> &distancias){
    uint32_t posibilidades{1};
    uint16_t inferior{0}, superior{0};

    for(uint8_t i{0}; i < tiempos.size(); i++){

        inferior = std::ceil((tiempos[i] - std::sqrt(tiempos[i]*tiempos[i] - 4 * distancias[i])) / 2);
        if(distancias[i] == inferior*(tiempos[i] - inferior)) inferior++;
        superior = (tiempos[i] + std::sqrt(tiempos[i]*tiempos[i] - 4 * distancias[i])) / 2;
        if(distancias[i] == superior*(tiempos[i] - superior)) superior--;
        posibilidades *= (superior - inferior) + 1;
    }
    return posibilidades;
}

uint64_t parteSegunda(const uint64_t &tiempos, const uint64_t &distancias){
    uint64_t posibilidades{1};
    uint64_t inferior{0}, superior{0};

    inferior = std::ceil((tiempos - std::sqrt(tiempos*tiempos - 4 * distancias)) / 2);
    if(distancias == inferior*(tiempos - inferior)) inferior++;
    superior = (tiempos + std::sqrt(tiempos*tiempos - 4 * distancias)) / 2;
    if(distancias == superior*(tiempos - superior)) superior--;
    posibilidades *= (superior - inferior) + 1;
    return posibilidades;
}

int main(){
    string linea, strDigito1, strDigito2;
    vector<uint16_t> tiempos1, distancias1;
    vector<uint16_t>* apuntador{&tiempos1};
    uint64_t tiempos2{0}, distancias2{0};
    uint64_t* apuntador2;
    std::ifstream entrada("input.txt");

    while(getline(entrada, linea)){
        if('T' == linea[0]){
            apuntador = &tiempos1;
            apuntador2 = &tiempos2;
        }else{
            apuntador = &distancias1;
            apuntador2 = &distancias2;
        }
        for(char c : linea){
            if(!isdigit(c) && ' ' != c) continue;
            if(isdigit(c)){
                strDigito1.push_back(c);
                strDigito2.push_back(c);
            }else if(' ' == c && !strDigito1.empty()){
                (*apuntador).push_back(stoi(strDigito1));
                strDigito1.clear();
            }else continue;
        }
        (*apuntador).push_back(stoi(strDigito1));
        strDigito1.clear();
        (*apuntador2) += stoll(strDigito2);
        strDigito2.clear();
    }
    cout <<"Primera parte: " << partePrimera(tiempos1, distancias1) << '\n';
    cout <<"Segunda parte: " << parteSegunda(tiempos2, distancias2) << '\n';

    return 0;
}
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
    string linea, num;
    int32_t dif{0};
    uint64_t sumP1{0};
    int64_t sumP2{0};
    vector<int32_t> numLinea;
    vector<vector<int32_t>> numeros;
    bool flgZero{false};

    while(getline(entrada, linea)){
        numLinea.clear();
        numeros.clear();
        num.clear();
        flgZero = false;

        for(char c : linea){
            if(c == ' '){
                numLinea.push_back(stol(num));
                num.clear();
            }else{
                num += c;
            }
        }
        numLinea.push_back(stol(num));
        numeros.push_back(numLinea);

        while(!flgZero && numLinea.size() > 1){
            numLinea.clear();
            flgZero = true;
            for(uint8_t n{0}; n < numeros[numeros.size() - 1].size() - 1; n++){
                dif = numeros[numeros.size() - 1][n + 1] - numeros[numeros.size() - 1][n];
                numLinea.push_back(dif);
                if(0 != dif) flgZero = false;
            }
            numeros.push_back(numLinea);
        }

        numeros[numeros.size() - 1].push_back(0);
        numeros[numeros.size() - 1].insert(numeros[numeros.size() - 1].begin(), 0);
        for(int8_t n{numeros.size() - 2}; n >= 0; n--){
            numeros[n].insert(numeros[n].begin(), numeros[n][0] - numeros[n + 1][0]);
            numeros[n].push_back(numeros[n][numeros[n].size() - 1] + numeros[n + 1][numeros[n].size() - 1]);
        }
        sumP1 += numeros[0][numeros[0].size() - 1];
        sumP2 += numeros[0][0];
    }

    cout <<"Suma de los numeros extrapolados al final: " << sumP1 << '\n';
    cout <<"Suma de los numeros extrapolados al inicio: " << sumP2 << '\n';

    return 0;
}
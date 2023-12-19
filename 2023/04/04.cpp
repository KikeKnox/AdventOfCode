#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>

using std::string;
using std::cout;

#define TAM 216

void separaLinea(string &linea, string (&izq)[10], string (&der)[25]){
    bool esSeparador{false};
    string digitos{""};
    uint8_t j{0};

    for(uint8_t i = 10; i < linea.length(); i++){
        if('|'==linea[i]){
            esSeparador = true;
            i++;
            j = 0;
        }
        if(digitos.empty() && !isdigit(linea[i]))continue;
        else if(isdigit(linea[i]))digitos.push_back(linea[i]);
        else{
            if(esSeparador){
                der[j++] = digitos;
            }else{
                izq[j++] = digitos;
            }
            digitos = "";
        }
    }
    if(!digitos.empty())der[j++] = digitos;
}

int expo(int base, int expon){
    int result{1};
    for(int i = 0; i < expon; i++) result *= base;
    return result;
}

int main(){
    string linea, izq[10], der[25];
    int sumatorioP1{0}, sumatorioP2{0}, multi[TAM];
    uint8_t i{0}, j{0}, n{0};

    for(int ones = 0; ones < TAM; ones++)multi[ones] = 1;

    std::ifstream entrada("input.txt");
    while(std::getline(entrada, linea)){
        separaLinea(linea, izq, der);
        i = 0;
        for(string num : izq){
            j = 0;
            while(j<25){
                if(der[j] == num){
                    i++;
                    break;
                }
                j++;
            }
        }
        if(0 != i) sumatorioP1 += expo(2,i-1);
        for(i; 0 < i; i--){
            if(TAM <= n + i) continue;
            multi[n+i] += multi[n];
        }
        sumatorioP2 += multi[n];
        n++;
    }
    cout<<"Solucion de primera parte: "<<sumatorioP1<<"\n";
    cout<<"Solucion de segunda parte parte: "<<sumatorioP2<<"\n";
    return 0;
}
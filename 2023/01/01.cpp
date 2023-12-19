#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

int main(){
    std::string linea, copia;
    std::string digitos{""};
    uint64_t sumatorio{0};
    std::string numer[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::size_t encont;

    std::ifstream entrada("input.txt");
    while(std::getline(entrada, linea)){
        copia = linea;
        /********PARTE DOS*******************/
        for(int i = 0; i < 9; i++){
            encont = linea.find(numer[i]);
            while(encont!=std::string::npos){
                copia.replace(encont+1, 1, std::to_string(i+1));
                encont = linea.find(numer[i], encont+1);
            }
        }
        /***********************************/
        for(char n : copia){
            if(isdigit(n)){
                digitos += n;
                break;
            }
        }
        for(auto ch = copia.rbegin(); ch != copia.rend(); ch++){
            if(isdigit(*ch)){
                digitos += *ch;
                break;
            }
        }
        sumatorio += stoi(digitos);
        digitos="";
    }

    std::cout<<"Sumatorio total: "<<sumatorio<<"\n";
    return 0;
}
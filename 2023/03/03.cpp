#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>

using std::string;
using std::cout;

struct analizar{
    string superior;
    string medio;
    string inferior;
};

void primeraParte(uint8_t &idx, uint32_t &sumatorio, analizar &lectura){
    uint8_t cola = idx,st,fn;
    bool flgSp{false},flgMd{false},flgIn{false};
    string digitos{""};
    
    while(isdigit(lectura.medio[cola])){
        digitos.push_back(lectura.medio[cola]);
        cola++;
    }
    0 >= idx ? st = 0 : st = idx-1;
    lectura.medio.length()-1 <= cola ? fn = lectura.medio.length()-1 : fn = cola;

    for(uint8_t n = st; n<=fn; n++){
        ""==lectura.superior ? flgSp = false : flgSp = !isdigit(lectura.superior[n]) && '.' != lectura.superior[n];
        flgMd = !isdigit(lectura.medio[n]) && '.' != lectura.medio[n];
        lectura.medio==lectura.inferior ? flgIn = false : flgIn = !isdigit(lectura.inferior[n]) && '.' != lectura.inferior[n];
        if(flgIn || flgMd || flgSp){
            sumatorio += stoi(digitos);
        }
    }
    idx = cola-1;
}

void segundaParte(uint8_t &idx, uint32_t &sumatorio, analizar &lectura, uint8_t numLinea,std::ofstream &sal){
    uint8_t st,fn,st1,st2,n;
    bool flgColumnas{false},flgFilas{false},flgDigito{false};
    string digitos{""}, digitos2{""};
    bool comprobacion[3][3]={{false,false,false},{false,false,false},{false,false,false}};
    string imp[4]={"\n","\n","\n\n","/////////////////////////////////////////////////////////////////\n\n"};
    
    0 >= idx-1 ? st = 0 : st = idx-1;
    lectura.medio.length()-1 <= idx+1 ? fn = lectura.medio.length()-1 : fn = idx+1;
    
    for(n = st-idx+1; n <= fn-idx+1;n++){
        ""==lectura.superior ? comprobacion[0][n] = false : comprobacion[0][n] = isdigit(lectura.superior[st+n]);
        comprobacion[1][n] = isdigit(lectura.medio[st+n]);
        lectura.medio==lectura.inferior ? comprobacion[2][n] = false : comprobacion[2][n] = isdigit(lectura.inferior[st+n]);
    }
    flgColumnas = 2 <= (int(comprobacion[0][0] || comprobacion[0][1] || comprobacion[0][2])+int(comprobacion[1][0] || comprobacion[1][2])+int(comprobacion[2][0] || comprobacion[2][1] || comprobacion[2][2]));
    flgFilas = st == idx || fn ==idx ? false : (comprobacion[0][0] && !comprobacion[0][1] && comprobacion[0][2]) || (comprobacion[1][0] && comprobacion[1][2]) || (comprobacion[2][0] && !comprobacion[2][1] && comprobacion[2][2]); 
    if(flgColumnas){
        if(comprobacion[0][0] || comprobacion[0][1] || comprobacion[0][2]){
            n=0;
            flgDigito=false;
            while(!flgDigito || isdigit(lectura.superior[idx+1-n])){
                if(isdigit(lectura.superior[idx+1-n])) flgDigito = true;
                n++;
            }
            st1 = 0>=idx+2-n ? 0 : idx+2-n;
            for(n=0;2>=n && st1+n<lectura.superior.length();n++) if(isdigit(lectura.superior[st1+n])) digitos.push_back(lectura.superior[st1+n]);
        }
        if(comprobacion[1][0] || comprobacion[1][2]){
            n=0;
            flgDigito=false;
            while(!flgDigito || isdigit(lectura.medio[idx+1-n])){
                if(isdigit(lectura.medio[idx+1-n])) flgDigito = true;
                n++;
            }
            if(""==digitos){
                st1 = 0>=idx+2-n ? 0 : idx+2-n;
                for(n=0;2>=n && st1+n<lectura.medio.length();n++) if(isdigit(lectura.medio[st1+n])) digitos.push_back(lectura.medio[st1+n]);
            }else{
                st2 = 0>=idx+2-n ? 0 : idx+2-n;
                for(n=0;2>=n && st2+n<lectura.medio.length();n++) if(isdigit(lectura.medio[st2+n])) digitos2.push_back(lectura.medio[st2+n]);
            }
        }
        if(""==digitos2){
            n=0;
            flgDigito=false;
            while(!flgDigito || isdigit(lectura.inferior[idx+1-n])){
                if(isdigit(lectura.inferior[idx+1-n])) flgDigito = true;
                n++;
            }
            st2 = 0>=idx+2-n ? 0 : idx+2-n;
            for(n=0;2>=n && st2+n<lectura.inferior.length();n++) if(isdigit(lectura.inferior[st2+n])) digitos2.push_back(lectura.inferior[st2+n]);
        }
    }else if(flgFilas){
        n=1;
        st1=idx-n;
        st2=idx+n;
        if(comprobacion[0][0]){
            while(3>=n){
                if(isdigit(lectura.superior[st1]))digitos.insert(digitos.begin(),lectura.superior[st1]);
                if(isdigit(lectura.superior[st2]))digitos2.push_back(lectura.superior[st2]);
                n++;
            }
        }else if(comprobacion[1][0]){
            while(3>=n){
                if(isdigit(lectura.medio[st1]))digitos.insert(digitos.begin(),lectura.medio[st1]);
                if(isdigit(lectura.medio[st2]))digitos2.push_back(lectura.medio[st2]);
                n++;
            }
        }else{
            while(3>=n){
                if(isdigit(lectura.inferior[st1]))digitos.insert(digitos.begin(),lectura.inferior[st1]);
                if(isdigit(lectura.inferior[st2]))digitos2.push_back(lectura.inferior[st2]);
                n++;
            }
        } 
    }else return;

    for(n = fn-idx+1; n >= st-idx+1 && n<lectura.medio.length();n--){
        imp[0].insert(imp[0].begin(),lectura.superior[st+n]);
        imp[1].insert(imp[1].begin(),lectura.medio[st+n]);
        imp[2].insert(imp[2].begin(),lectura.inferior[st+n]);
    }
    for(n=0;n<4;n++){
        sal<<imp[n];
    }

    sumatorio += stoi(digitos) * stoi(digitos2);
}

int main(){
    analizar lectura;
    string superior{""}, medio{""},inferior,digitos,digitos2;
    uint8_t idx{0};
    uint32_t sumatorio{0},sumatorioP2{0};
    
    std::ifstream entrada("input.txt");
    std::ofstream sal("output.txt");
    uint8_t li{0};
    while(std::getline(entrada, lectura.inferior)){
        if(""==lectura.medio){
            lectura.superior = lectura.medio;
            lectura.medio = lectura.inferior;
            continue;
        }
        li++;
        for(idx = 0; lectura.medio.length() > idx; idx++){
            if(isdigit(lectura.medio[idx])){
                primeraParte(idx, sumatorio, lectura);
            }else if('*'==lectura.medio[idx]){
                segundaParte(idx,sumatorioP2, lectura,li,sal);
            }else continue;
            
        }
        lectura.superior = lectura.medio;
        lectura.medio = lectura.inferior;
    }
    li++;
    for(idx = 0; lectura.medio.length() > idx; idx++){
        if(isdigit(lectura.medio[idx])){
            primeraParte(idx, sumatorio, lectura);
        }else if('*'==lectura.medio[idx]){
            segundaParte(idx,sumatorioP2, lectura,li,sal);
        }else continue;
    }
    cout<<"Sumatorio de digitos: "<<sumatorio<<"\n";
    cout<<"Sumatorio de potencias: "<<sumatorioP2<<"\n";
    return 0;
}
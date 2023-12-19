#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include <unordered_map>
#include <vector>


using std::string;
using std::cout;
using std::unordered_map;
using std::vector;


void construirMapas(vector<uint64_t> &sd,unordered_map<uint8_t, vector<uint64_t>> &sd2sl, unordered_map<uint8_t, vector<uint64_t>> &sl2ft, unordered_map<uint8_t, vector<uint64_t>> &ft2wt, unordered_map<uint8_t, vector<uint64_t>> &wt2lt, unordered_map<uint8_t, vector<uint64_t>> &lt2tp, unordered_map<uint8_t, vector<uint64_t>> &tp2hm, unordered_map<uint8_t, vector<uint64_t>> &hm2lc){
    std::ifstream entrada("input.txt");
    string linea, val[3];
    uint8_t seccion{0}, i{0}, j{0};

    while(std::getline(entrada,linea)){
        if(isdigit(linea[0])){
            i = 0;
            for(char c : linea){
                if(' ' != c)val[i].push_back(c);
                else i++;
            }
            
            switch (seccion){
                case 1:
                    sd2sl[j].push_back(stoll(val[0]));
                    sd2sl[j].push_back(stoll(val[1]));
                    sd2sl[j].push_back(stoll(val[2]));
                    break;
                case 2:
                    sl2ft[j].push_back(stoll(val[0]));
                    sl2ft[j].push_back(stoll(val[1]));
                    sl2ft[j].push_back(stoll(val[2]));
                    break;
                case 3:
                    ft2wt[j].push_back(stoll(val[0]));
                    ft2wt[j].push_back(stoll(val[1]));
                    ft2wt[j].push_back(stoll(val[2]));
                    break;
                case 4:
                    wt2lt[j].push_back(stoll(val[0]));
                    wt2lt[j].push_back(stoll(val[1]));
                    wt2lt[j].push_back(stoll(val[2]));
                    break;
                case 5:
                    lt2tp[j].push_back(stoll(val[0]));
                    lt2tp[j].push_back(stoll(val[1]));
                    lt2tp[j].push_back(stoll(val[2]));
                    break;
                case 6:
                    tp2hm[j].push_back(stoll(val[0]));
                    tp2hm[j].push_back(stoll(val[1]));
                    tp2hm[j].push_back(stoll(val[2]));
                    break;
                case 7:
                    hm2lc[j].push_back(stoll(val[0]));
                    hm2lc[j].push_back(stoll(val[1]));
                    hm2lc[j].push_back(stoll(val[2]));
                    break;
                default:
                    continue;
            }
            j++;
            val[0].clear();
            val[1].clear();
            val[2].clear();
        }else{
            if("seed-to-soil map:" == linea){seccion = 1; j = 0; continue;}
            else if("soil-to-fertilizer map:" == linea) {seccion = 2; j = 0; continue;}
            else if("fertilizer-to-water map:" == linea) {seccion = 3; j = 0; continue;}
            else if("water-to-light map:" == linea) {seccion = 4; j = 0; continue;}
            else if("light-to-temperature map:" == linea) {seccion = 5; j = 0; continue;}
            else if("temperature-to-humidity map:" == linea) {seccion = 6; j = 0; continue;}
            else if("humidity-to-location map:" == linea) {seccion = 7; j = 0;continue;}
            else if(linea.empty())continue;
            else{
                for(char c : linea){
                    if(isdigit(c))val[0].push_back(c);
                    else if(' ' == c && !val[0].empty()){
                        sd.push_back(stoll(val[0]));
                        val[0].clear();
                    }else continue;
                }
                sd.push_back(stoll(val[0]));
                val[0].clear();
            }
        }
    }
}


int main(){
    uint64_t fertilizante, agua, luz, temperatura, humedad, ubicacion,minUbi{0};
    vector<uint64_t> semilla; 
    unordered_map<uint8_t, vector<uint64_t>> seed2soil,soil2fertilizer,fertilizer2water,water2light,light2temperature,temperature2humidity,humidity2location;

    construirMapas(semilla,seed2soil,soil2fertilizer,fertilizer2water,water2light,light2temperature,temperature2humidity,humidity2location);

    for(uint8_t i{0}; i < semilla.size(); i++){
        
    }

    cout<<"El valor minimo de ubicacion es: "<<minUbi<<"\n";
    
    return 0;
}
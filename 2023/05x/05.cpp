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

unordered_map<uint8_t, vector<uint64_t>> seed2soil,soil2fertilizer,fertilizer2water,water2light,light2temperature,temperature2humidity,humidity2location;

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

uint64_t minimaUbicacionP1(vector<uint64_t> &sd){
    uint64_t tierra, fertilizante, agua, luz, temperatura, humedad, ubicacion,minUbi{UINT64_MAX};
    uint8_t j{0};

    for(uint64_t i{0}; i < sd.size(); i++){
        tierra = 0;
        fertilizante = 0;
        agua = 0;
        luz = 0;
        temperatura = 0;
        humedad = 0;
        ubicacion = 0;
        for(j = 0; j < seed2soil.size(); j++){
            if(sd[i] < seed2soil[j][1] || sd[i] > seed2soil[j][2] + seed2soil[j][1])continue;
            tierra = seed2soil[j][0] + (sd[i] - seed2soil[j][1]);
        }
        if(0 == tierra && seed2soil.size() == j)tierra = sd[i];
        for(j = 0; j < soil2fertilizer.size(); j++){
            if(tierra < soil2fertilizer[j][1] || tierra > soil2fertilizer[j][2] + soil2fertilizer[j][1])continue;
            fertilizante = soil2fertilizer[j][0] + (tierra - soil2fertilizer[j][1]);
        }
        if(0 == fertilizante && soil2fertilizer.size() == j)fertilizante = tierra;
        for(j = 0; j < fertilizer2water.size(); j++){
            if(fertilizante < fertilizer2water[j][1] || fertilizante > fertilizer2water[j][2] + fertilizer2water[j][1])continue;
            agua = fertilizer2water[j][0] + (fertilizante - fertilizer2water[j][1]);
        }
        if(0 == agua && fertilizer2water.size() == j)agua = fertilizante;
        for(j = 0; j < water2light.size(); j++){
            if(agua < water2light[j][1] || agua > water2light[j][2] + water2light[j][1])continue;
            luz = water2light[j][0] + (agua - water2light[j][1]);
        }
        if(0 == luz && water2light.size() == j)luz = agua;
        for(j = 0; j < light2temperature.size(); j++){
            if(luz < light2temperature[j][1] || luz > light2temperature[j][2] + light2temperature[j][1])continue;
            temperatura = light2temperature[j][0] + (luz - light2temperature[j][1]);
        }
        if(0 == temperatura && light2temperature.size() == j)temperatura = luz;
        for(j = 0; j < temperature2humidity.size(); j++){
            if(temperatura < temperature2humidity[j][1] || temperatura > temperature2humidity[j][2] + temperature2humidity[j][1])continue;
            humedad = temperature2humidity[j][0] + (temperatura - temperature2humidity[j][1]);
        }
        if(0 == humedad && temperature2humidity.size() == j)humedad = temperatura;
        for(j = 0; j < humidity2location.size(); j++){
            if(humedad < humidity2location[j][1] || humedad > humidity2location[j][2] + humidity2location[j][1])continue;
            ubicacion = humidity2location[j][0] + (humedad - humidity2location[j][1]);
        }
        if(0 == ubicacion && humidity2location.size() == j)ubicacion = humedad;
        if(ubicacion < minUbi)minUbi = ubicacion;
    }
    return minUbi;
}

uint64_t minimaUbicacionP1(uint64_t &sd){
    uint64_t tierra, fertilizante, agua, luz, temperatura, humedad, ubicacion,minUbi{UINT64_MAX};
    uint8_t j{0};

    tierra = 0;
    fertilizante = 0;
    agua = 0;
    luz = 0;
    temperatura = 0;
    humedad = 0;
    ubicacion = 0;
    for(j = 0; j < seed2soil.size(); j++){
        if(sd < seed2soil[j][1] || sd > seed2soil[j][2] + seed2soil[j][1])continue;
        tierra = seed2soil[j][0] + (sd - seed2soil[j][1]);
    }
    if(0 == tierra && seed2soil.size() == j)tierra = sd;
    for(j = 0; j < soil2fertilizer.size(); j++){
        if(tierra < soil2fertilizer[j][1] || tierra > soil2fertilizer[j][2] + soil2fertilizer[j][1])continue;
        fertilizante = soil2fertilizer[j][0] + (tierra - soil2fertilizer[j][1]);
    }
    if(0 == fertilizante && soil2fertilizer.size() == j)fertilizante = tierra;
    for(j = 0; j < fertilizer2water.size(); j++){
        if(fertilizante < fertilizer2water[j][1] || fertilizante > fertilizer2water[j][2] + fertilizer2water[j][1])continue;
        agua = fertilizer2water[j][0] + (fertilizante - fertilizer2water[j][1]);
    }
    if(0 == agua && fertilizer2water.size() == j)agua = fertilizante;
    for(j = 0; j < water2light.size(); j++){
        if(agua < water2light[j][1] || agua > water2light[j][2] + water2light[j][1])continue;
        luz = water2light[j][0] + (agua - water2light[j][1]);
    }
    if(0 == luz && water2light.size() == j)luz = agua;
    for(j = 0; j < light2temperature.size(); j++){
        if(luz < light2temperature[j][1] || luz > light2temperature[j][2] + light2temperature[j][1])continue;
        temperatura = light2temperature[j][0] + (luz - light2temperature[j][1]);
    }
    if(0 == temperatura && light2temperature.size() == j)temperatura = luz;
    for(j = 0; j < temperature2humidity.size(); j++){
        if(temperatura < temperature2humidity[j][1] || temperatura > temperature2humidity[j][2] + temperature2humidity[j][1])continue;
        humedad = temperature2humidity[j][0] + (temperatura - temperature2humidity[j][1]);
    }
    if(0 == humedad && temperature2humidity.size() == j)humedad = temperatura;
    for(j = 0; j < humidity2location.size(); j++){
        if(humedad < humidity2location[j][1] || humedad > humidity2location[j][2] + humidity2location[j][1])continue;
        ubicacion = humidity2location[j][0] + (humedad - humidity2location[j][1]);
    }
    if(0 == ubicacion && humidity2location.size() == j)ubicacion = humedad;
    if(ubicacion < minUbi)minUbi = ubicacion;
    
    return minUbi;
}

uint64_t minimaUbicacionP2(vector<uint64_t> &sd){
    uint64_t semi{0},tierra{0}, fertilizante{0}, agua{0}, luz{0}, temperatura{0}, humedad{0},minUbi{UINT64_MAX},ultimo{0}, maxVal{UINT64_MAX}, maxUbi{0};
    uint8_t i{0}, j{0};

    for(i = 0; i < humidity2location.size(); i++){
        if(minUbi > humidity2location[i][0])minUbi = humidity2location[i][0], maxVal = humidity2location[i][2];
        if(maxUbi < humidity2location[i][0])maxUbi = humidity2location[i][0];
    }
    while(ultimo < maxUbi){
        for(i = 0; i < humidity2location.size(); i++){
            if(minUbi < humidity2location[i][0] || minUbi > humidity2location[i][2] + humidity2location[i][0])continue;
            humedad = humidity2location[i][1] + (minUbi - humidity2location[i][0]);
            if(humidity2location[i][2] + humidity2location[i][0] - minUbi < maxVal && 0 != humidity2location[i][2] + humidity2location[i][0] - minUbi)maxVal = humidity2location[i][2] + humidity2location[i][0] - minUbi;
        }
        if(0 == humedad && humidity2location.size() == i)humedad = minUbi;
        for(i = 0; i < temperature2humidity.size(); i++){
            if(humedad < temperature2humidity[i][0] || humedad > temperature2humidity[i][2] + temperature2humidity[i][0])continue;
            temperatura = temperature2humidity[i][1] + (humedad - temperature2humidity[i][0]);
            if(temperature2humidity[i][2] + temperature2humidity[i][0] - humedad < maxVal && 0 != temperature2humidity[i][2] + temperature2humidity[i][0] - humedad)maxVal = temperature2humidity[i][2] + temperature2humidity[i][0] - humedad;
        }
        if(0 == temperatura && temperature2humidity.size() == i)temperatura = humedad;
        for(i = 0; i < light2temperature.size(); i++){
            if(temperatura < light2temperature[i][0] || temperatura > light2temperature[i][2] + light2temperature[i][0])continue;
            luz = light2temperature[i][1] + (temperatura - light2temperature[i][0]);
            if(light2temperature[i][2] + light2temperature[i][0] - temperatura < maxVal && 0 != light2temperature[i][2] + light2temperature[i][0] - temperatura)maxVal = light2temperature[i][2] + light2temperature[i][0] - temperatura;
        }
        if(0 == luz && light2temperature.size() == i)luz = temperatura;
        for(i = 0; i < water2light.size(); i++){
            if(luz < water2light[i][0] || luz > water2light[i][2] + water2light[i][0])continue;
            agua = water2light[i][1] + (luz - water2light[i][0]);
            if(water2light[i][2] + water2light[i][0] - luz < maxVal && 0 != water2light[i][2] + water2light[i][0] - luz)maxVal = water2light[i][2] + water2light[i][0] - luz;
        }
        if(0 == agua && water2light.size() == i)agua = luz;
        for(i = 0; i < fertilizer2water.size(); i++){
            if(agua < fertilizer2water[i][0] || agua > fertilizer2water[i][2] + fertilizer2water[i][0])continue;
            fertilizante = fertilizer2water[i][1] + (agua - fertilizer2water[i][0]);
            if(fertilizer2water[i][2] + fertilizer2water[i][0] - agua < maxVal && 0 != fertilizer2water[i][2] + fertilizer2water[i][0] - agua)maxVal = fertilizer2water[i][2] + fertilizer2water[i][0] - agua;
        }
        if(0 == fertilizante && fertilizer2water.size() == i)fertilizante = agua;
        for(i = 0; i < soil2fertilizer.size(); i++){
            if(fertilizante < soil2fertilizer[i][0] || fertilizante > soil2fertilizer[i][2] + soil2fertilizer[i][0])continue;
            tierra = soil2fertilizer[i][1] + (fertilizante - soil2fertilizer[i][0]);
            if(soil2fertilizer[i][2] + soil2fertilizer[i][0] - fertilizante < maxVal && 0 != soil2fertilizer[i][2] + soil2fertilizer[i][0] - fertilizante)maxVal = soil2fertilizer[i][2] + soil2fertilizer[i][0] - fertilizante;
        }
        if(0 == tierra && soil2fertilizer.size() == i)tierra = fertilizante;
        for(i = 0; i < seed2soil.size(); i++){
            if(tierra < seed2soil[i][0] || tierra > seed2soil[i][2] + seed2soil[i][0])continue;
            semi = seed2soil[i][1] + (tierra - seed2soil[i][0]);
            if(seed2soil[i][2] + seed2soil[i][0] - tierra < maxVal && 0 != seed2soil[i][2] + seed2soil[i][0] - tierra)maxVal = seed2soil[i][2] + seed2soil[i][0] - tierra;
        }
        if(0 == semi && seed2soil.size() == i)semi = tierra;

        for(i = 0; i < sd.size()/2; i++){
            if(sd[2*i] < semi && sd[2*i] + sd[2*i+1] > semi){
                return minUbi;
            }
            else if(sd[2*i] < semi + maxVal && sd[2*i] + sd[2*i+1] > semi + maxVal){
                minUbi = minimaUbicacionP1(sd[2*i]); 
                return minUbi;
            }
        }
        ultimo = minUbi + maxVal;
        for(i = 0; i < humidity2location.size(); i++){
            if(ultimo < humidity2location[i][0] || ultimo > humidity2location[i][2] + humidity2location[i][0])continue;
            minUbi = humidity2location[i][0] + (ultimo - humidity2location[i][0] + 1);
        }
        maxVal = UINT64_MAX;


    }
    return 2;
}

int main(){
    vector<uint64_t> semilla;
    uint64_t ubiParte1{0}, ubiParte2{0};
    uint64_t m{0}, n{0};

    construirMapas(semilla,seed2soil,soil2fertilizer,fertilizer2water,water2light,light2temperature,temperature2humidity,humidity2location);
    ubiParte1 = minimaUbicacionP1(semilla);
    cout<<"Ubicacion parte 1: "<<ubiParte1<<"\n";
    

    ubiParte2 = minimaUbicacionP2(semilla);
    cout<<"Ubicacion parte 2: "<<ubiParte2<<"\n";
    return 0;
}
%% AdventOfCode 2023 - Dia 01

archivo = fopen("input.txt",'r');
datos = textscan(archivo,'%s');
datos = datos{1,1};

%% Primer caso
primer = char(datos);
longPrimer = length(primer);
izq = num2str(zeros(length(primer),1));
der = num2str(zeros(length(primer),1));
for n = 1:longPrimer
    linea = primer(n,:);
    longLinea = length(linea);
    for d = 1:longLinea
        if isstrprop(linea(d),"digit")
            izq(n)=linea(d);
            break
        end
    end
    for d = longLinea:-1:1
        if isstrprop(linea(d),"digit")
            der(n)=linea(d);
            break
        end
    end
end
digitosChar = strcat(izq,der);
digitos = str2num(digitosChar);

total = sum(digitos)

%% Segundo caso
primer = char(datos);
longPrimer = length(primer);
izq = num2str(zeros(length(primer),1));
der = num2str(zeros(length(primer),1));
mapa = containers.Map({'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine'}, {'1', '2', '3', '4', '5', '6', '7', '8', '9'});
keys = mapa.keys;
for n = 1:longPrimer
    linea = primer(n,:);
    copia = linea;
    longLinea = length(linea);
    for i = 1:length(keys)
        key = keys{i};
        idx = strfind(linea, key);
        if ~isempty(idx)
            for j = 1:length(idx)
                copia(idx(j)) = mapa(key);
            end
        end
    end
    for d = 1:longLinea
        if isstrprop(copia(d),"digit")
            izq(n)=copia(d);
            break
        end
    end
    for d = longLinea:-1:1
        if isstrprop(copia(d),"digit")
            der(n)=copia(d);
            break
        end
    end
end
digitosChar = strcat(izq,der);
digitos = str2num(digitosChar);

total2 = sum(digitos)
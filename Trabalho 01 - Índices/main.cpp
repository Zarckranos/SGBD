#include <iostream>
#include <fstream>
using namespace std;

#include "hashExtensivel.cpp"
#include "vinho.cpp"


int main() {
    /*string indice = "01";
    ofstream Registro("./diretorio/"+indice+".txt");
    Registro << "vinho tinto, " << 1984 << '\n';
    Registro.close();
    
    ofstream Registro2("./diretorio/01.txt");
    Registro2 << "vinho rose, " << 2000;
    Registro2.close();

    HashExtensivel::Diretorio dir;

    dir.criarDiretorio();
    cout << dir.buckets.size();*/

    //rename(("./diretorio/"+to_string(0)+".txt").c_str(), "./diretorio/000.txt");
    /*string bin = "110";
    string filename = "./diretorio/"+bin+".txt";
    HashExtensivel hash;
    remove(filename.c_str());*/

    /* fstream file1;
    file1.open("./diretorio/000.txt");

    string line;
    int ano;
    while(getline(file1, line)){
        ano = getAnoColheita(line);
        //cout << ano << "\n";
        unsigned int num = get_n_bits(3, ano);
        cout << num << "\n";
        if(num == bin_string_to_dec("100")) {
            cout << ano << "\n";
        }
    }
    file1.close();*/

    fstream file;
    file.open("./vinhos_teste.txt");
    string registro;
    int ano;

    HashExtensivel hash;
    HashExtensivel::Diretorio dir;
    dir.criarDiretorio();

    while(getline(file, registro)) {
        ano = hash.getAnoColheita(registro);
        hash.inserir(&dir, registro, ano);
    }
    file.close();

    cout << hash.remover(&dir, 1952);

    return 0;
}
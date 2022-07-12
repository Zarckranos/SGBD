#include <string>
#include <vector>
#include <iostream>

#include "historia.cpp"

// Log de n histórias
class Log {
    vector<Historia*> historias;

    public:
    void inserirHistoria(Historia* historia) {
        historias.push_back(historia);
    }

    vector<Historia*> getHistorias(){
        return historias;
    }

    int getSizeHistorias(){
        return historias.size();  
    }

    void imprimirHistorias(){
        for(auto & elem : historias){
            cout << elem->lsn << " - ";
        }
    }
}; // -------------------------------------------------------------------------
#include <string>
#include <vector>
#include <iostream>
#include <fstream>  
#include <map>

#include "log.cpp"

using namespace std;

class UNDO_NOREDO{
    map<string, int> BDstate;
    map<string, string> Tn_state;
    vector<string> ROLL;
    vector<string> UNDO;

    // Printa estado de um MAP;
    template <typename TC, typename TV>
    void print_map(map<TC, TV> const &m) {
        for (auto const &pair: m) {
            cout << ">> " << pair.first << " = " << pair.second << "\n";
        }
    }

    // Printa o estado atual do BD, usado essencialmente para fazer o arquivo de saída;
    string stateBD() {
        string aux = "";

        for (auto const &pair: BDstate) {
            aux += ">>    " + pair.first + " = " + to_string(pair.second) + "\n";
        }
        
        return aux;
    }

    // Printa o estado atual da lista UNDO, usado essencialmente para fazer o arquivo de saída;
    string showUNDO() {
        string aux = "";
        unsigned int size = UNDO.size();

        for(unsigned int i = 0; i < size; i++){
            aux += UNDO[i];
            if(i != size - 1) aux += ", ";
        }
        return aux;
    }

    // Com base nos estados das transações, adiciona ela na Lista UNDO caso seja "u",
    // ou adiciona na lista ROLL caso seja "a";
    
    // "u": transações que tem operações de 'r' ou 'w', mas não comitaram;
    // "a": transações que sofreram rollback;
    void atualizar_listas() {
        // Em desuso por conta de alterações que fizemos durante a lógica;
        for (auto const &pair: Tn_state) {
            if(pair.second == "u") {
                UNDO.push_back(pair.first);
            }
            if(pair.second == "a") {
                ROLL.push_back(pair.first);
            }
        }
    }

    // Mostra o estado da tabela ROLL
    void print_roll() {
        cout << "- ROLL: { ";
        for(unsigned int i = 0; i < ROLL.size(); i++){
            cout << ROLL[i];
            if(i + 1 < ROLL.size()) cout << ", ";
        }
        cout << " }\n";
    }

    void print_undo() {
        cout << "- UNDO: { ";
        for(unsigned int i = 0; i < UNDO.size(); i++){
            cout << UNDO[i];
            if(i + 1 < UNDO.size()) cout << ", ";
        }
        cout << " }\n";
    }

    // Verifica se uma transação já está dentro de uma lista, UNDO OR ROLL.
    bool buscarTransacao(string lista, string Tn) {
        bool state = false;
        if(lista == "UNDO") {
            for(auto & elem : UNDO){
                if(elem == Tn) {
                    state = true;
                }
            }
        } else {
            for(auto & elem : ROLL){
                if(elem == Tn) {
                    state = true;
                }
            }
        }
        
        return state;
    }

    // Remove uma transação Tn da lista UNDO.
    void removeTransacao(string Tn) {
        vector<string>::iterator ptr;

        int i = 0;
        for (ptr = UNDO.begin(); ptr < UNDO.end(); ptr++) {
            if(UNDO[i] == Tn) {
                UNDO.erase(ptr);
            }
            i++;
        }
    }

    // Faz o rollback das transações presentes na lista ROLL
    void rollback(Log* log, string Tn) {
        vector<Historia*> historias;
        historias = log->getHistorias();
        int tamanho = log->getSizeHistorias() - 1;

        for(int i = tamanho; i>=0; i--){
            if(historias[i]->operacao == "w" && historias[i]->transaction == Tn){
                BDstate[historias[i]->objeto] = historias[i]->imagem_Anterior;
            }
        }
    }

    public:
    // Operação de Análise. Extração de informações para auxilio das próximas fases.
    void analise(Log* log){
        vector<Historia*> historias;
        historias = log->getHistorias();

        for(auto & elem : historias){
            if(elem->operacao == "w" || elem->operacao == "r") {
                BDstate[elem->objeto] = elem->imagem_Posterior;
                Tn_state[elem->transaction] = "u";

                if(!buscarTransacao("UNDO", elem->transaction)) {
                    UNDO.push_back(elem->transaction);
                }
            } else{
                if(elem->operacao == "a") {
                    ROLL.push_back(elem->transaction);
                    Tn_state[elem->transaction] = elem->operacao;
                    removeTransacao(elem->transaction);
                    
                    rollback(log, elem->transaction);
                } else {
                    Tn_state[elem->transaction] = elem->operacao;

                    removeTransacao(elem->transaction);
                }
            }
        }

        cout << "------ Estado das Transacoes -------------------------\n";
        print_map(Tn_state);
        cout << "------ Estado do BD durante operacao de Analise ------\n";
        print_map(BDstate);
        cout << "\n------ Estado das listas ROLL e UNDO -----------------\n";
        print_roll();
        print_undo();
    }

    // Desfaz as transações presentes na lista UNDO
    void desfazer(Log* log){
        vector<Historia*> historias;
        historias = log->getHistorias();
        int tamanho = log->getSizeHistorias() - 1;
        unsigned int size = UNDO.size();
        ofstream outfile("out.txt");
        for(unsigned int w = 0; w < size; w++) {
            outfile << "- Passo " << w + 1 << " (" << UNDO[0] << "): estado do BD = {\n";
            for(int i = tamanho; i >= 0; i--) {
                if(historias[i]->transaction == UNDO[0]) {
                    if(historias[i]->operacao == "w"){
                        BDstate[historias[i]->objeto] = historias[i]->imagem_Anterior;
                    }
                }
            }
            removeTransacao(UNDO[0]);
            outfile << stateBD() << "}, ADesfazer = {" << showUNDO() << "}\n" ;
        }
        
        outfile.close();

        cout << "------ Estado do BD apos Operacao Desfazer -----------\n";
        print_map(BDstate);
    }
}; // -------------------------------------------------------------------------
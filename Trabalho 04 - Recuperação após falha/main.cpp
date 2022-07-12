// -----------------------------------------------------------------------------
// Universidade Federal do Ceará, Centro de Ciências, Departamento de Computação
// Disciplina: SGBD - CK0117 2022.1
// Professor: Javam de Castro Machado
// Trabalho 4
// Transações e Controle de Concorrência
// Autores: Javam, Leonardo, Daniel, Paulo, Edvar

// Nome: Matheus do Vale Almeida
// Matrícula: 473219
// Nome: Silvio Soares Carreiro
// Matrícula: 473582
// -----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include "undo_noredo.cpp"

using namespace std;

int main() {
    // ARQUIVOS DE ENTRADA =====================
    string in  = "in.txt";
    string in1 = "in1.txt";
    string in2 = "in2.txt";
    string in3 = "in3.txt";
    //===========================================

    ifstream log_file( in );

    //string auxiliar para guardar as historias
    string buffer;

    //valores da historia
    int lsn, timeTn, im_A, im_P;
    string tn, operacao, objeto;

    Log log;
    UNDO_NOREDO exe;
    // Pegar as n historias do arquivo de entrada e grava-las na classe log
    while(log_file >> buffer) {
        int delimiter1 = buffer.find('|');
        int delimiter2 = buffer.find('|', delimiter1 + 1);
        int delimiter3 = buffer.find('|', delimiter2 + 1);
        int delimiter4 = buffer.find('|', delimiter3 + 1);
        
        lsn      = stoi(buffer.substr(1, delimiter1 - 1));
        timeTn   = stoi(buffer.substr(delimiter1 + 1, delimiter2 - delimiter1 - 1));
        tn       = buffer.substr(delimiter2 + 1, delimiter3 - delimiter2 - 1);
        operacao = buffer.substr(delimiter3 + 1, delimiter4 - delimiter3 - 1);
        
        // Se a operação for de "commit" ou "rollback", a entrada não possui as próximas entradas
        if(operacao == "c" || operacao == "a") {
            Historia* hist =  new Historia(lsn, timeTn, tn, operacao);

            log.inserirHistoria(hist);
        } else {
            int delimiter5 = buffer.find('|', delimiter4 + 1);
            int delimiter6 = buffer.find('|', delimiter5 + 1);

            objeto = buffer.substr(delimiter4 + 1, 1);
            im_A   = stoi(buffer.substr(delimiter5 + 1, delimiter6 - delimiter5 - 1));
            im_P   = stoi(buffer.substr(delimiter6 + 1, buffer.size() - delimiter6 - 2));
            
            Historia* hist = new Historia(lsn, timeTn, tn, operacao, objeto, im_A, im_P);

            log.inserirHistoria(hist);
        }
    }
    
    exe.analise(&log);
    exe.desfazer(&log);
    //log.imprimirHistorias();

    log_file.close();
    return 0;
}
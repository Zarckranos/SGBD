#include <string>

using namespace std;

// -------------------------------------------------------------------------------------------------
// Estrutura de uma historia:
// LSN              - Significa o Número Sequencial de Log;
// TimeTn           - Significa o 'timestamp' da transação n;
// Operação         - Significa 'w' para operação de escrita, 'r' para operação de leitura, 'a' para
//                    operação de rollback e 'c' para operação de commit;
// Objeto           - Significa o objeto de dados alvo da operação. Quando a operação for de commit
//                    ou rollback, esse campo fica inutilizado.
// Imagem Anterior  - Significa o valor do dado antes da execução da operação. Esse campo fica
//                    inutilizado quando a opera ̧c ̃ao for de commit ou rollback.
// Imagem Posterior - Significa o valor do dado após a execução da operação. Esse campo também fica
//                    inutilizado quando a operação for de commit ou rollback.
// -------------------------------------------------------------------------------------------------
struct Historia{
    int lsn;
    int timeTn;
    string transaction;
    string operacao;
    string objeto;
    int imagem_Anterior;
    int imagem_Posterior;

    // Construtor -----------------------------------------------
    Historia(int lsn_, int timeTn_, string tn, string operacao_, string objeto_, int im_A, int im_P) {
        lsn              = lsn_;
        timeTn           = timeTn_;
        transaction      = tn;
        operacao         = operacao_;
        objeto           = objeto_;
        imagem_Anterior  = im_A;
        imagem_Posterior = im_P;
    }

    Historia(int lsn_, int timeTn_, string tn, string operacao_) {
        lsn         = lsn_;
        timeTn      = timeTn_;
        transaction = tn;
        operacao    = operacao_;

        //estamos colando em 0 os valores de im_A e im_P por convenção, em caso da operação ser 'c' ou 'a'.
        objeto           = "null";
        imagem_Anterior  = 0;
        imagem_Posterior = 0;
    }
    // ----------------------------------------------------------
};
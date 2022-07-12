#include <string>

struct Vinho {
    int vinho_id;
    string rotulo;
    int ano_colheita;
    string tipo;

    void criar(int id, string rot, int ano, string tip) {
        vinho_id = id;
        rotulo = rot;
        ano_colheita = ano;
        tipo = tip;
    }
};
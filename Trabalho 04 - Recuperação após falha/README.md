## Resumo:
O trabalho consiste em desenvolver em C++ que faça a simulação de um algoritmo de recuperação após falha, em nosso caso, **Modificação imediata do BD (técnica UNDO/NO-REDO)**. É importante notar, não foi necessário utilizar *checkpoints* nem tratar *rollbacks* em cascata por motivos de simplificação.
O programa receberá como entrada um arquivo com *n* histórias, uma história por linha. Olhe os arquivos *in.txt*, *in1.txt*, *in2.txt* e *in3.txt* para ver exemplos de entrada. 

## Compilação da Solução:
O programa foi compilado através de uma linha como:

`g++ -Wall -Wextra -std=c++17 -pedantic -o programa main.cpp`

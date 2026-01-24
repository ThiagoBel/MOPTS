#include <iostream>
#include "MOPTS.h"

void FUN1() // Function 1
{
    std::cout << "OPTION1" << std::endl;
}
void FUN2() // Function 2
{
    std::cout << "OPTION2" << std::endl;
}
void FUN3() // Function 3
{
    std::cout << "OPTION3" << std::endl;
}
void FUN4() // Function 4
{
    std::cout << "OPTION4" << std::endl;
}
// Voce pode colocar mais funcoes se quiser

int main()
{
    MOPTS::allline = true; // vai deixar a linha inteira da opção navegada com fundo branco e texto preto
    
    MOPTS::MenuOption options[] = { // Declarar opções
        {"Opcao 2", FUN2}, //opcoes
        {"Opcao 3", FUN3}, //opcoes
        {"Opcao 1", FUN1}, //opcoes
        {"Opcao 4", FUN4}  //opcoes
        //pode colocar mais se quiser
    };

    MOPTS::ShowMenu("Descricao de cima", options, "", false, true, "Descricao de baixo"); // aparecer no console
    // Primeira parte serve para mostrar um texto antes das opções
    // Segunda parte serve para colocar as opções no console
    // Terceira parte serve para mostrar o marcador, exemplo: "> OPCAO 1"
    // Quarta parte serve para ver se ele limpa as opções depois de ser usada (cls)
    // Quinta parte serve para quando a opção for selecionada ou ficar em cima, irá ficar um fundo branco na opção e texto preto na opção (Recomendado para terminais escuros)
    // Sexta parte serve para mostrar um texto depois das opções

}

#include <iostream>
#include "MOPTS.h" // biblioteca

void OPTION1(const std::string &classe) // funcao 1
{
    std::cout << classe << " selecionada" << std::endl;
}

void OPTION2(const std::string &classe) // funcao 2
{
    std::cout << classe << " selecionada" << std::endl;
}

void OPTION3(const std::string &classe) // funcao 3
{
    std::cout << classe << " selecionada" << std::endl;
}

int main()
{
    MOPTS::color = true;
    // Ativa o uso de cores na opção selecionada
    // true  = fundo branco e texto preto
    // false = sem destaque de cor
    MOPTS::all_color_line = true;
    // Define se a linha inteira da opção ficará destacada
    // true  = a linha inteira é colorida
    // false = apenas o texto da opção é colorido
    MOPTS::clear_opts = true;
    // Define se o console será limpo após selecionar uma opção
    // true  = limpa o console antes de executar a função
    // false = mantém o menu visível

    MOPTS::MenuOption opcoes[] = {
        // opcoes
        {"Opcao 1", "CLASS1", OPTION1},
        {"Opcao 2", "CLASS2", OPTION2},
        {"Opcao 3", "CLASS3", OPTION3},
    };
    // 1. "Opcao X" -> opção
    // 2. "CLASS X" -> classe (informacao que manda para funcao)
    // 3. "OPTIONX" -> funcao que executa

    MOPTS::ShowMenu("Descricao de cima", opcoes, "", "Descricao de baixo"); // mostrar no terminal

    // 1. "Descricao de cima"  -> texto exibido antes das opções (vazio = sem descricao)
    // 2. opcoes               -> lista de opções do menu
    // 3. ""                   -> marcador da opção selecionada (vazio = sem marcador)
    // 4. "Descricao de baixo" -> texto exibido após as opções (vazio = sem descricao)
    return 0;
}
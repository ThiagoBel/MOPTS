#include <iostream>
#include "MOPTS.h" // Biblioteca de menu interativo no console (APENAS WINDOWS)

void OPTION1()
{
    std::cout << "Opcao 1 selecionada" << std::endl;
}
void OPTION2()
{
    std::cout << "Opcao 2 selecionada" << std::endl;
}
void OPTION3()
{
    std::cout << "Opcao 3 selecionada" << std::endl;
}

int main()
{
    // Ativa o uso de cores na opção selecionada
    // true  = fundo branco e texto preto
    // false = sem destaque de cor
    MOPTS::color = true;

    // Define se a linha inteira da opção ficará destacada
    // true  = a linha inteira é colorida
    // false = apenas o texto da opção é colorido

    MOPTS::all_color_line = true;

    // Define se o console será limpo após selecionar uma opção
    // true  = limpa o console antes de executar a função
    // false = mantém o menu visível

    MOPTS::clear_opts = false;
    // Lista de opções do menu
    // Cada opção possui:
    // - Texto que será exibido no menu
    // - Função que será executada ao selecionar
    MOPTS::MenuOption opcoes[] = {
        {"Opcao 1", OPTION1}, // Executa OPTION1()
        {"Opcao 2", OPTION2}, // Executa OPTION2()
        {"Opcao 3", OPTION3}, // Executa OPTION3()
    };

    // Exibe o menu no console

    // 1º "Descricao de cima"  -> texto exibido antes das opções
    // 2º opcoes               -> lista de opções do menu
    // 3º ""                   -> marcador da opção selecionada (vazio = sem marcador)
    // 4º "Descricao de baixo" -> texto exibido após as opções

    MOPTS::ShowMenu("Descricao de cima", opcoes, "", "Descricao de baixo");

    return 0;
}
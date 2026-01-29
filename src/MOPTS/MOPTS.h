/*
MOPTS
>> APENAS WINDOWS <<

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


    Não precisa dar créditos, fiz no tédio
*/
#pragma once
#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

namespace MOPTS // UAU!
{
    bool all_color_line = false; // linha inteira destacada
    bool clear_opts = false;     // limpar console após escolher
    bool color = false;          // fundo branco na opção selecionada

    typedef void (*MenuFunc)(const std::string &);

    struct MenuOption
    {
        std::string texto;
        std::string classe;
        MenuFunc func;
    };

    inline void ClearConsole() // limpa o bagulho
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD count;
        DWORD cellCount;

        if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
            return;

        cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        FillConsoleOutputCharacter(hConsole, ' ', cellCount, {0, 0}, &count);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, {0, 0}, &count);
        SetConsoleCursorPosition(hConsole, {0, 0});
    }

    template <size_t N>
    inline void ShowMenu( // mostra no console as opcao q ce colocou
        const std::string &desc,
        MenuOption (&opcoes)[N],
        const std::string &marcador,
        const std::string &desc2)
    {
        int selecionado = 0;
        const int total = static_cast<int>(N);

        while (true) // wow!
        {
            ClearConsole();

            if (!desc.empty())
                std::cout << desc << std::endl;

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO info;
            GetConsoleScreenBufferInfo(hConsole, &info);

            WORD corOriginal = info.wAttributes;
            int larguraConsole = info.dwSize.X;

            for (int i = 0; i < total; i++)
            {
                bool ativo = (i == selecionado);

                if (ativo && color)
                {
                    SetConsoleTextAttribute(
                        hConsole,
                        BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE); // eita, cores
                }

                if (ativo && all_color_line)
                {
                    std::cout << std::string(larguraConsole, ' ') << "\r";
                }

                if (!marcador.empty())
                    std::cout << (ativo ? marcador : "  ");

                std::cout << opcoes[i].texto << '\n';

                if (ativo && color)
                    SetConsoleTextAttribute(hConsole, corOriginal);
            }

            if (!desc2.empty())
                std::cout << desc2 << std::endl;

            int tecla = _getch();

            if (tecla == 224)
            {
                tecla = _getch();
                if (tecla == 72)
                    selecionado = (selecionado - 1 + total) % total;
                else if (tecla == 80)
                    selecionado = (selecionado + 1) % total;
            }
            else if (tecla == 'w' || tecla == 'W') // wow
            {
                selecionado = (selecionado - 1 + total) % total;
            }
            else if (tecla == 's' || tecla == 'S')
            {
                selecionado = (selecionado + 1) % total;
            }
            else if (tecla == 13 || tecla == 32)
            {
                if (clear_opts)
                    ClearConsole(); // WOW

                if (opcoes[selecionado].func)
                    opcoes[selecionado].func(opcoes[selecionado].classe);

                return;
            }
        }
    }

}

#endif // cabou
/*
MOPTS
>> APENAS WINDOWS <<

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

                MOPTS::clear_opts = true;
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

    typedef void (*MenuFunc)();

    struct MenuOption // negocin basico
    {
        std::string texto; // wow
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
                    opcoes[selecionado].func();

                return;
            }
        }
    }

}

#endif // cabou
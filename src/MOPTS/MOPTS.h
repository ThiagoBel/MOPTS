/*
MOPTS
>> APENAS WINDOWS <<

    MOPTS::allline = true; // (true = a linha inteira da opção ficará com fundo branco e texto preto quando for navegada / false = apenas o texto da opção fica com fundo branco e texto preto quando for navegada)
    
    MOPTS::MenuOption opcoes[] = {
        {"OPCAO 1", FUNCTION1}, // Opção 1
        {"OPCAO 2", FUNCTION2}, // Opção 2
        {"OPCAO 3", FUNCTION3}  // Opção 2
        ...
    };
    // Esses 'FUNCTION' serve para que quando a opção for selecionada, a função ser executada :)

    MOPTS::ShowMenu("Descricao de cima", opcoes, "> ", false, true, "Descricao de baixo");

    // Primeira parte serve para mostrar um texto antes das opções
    // Segunda parte serve para colocar as opções no console
    // Terceira parte serve para mostrar o marcador, exemplo: "> OPCAO 1"
    // Quarta parte serve para ver se ele limpa as opções depois de ser usada (cls)
    // Quinta parte serve para quando a opção for selecionada ou ficar em cima, irá ficar um fundo branco na opção e texto preto na opção (Recomendado para terminais escuros)
    // Sexta parte serve para mostrar um texto depois das opções

    Não precisa dar créditos, fiz no tédio
*/
#pragma once
#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

namespace MOPTS
{
    bool allline = true; // MUDE SE QUISER (true = fica a linha inteira branca ao navegar / false = fica so o texto inteiro com fundo branco ao navegar)
    typedef void (*MenuFunc)();

    struct MenuOption
    {
        std::string texto;
        MenuFunc func;
    };

    inline void ClearConsole()
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
    inline void ShowMenu(
        const std::string &desc,
        MenuOption (&opcoes)[N],
        const std::string &marcador = "> ",
        bool limparDepois = true,
        bool corNaEscolha = true,
        const std::string &desc2 = "")
    {
        int selecionado = 0;
        const int total = static_cast<int>(N);

        while (true)
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
                if (i == selecionado)
                {
                    if (corNaEscolha)
                        SetConsoleTextAttribute(
                            hConsole,
                            BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

                    if (allline)
                    {
                        // Preenche a linha inteira
                        std::cout << std::string(larguraConsole, ' ') << "\r";
                    }

                    if (!marcador.empty())
                        std::cout << marcador;

                    std::cout << opcoes[i].texto << '\n';

                    if (corNaEscolha)
                        SetConsoleTextAttribute(hConsole, corOriginal);
                }
                else
                {
                    if (!marcador.empty())
                        std::cout << "  ";

                    std::cout << opcoes[i].texto << '\n';
                }
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
            else if (tecla == 'w' || tecla == 'W')
            {
                selecionado = (selecionado - 1 + total) % total;
            }
            else if (tecla == 's' || tecla == 'S')
            {
                selecionado = (selecionado + 1) % total;
            }
            else if (tecla == 13 || tecla == 32)
            {
                if (limparDepois)
                    ClearConsole();

                if (opcoes[selecionado].func)
                    opcoes[selecionado].func();

                return;
            }
        }
    }

}

#endif

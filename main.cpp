#include <Windows.h>
#include <chrono>

struct Jogador {
    int x;
    int y;
};

auto framesPorSegundo = std::chrono::milliseconds(1000/24);

int nLarguraJanela = 120;
int nAlturaJanela = 30;

void limpaTabuleiro(wchar_t* janela);

void desenhaParedes(wchar_t* janela);
void desenhaJogador(Jogador jogador, wchar_t* janela);

void eventosTeclado(Jogador* jogador, wchar_t* janela);

void sombraMapa(Jogador jogador, wchar_t* janela);

int main() {
    //Buffer
    wchar_t* janela = new wchar_t[nAlturaJanela * nLarguraJanela];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    Jogador jogador = { 1,1 };

    while (1) {
        auto novoContador = std::chrono::high_resolution_clock::now();

        limpaTabuleiro(janela);
        desenhaParedes(janela);

        eventosTeclado(&jogador, janela);
        desenhaJogador(jogador, janela);

        if (!GetAsyncKeyState(VK_SPACE))
            sombraMapa(jogador, janela);
        WriteConsoleOutputCharacterW(hConsole, janela, nLarguraJanela * nAlturaJanela, { 0,0 }, &dwBytesWritten);
        
        auto tempoRestanteDoFrame = std::chrono::high_resolution_clock::now() - novoContador;

        DWORD i = framesPorSegundo.count() - std::chrono::duration_cast<std::chrono::milliseconds>(tempoRestanteDoFrame).count();
        if(i > 0)
            Sleep(i);
    }


    return 0;
}

void limpaTabuleiro(wchar_t* janela) {
    for (int i = 0; i < nLarguraJanela * nAlturaJanela; i++) {
        janela[i] = L' ';
    }
}

void desenhaParedes(wchar_t* janela) {
    wsprintfW(&janela[0], L"########################################");
    wsprintfW(&janela[1 * nLarguraJanela], L"#     #                                #");
    wsprintfW(&janela[2 * nLarguraJanela], L"#  #  #                                #");
    wsprintfW(&janela[3 * nLarguraJanela], L"#  #  #                                #");
    wsprintfW(&janela[4 * nLarguraJanela], L"#  #  #                                #");
    wsprintfW(&janela[5 * nLarguraJanela], L"#  #  #                                #");
    wsprintfW(&janela[6 * nLarguraJanela], L"#  #  ##########                       #");
    wsprintfW(&janela[7 * nLarguraJanela], L"#  #           #                       #");
    wsprintfW(&janela[8 * nLarguraJanela], L"####   #########                       #");
    wsprintfW(&janela[9 * nLarguraJanela], L"#      #                               #");
    wsprintfW(&janela[10 * nLarguraJanela], L"#  #####                               #");
    wsprintfW(&janela[11 * nLarguraJanela], L"#      #                               #");
    wsprintfW(&janela[12 * nLarguraJanela], L"#      #######################         #");
    wsprintfW(&janela[13 * nLarguraJanela], L"#      #              #                #");
    wsprintfW(&janela[14 * nLarguraJanela], L"#      #  #    #####  #                #");
    wsprintfW(&janela[15 * nLarguraJanela], L"#      #  #    # #    #                #");
    wsprintfW(&janela[16 * nLarguraJanela], L"#      #  #      #    #                #");
    wsprintfW(&janela[17 * nLarguraJanela], L"#      #  ########    #                #");
    wsprintfW(&janela[18 * nLarguraJanela], L"#####  #       #      #                #");
    wsprintfW(&janela[19 * nLarguraJanela], L"#   #     #    #  #####                #");
    wsprintfW(&janela[20 * nLarguraJanela], L"#   ############                       #");
    wsprintfW(&janela[21 * nLarguraJanela], L"#                                      #");
    wsprintfW(&janela[22 * nLarguraJanela], L"#                                      #");
    wsprintfW(&janela[23 * nLarguraJanela], L"#                                      #");
    wsprintfW(&janela[24 * nLarguraJanela], L"#                                      #");
    wsprintfW(&janela[25 * nLarguraJanela], L"#                                      #");
    wsprintfW(&janela[26 * nLarguraJanela], L"#                                      #");
    wsprintfW(&janela[27 * nLarguraJanela], L"#                                      #");
    wsprintfW(&janela[28 * nLarguraJanela], L"#                                      #");
    wsprintfW(&janela[29 * nLarguraJanela], L"########################################");
}

void desenhaJogador(Jogador jogador, wchar_t* janela) {
    janela[jogador.y * nLarguraJanela + jogador.x] = L'@';
}

void eventosTeclado(Jogador* jogador, wchar_t* janela) {
    if (GetAsyncKeyState(VK_UP)) {
        if (janela[(jogador->y - 1) * nLarguraJanela + jogador->x] == L' ') {
            jogador->y -= 1;
        }
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        if (janela[(jogador->y + 1) * nLarguraJanela + jogador->x] == L' ') {
            jogador->y += 1;
        }
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        if (janela[jogador->y * nLarguraJanela + jogador->x + 1] == L' ') {
            jogador->x += 1;
        }
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        if (janela[jogador->y * nLarguraJanela + jogador->x - 1] == L' ') {
            jogador->x -= 1;
        }
    }
}

void sombraMapa(Jogador jogador, wchar_t* janela) {
    for (int i = 0; i < nLarguraJanela; i++) {
        for (int j = 0; j < nAlturaJanela; j++) {
            if (!(((jogador.x - i) < 3 && (jogador.x - i) > -3) && ((jogador.y - j) < 3) && (jogador.y - j) > -3)) {
                janela[j * nLarguraJanela + i] = L' ';
            }
        }
    }
}
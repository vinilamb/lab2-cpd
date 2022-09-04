#include <iostream>
#include <fstream>

#include "include/Dados.h"

void gerarDados();

int main() {
    gerarDados();
    return 0;
}

int main2()
{
    std::cout << "LAB 2" << std::endl;

    Dados dados;
    Timer timer;
    Estatisticas est;
    float tempo;

    int VALOR_MAXIMO=1000;

    for(int tamanho = 1000; tamanho<1000000; tamanho*=2){

        est.trocas = est.comparacoes = 0;

        VALOR_MAXIMO = tamanho;

        dados.geraVetorAleatorio(tamanho,0,VALOR_MAXIMO);
//          dados.geraVetorOrdenado(tamanho,0,VALOR_MAXIMO);
//        dados.geraVetorQuaseOrdenado(tamanho,0,VALOR_MAXIMO);
//        dados.geraVetorReverso(tamanho,0,VALOR_MAXIMO);
        std::cout << "N " << tamanho;
        std::cout.flush();

        timer.iniciaContagem();

        /// MÉTODOS DO LAB 1 ///

//        est = dados.ordenaComBubbleSort();
//        est = dados.ordenaComInsertionSort();
//        est = dados.ordenaComShellSort(SHELL59);
//        est = dados.ordenaComShellSort(KNUTH71);
//        est = dados.ordenaComShellSort(TOKUDA92);
//        est = dados.ordenaComShellSort(CIURA01);

        /// MÉTODOS DO LAB 2 ///
        est = dados.ordenaComQuickSort();
//        est = dados.ordenaComHeapSort();
//        dados.ordenaComCountingSort(VALOR_MAXIMO);

        tempo = timer.finalizaContagem();

        std::cout << " tempo " << tempo << " trocas " << est.trocas << " comparacoes " << est.comparacoes << std::endl;

//        dados.imprimeRegistros();

        bool estaOrdenado = dados.checaSeRegistrosOrdenados();
        bool ordenacaoEstavel = dados.checaSeOrdenacaoFoiEstavel();
        std::cout << (estaOrdenado ? "Vetor ordenado" : "Vetor NAO ordenado") << " - "
                  << (ordenacaoEstavel ? "Ordenacao foi estavel" : "Ordenacao NAO foi estavel") << std::endl;

    }

    return 0;
}

void gerarDados()
{
    std::vector<int> TAMANHOS_TESTE = {};

    for (int n = 10000; n <= 1000000; n += 10000)
    {
        TAMANHOS_TESTE.push_back(n);
    }

    std::vector<std::string> ORDENS = { "RAND", "ORD", "SEMI", "REV" };

    std::vector<std::string> ALGORITMOS = { "QUICK", "COUNT", "HEAP" };

    // abre o arquivo
    std::ofstream file ("medidas.txt");
    if (!file.is_open()) {
        std::cout << "Não foi possível abrir arquivo." << std::endl;
    }

    for (int N : TAMANHOS_TESTE) {
        for (const auto& algo : ALGORITMOS) {
            int VALOR_MAXIMO = N;

            if (algo == "COUNT") {
                VALOR_MAXIMO = 100;
            }

            for (const auto& ord : ORDENS) {
                Dados dados;
                Timer timer;
                Estatisticas est;
                float tempo;

                est.comparacoes = est.trocas = 0;

                if (algo == "QUICK" && (ord == "SEMI" || ord == "REV" || ord == "ORD"))
                    break;

                if (ord == "RAND") {
                    dados.geraVetorAleatorio(N, 0, VALOR_MAXIMO);
                } else if (ord == "ORD") {
                    dados.geraVetorOrdenado(N, 0, VALOR_MAXIMO);
                } else if (ord == "SEMI") {
                    dados.geraVetorQuaseOrdenado(N, 0, VALOR_MAXIMO);
                } else if (ord == "REV") {
                    dados.geraVetorReverso(N, 0, VALOR_MAXIMO);
                }

                if (algo == "HEAP") {
                    timer.iniciaContagem();
                    est = dados.ordenaComHeapSort();
                } else if (algo == "QUICK") {
                    timer.iniciaContagem();
                    est = dados.ordenaComQuickSort();
                } else if (algo == "COUNT") {
                    timer.iniciaContagem();
                    dados.ordenaComCountingSort(VALOR_MAXIMO);
                }
                tempo = timer.finalizaContagem();

                std::cout << N << " " << ord << " " << algo << " " << tempo << " " << est.comparacoes << " " << est.trocas << " " << std::endl;
                file << N << " " << ord << " " << algo << " " << tempo << " " << est.comparacoes << " " << est.trocas << " " << std::endl;

            }
        }
    }
}

#include "../include/Dados.h"

#include <iostream>     // std::cout
#include <algorithm>    // std::sort

bool pivoAleatorio = false;

int Dados::gerarPivoAleatorio(int xi, int xf)
{
    std::uniform_int_distribution<int> numero_aleatorio(xi, xf);
    return numero_aleatorio(*gerador);
}

//////////////////////////////////
/// CONSTRUTORES E DESTRUTORES ///
//////////////////////////////////

Dados::Dados()
{
    //construtor

    // Inicializa gerador de numeros aleatorios (da biblioteca random)
    std::random_device r;
    gerador = new std::default_random_engine(r());

}

Dados::~Dados()
{
    // destrutor

    delete(gerador);
}

////////////////////////////////////
/// METODOS DE ORDENACAO - LAB 2 ///
////////////////////////////////////

int Dados::particione(int pi, int pf)
{
    int pivo, i, j;
    //int initSize = registros.size();

    if (pivoAleatorio) {
        i = pi;
        j = pf;
        pivo = gerarPivoAleatorio(pi, pf);
    }
    else {
        i = pi + 1;
        j = pf;
        pivo = pi;
    }

    while (j > i) {
        while (i < pf) {
            estatisticasTotais.comparacoes++;
            if (registros[i] > registros[pivo])
                break;
            i++;
        }

        while (j > pi) {
            estatisticasTotais.comparacoes++;
            if (registros[j] <=  registros[pivo])
                break;
            j--;
        }

        if (i < j) {
            estatisticasTotais.trocas++;
            if (registros[i] > registros[j]) {
                troca(registros[i], registros[j]);
            }
        }
    }

    if (registros[j] < registros[pivo]) {
        estatisticasTotais.trocas++;
        troca(registros[j], registros[pivo]);
    }

    return j;
}

void Dados::quickSort(int i, int f)
{
    int pivo;
    if (f > i) {
        pivo = particione(i, f);
        quickSort(i, pivo - 1);
        quickSort(pivo + 1, f);
    }
}

Estatisticas Dados::ordenaComQuickSort()
{
    estatisticasTotais.trocas = 0;
    estatisticasTotais.comparacoes = 0;

    quickSort(0,registros.size()-1);

    return estatisticasTotais;
}

void Dados::heapify(int i)
{
    int e, d, maior;

    e = filhoEsquerdoHeap(i);
    d = filhoDireitoHeap(i);
    maior = i;

    if (e < heapSize) {
        estatisticasTotais.comparacoes++;
        if (registros[e] > registros[maior]) {
            maior = e;
        }
    }

    if (d < heapSize) {
        estatisticasTotais.comparacoes++;
        if (registros[d] > registros[maior]) {
            maior = d;
        }
    }

    if (maior != i) {
        estatisticasTotais.trocas++;
        troca(registros[i], registros[maior]);
        heapify(maior);
    }
}

void Dados::buildHeap()
{
    heapSize = registros.size();
    for(int i=heapSize/2 - 1; i>=0; i--)
        heapify(i);
}

Estatisticas Dados::ordenaComHeapSort()
{
    estatisticasTotais.trocas = 0;
    estatisticasTotais.comparacoes = 0;

    heapSize = 0;

    // TODO: implementar funcao de heapsort chamando buildHeap() e heapify(i)
    buildHeap();
    for (int i = heapSize - 1; i >= 1; i--) {
        estatisticasTotais.trocas++;
        troca(registros[i], registros[0]);
        heapSize--;
        heapify(0);
    }

    return estatisticasTotais;
}

void Dados::ordenaComCountingSort(int K)
{
    std::vector<long> acumulador(K+1, 0);
    std::vector<Registro> entrada(registros);

    for (size_t i = 0; i < entrada.size(); i++) {
        acumulador[entrada[i].getChave()]++;
    }

    for (int i = 1; i < K+1; i++) {
        int val = (acumulador[i] + acumulador[i - 1]);
        acumulador[i] = val;
    }

    for (int j = entrada.size() - 1; j >= 0; j--) {
        int chave = entrada[j].getChave();
        int indice = acumulador[chave]-1;

        registros[indice] = entrada[j];
        acumulador[chave]--;
    }

}

////////////////////////////////////
/// METODOS DE ORDENACAO - LAB 1 ///
////////////////////////////////////

Estatisticas Dados::ordenaComBubbleSort()
{
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    // TODO: implementar codigo do bubbleSort








    return est;
}

Estatisticas Dados::ordenaComInsertionSort()
{
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    // TODO: implementar codigo do insertionSort







    return est;
}

Estatisticas Dados::ordenaComShellSort(TipoShellSort tipo)
{
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    int n = registros.size();

    std::vector<int> sequenciaDeGaps = geraSequenciaDeGaps(n,tipo);

//    for(int i=0;i<sequenciaDeGaps.size();i++)
//        std::cout << sequenciaDeGaps[i] << ' ';

    // TODO: implementar codigo do shellSort









    return est;
}

bool Dados::checaSeOrdenacaoFoiEstavel()
{
    bool ehEstavel=true;

    // TODO: checar se elementos com chave igual mantem a ordem inicial analisando seus dados satelites
    for (std::size_t i = 0; i < registros.size() - 1; i++) {
        if ((registros[i] == registros[i + 1]) && (registros[i].getDadoSatelite() > registros[i + 1].getDadoSatelite()))
        {
            ehEstavel = false;
            break;
        }
    }

    return ehEstavel;
}

//////////////////////////
/// METODOS AUXILIARES ///
//////////////////////////

int Dados::filhoEsquerdoHeap(int i)
{
    return 2*i+1;
}

int Dados::filhoDireitoHeap(int i)
{
    return 2*i+2;
}

int Dados::paiHeap(int i)
{
    return (i-1)/2;
}

void Dados::imprimeHeap()
{
    int nivel=-1;
    int nodos_no_nivel=1;

    std::cout << "\nHEAP\n";
    for(int i=0;i<heapSize; i++){
        if(i==nodos_no_nivel-1){
            nivel++;
            nodos_no_nivel *= 2;
        }
        for(int j=0;j<nivel;j++)
            std::cout << " ";
        std::cout << registros[i];

        int e = filhoEsquerdoHeap(i);
        int d = filhoDireitoHeap(i);

        if(e<heapSize)
            std::cout << " filho_esq: " << registros[e];
        if(d<heapSize)
            std::cout << " filho_dir: " << registros[d];
        if(i>=heapSize/2)
            std::cout << " FOLHA";
        std::cout << std::endl;
    }
}

void Dados::troca(Registro &x, Registro &y)
{
    Registro temp;
    temp = x;
    x = y;
    y = temp;
}

bool Dados::checaSeRegistrosOrdenados()
{
    for(unsigned int i=0; i<registros.size() - 1; i++)
        if(registros[i]>registros[i+1])
            return false;

    return true;
}

std::vector<int> Dados::geraSequenciaDeGaps(int tamanho, TipoShellSort tipo)
{
    std::vector<int> v;

    int e=1;
    v.push_back(e);

    if(tipo==SHELL59){         // (Shell,1959) - sequencia 1, 2, 4, 8, 16, 32, ...
        while(e<tamanho){
            e *= 2;
            v.push_back(e);
        }

    }else if(tipo==KNUTH71){   // (Knuth,1971) - sequencia 1, 4, 13, 40, 121, 364, ...
        while(e<tamanho){
            e = e*3+1;
            v.push_back(e);
        }

    }else if(tipo==TOKUDA92){  // (Tokuda,1992) - sequencia 1, 4, 9, 20, 46, 103, ...
        int i=1;
        while((e=ceil((9.0 * pow(9.0,i)/pow(4.0,i) - 4.0)/5.0)) < tamanho){
            v.push_back(e);
            i++;
        }
    }else if(tipo==CIURA01){  // (Ciura,2001) - sequencia 1, 4, 10, 23, 57, 132, 301, 701 - daqui em diante nao tem prova de otimalidade
        int seq[8]={1,4,10,23,57,132,301,701};

        int i=1;
        while(i<8 && seq[i]<tamanho){
            v.push_back(seq[i]);
            i++;
        }

        int e=701;
        while((e=floor(2.25*(float)e))<tamanho)
            v.push_back(e);
    }

    return v;
}

void Dados::inicializaRegistrosComVetor(const std::vector<int>& vetor_auxiliar)
{
    // Reseta vetor de registros
    registros.clear();

    // Reserva novo tamanho do vetor de registros
    unsigned int tamanho = vetor_auxiliar.size();
    registros.reserve(tamanho);

    // Copia valores para vetor de registros
    for(unsigned int i=0; i<tamanho; i++){
        int c = vetor_auxiliar[i];
        int s = i+1;

        registros.push_back(Registro(c,s));
    }
}

void Dados::geraVetorAleatorio(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Seta distribuicao de chaves como valor aleatorio uniforme entre 'minimo_possivel' e 'maximo_possivel'
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);

    // Cria vetor auxiliar e preenche com valores aleatorios
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++){
        vetor_auxiliar[i] = chave_aleatoria(*gerador);
    }

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorOrdenado(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort (vetor_auxiliar.begin(), vetor_auxiliar.end());

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorQuaseOrdenado(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort (vetor_auxiliar.begin(), vetor_auxiliar.end());

    // Da uma leve embaralhada, dentro de uma distancia 'range'
    int range=tamanho/50;
    if(range<5)
        range=5;
    std::uniform_int_distribution<int> gap_para_troca(0,range);

    for(unsigned int i=0; i<tamanho; i++){
        int k = gap_para_troca(*gerador);
        if(k%5==0 && i+k<tamanho){
            int temp = vetor_auxiliar[i+k];
            vetor_auxiliar[i+k] = vetor_auxiliar[i];
            vetor_auxiliar[i] = temp;
        }
    }

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorReverso(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort (vetor_auxiliar.begin(), vetor_auxiliar.end(), std::greater<int>());

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::imprimeRegistros()
{
    for(unsigned int i=0; i<registros.size(); i++){
        std::cout << registros[i] << ' ';
    }
    std::cout << std::endl;
}


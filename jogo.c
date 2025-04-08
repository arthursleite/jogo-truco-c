#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char naipes[4][20] = {"Copas", "Espadas", "Paus", "Ouros"};
int numeros[10] = {1, 2, 3, 4, 5, 6, 7, 10, 11, 12};

typedef struct
{
    char naipe[20];
    int numero;
    int peso;
} Carta;

typedef struct
{
    Carta cartas[3];
    int maosGanhas;
    int rodadasGanhas;
} Jogador;

typedef struct
{
    int pontuacaoRodada;
    int contadorRodada;
    int contadorMao;
} Rodada;

Carta gerarCarta();
void mostrarCarta(Carta carta);
void mostrarMao(Jogador jogador);
void distribuirCartas(Jogador *jogador1, Jogador *jogador2);
void aumentar(int *pontuacaoRodada, int valor, Jogador jogadorSolicitante, Jogador jogadorRespondente);
Carta jogarCarta(Jogador jogador, int escolhaJogador);
void verificarVencedorMao(Carta cartaJogador1, Carta cartaJogador2, Jogador *jogador1, Jogador *jogador2);
void jogarMao(Jogador *jogador1, Jogador *jogador2, int rodada, int mao);

int main()
{
    srand(time(NULL));
    Carta zap;
    strcpy(zap.naipe, "Paus");
    zap.numero = 4;
    zap.peso = 14;
    Carta seteDeCopas;
    strcpy(seteDeCopas.naipe, "Copas");
    seteDeCopas.numero = 7;
    seteDeCopas.peso = 13;
    Carta espadao;
    strcpy(espadao.naipe, "Espadas");
    espadao.numero = 1;
    espadao.peso = 12;
    Carta pe;
    strcpy(pe.naipe, "Paus");
    pe.numero = 1;
    pe.peso = 11;

    Jogador jogador1, jogador2;
    jogador1.maosGanhas = 0;
    jogador2.maosGanhas = 0;
    jogador1.rodadasGanhas = 0;
    jogador2.rodadasGanhas = 0;
    printf("Bem-vindo ao jogo de Truco!\n");

    for (int contadorRodada = 1; contadorRodada <= 100; contadorRodada++)
    {

        printf("Inicio da rodada %d\n", contadorRodada);

        int resultadoPrimeiraMao = 0;
        int resultadoSegundaMao = 0;

        jogarMao(&jogador1, &jogador2, contadorRodada, 1);
        if (jogador1.maosGanhas > jogador2.maosGanhas)
        {
            resultadoPrimeiraMao = 1;
        }
        else if (jogador2.maosGanhas > jogador1.maosGanhas)
        {
            resultadoPrimeiraMao = 2;
        }
        else
        {
            printf("Primeira mao empatou.\n");
        }

        jogador1.maosGanhas = jogador2.maosGanhas = 0;
        jogarMao(&jogador1, &jogador2, contadorRodada, 2);
        if (jogador1.maosGanhas > jogador2.maosGanhas)
        {
            resultadoSegundaMao = 1;
        }
        else if (jogador2.maosGanhas > jogador1.maosGanhas)
        {
            resultadoSegundaMao = 2;
        }
        else
        {
            printf("Segunda mao empatou.\n");
        }

        if (resultadoPrimeiraMao == 0 && resultadoSegundaMao == 1)
        {
            printf("Jogador 1 vence a rodada com a maior carta da segunda mao.\n");
            jogador1.rodadasGanhas++;
        }
        else if (resultadoPrimeiraMao == 0 && resultadoSegundaMao == 2)
        {
            printf("Jogador 2 vence a rodada com a maior carta da segunda mao.\n");
            jogador2.rodadasGanhas++;
        }
        else if (resultadoPrimeiraMao == 0 && resultadoSegundaMao == 0)
        {
            printf("Rodada termina sem vencedor.\n");
        }
        else if (resultadoPrimeiraMao != 0 && resultadoSegundaMao == 0)
        {
            jogador1.maosGanhas = jogador2.maosGanhas = 0;
            jogarMao(&jogador1, &jogador2, contadorRodada, 3);

            if (jogador1.maosGanhas > jogador2.maosGanhas)
            {
                printf("Jogador 1 vence a rodada na terceira mao.\n");
                jogador1.rodadasGanhas++;
            }
            else if (jogador2.maosGanhas > jogador1.maosGanhas)
            {
                printf("Jogador 2 vence a rodada na terceira mao.\n");
                jogador2.rodadasGanhas++;
            }
            else
            {
                printf("Empate na terceira mao. Vencedor da primeira mao leva a rodada.\n");
                if (resultadoPrimeiraMao == 1)
                {
                    printf("Jogador 1 vence a rodada.\n");
                    jogador1.rodadasGanhas++;
                }
                else if (resultadoPrimeiraMao == 2)
                {
                    printf("Jogador 2 vence a rodada.\n");
                    jogador2.rodadasGanhas++;
                }
            }
        }
        else if (resultadoPrimeiraMao == 1 && resultadoSegundaMao == 1)
        {
            printf("Jogador 1 vence a rodada com duas vitorias consecutivas.\n");
            jogador1.rodadasGanhas++;
        }
        else if (resultadoPrimeiraMao == 2 && resultadoSegundaMao == 2)
        {
            printf("Jogador 2 vence a rodada com duas vitorias consecutivas.\n");
            jogador2.rodadasGanhas++;
        }
        printf("Rodada %d: Jogador 1: %d, Jogador 2: %d\n", contadorRodada, jogador1.rodadasGanhas, jogador2.rodadasGanhas);

        if (jogador1.rodadasGanhas >= 12 || jogador2.rodadasGanhas >= 12)
        {
            break;
        }
    }

    return 0;
}

Carta gerarCarta()
{
    Carta carta;
    int naipe = rand() % 4;
    int numero = rand() % 10;

    strcpy(carta.naipe, naipes[naipe]);
    carta.numero = numeros[numero];

    int pesos[] = {4, 5, 6, 7, 8, 9, 10, 3, 2, 1};
    carta.peso = pesos[numero - 1];

    if (strcmp(carta.naipe, "Paus") == 0 && carta.numero == 4)
    {
        carta.peso = 14;
    }
    else if (strcmp(carta.naipe, "Copas") == 0 && carta.numero == 7)
    {
        carta.peso = 13;
    }
    else if (strcmp(carta.naipe, "Espadas") == 0 && carta.numero == 1)
    {
        carta.peso = 12;
    }
    else if (strcmp(carta.naipe, "Paus") == 0 && carta.numero == 1)
    {
        carta.peso = 11;
    }

    return carta;
}

void mostrarCarta(Carta carta)
{
    printf("%d de %s\n", carta.numero, carta.naipe);
}

void mostrarMao(Jogador jogador)
{
    printf("Mao do jogador:\n");
    for (int i = 0; i < 3; i++)
    {
        mostrarCarta(jogador.cartas[i]);
    }
}

void jogarMao(Jogador *jogador1, Jogador *jogador2, int rodada, int mao)
{
    printf("Rodada %d\n\n", rodada);
    distribuirCartas(jogador1, jogador2);

    printf("Cartas do jogador 1:\n");
    mostrarMao(*jogador1);

    printf("Cartas do jogador 2:\n");
    mostrarMao(*jogador2);

    printf("Jogada do jogador 1:\n");
    printf("Escolha uma carta (1, 2 ou 3): ");
    int escolhaJogador1;
    scanf("%d", &escolhaJogador1);

    printf("Jogada do jogador 2:\n");
    printf("Escolha uma carta (1, 2 ou 3): ");
    int escolhaJogador2;
    scanf("%d", &escolhaJogador2);

    printf("Jogador 1 jogou: ");
    mostrarCarta(jogador1->cartas[escolhaJogador1 - 1]);

    printf("Jogador 2 jogou: ");
    mostrarCarta(jogador2->cartas[escolhaJogador2 - 1]);

    Carta cartaJogador1 = jogarCarta(*jogador1, escolhaJogador1);
    Carta cartaJogador2 = jogarCarta(*jogador2, escolhaJogador2);

    verificarVencedorMao(cartaJogador1, cartaJogador2, jogador1, jogador2);

    printf("\nFim da mao %d da rodada %d.\n", mao, rodada);
}

void distribuirCartas(Jogador *jogador1, Jogador *jogador2)
{
    for (int i = 0; i < 3; i++)
    {
        jogador1->cartas[i] = gerarCarta();
        jogador2->cartas[i] = gerarCarta();
    }
}

void aumentar(int *pontuacaoRodada, int valor, Jogador jogadorSolicitante, Jogador jogadorRespondente)
{

    printf("Pontuacao da rodada aumentada para: %d\n", *pontuacaoRodada);
}

Carta jogarCarta(Jogador jogador, int escolhaJogador)
{
    printf("Jogador jogou: ");
    mostrarCarta(jogador.cartas[escolhaJogador - 1]);
    return jogador.cartas[escolhaJogador - 1];
}

void verificarVencedorMao(Carta cartaJogador1, Carta cartaJogador2, Jogador *jogador1, Jogador *jogador2)
{
    if (cartaJogador1.peso > cartaJogador2.peso)
    {
        jogador1->maosGanhas++;
        printf("Jogador 1 venceu a mao!\n");
    }
    else if (cartaJogador2.peso > cartaJogador1.peso)
    {
        jogador2->maosGanhas++;
        printf("Jogador 2 venceu a mao!\n");
    }
    else
    {
        printf("Empate!\n");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

const int LARGURA = 25;
const int ALTURA = 25;
const int TRUE = 1;
const int FALSE = 0;

/*Criação das novas geraçoes de criaturas*/
void novager (int borda[ALTURA][LARGURA])
{
    int filas;
    int colunas;
    for (filas =1; filas <ALTURA -1; filas++)
    {
        for (colunas = 1; colunas <LARGURA -1; colunas ++)
        {
            if (borda[filas][colunas] == 1)
                borda[filas][colunas] = 'O';
            else if (borda[filas][colunas] == 2)
                borda[filas][colunas] = 'O';
            else if (borda[filas][colunas] == 0)
                borda[filas][colunas] = ' ';
        }
    }
}
/*Verificação dos vizinhos para ver se a criatura vai morrer ou viver*/
void vizinhos (int borda[ALTURA][LARGURA])
{
    int vizinho;
    int filas;
    int colunas;
    int a, b;
    for (filas =1; filas <ALTURA; filas++)
    {
        for (colunas = 1; colunas <LARGURA; colunas ++)
        {
            vizinho = 0;
            if (borda[filas][colunas] == 'O')
            {
                for (a = -1; a <2; a++)
                {
                    for (b = -1; b <2; b++)
                        if (((filas +a) == filas) && ((colunas +b) == colunas))
                             vizinho = vizinho;
                        else if ((borda[filas +a][colunas +b] == 'O') ||(borda[filas +a][colunas +b] == 1) || (borda[filas +a][colunas +b] == 0))
                            vizinho++;
                }
                if ((vizinho == 2) || (vizinho == 3))
                    borda[filas][colunas] = 1; /*Vivo*/
                else if ((vizinho < 2) || (vizinho >= 4))
                    borda[filas][colunas] = 0; /*Morto*/
            }
        }
    }
}
/*Checagem das novas geraçoes vendo as possiveis novas criaturas*/
void checknovager(int borda[ALTURA][LARGURA])
{
    int vizinho;
    int filas;
    int colunas;
    int a, b;
    for (filas =1; filas <ALTURA -1; filas++)
    {
        for (colunas = 1; colunas <LARGURA -1; colunas ++)
        {
            vizinho = 0;
            if (borda[filas][colunas] == ' ')
            {
                for (a = -1; a <2; a++)
                {
                    for (b = -1; b <2; b++)
                        if (((filas +a) == filas) && ((colunas +b) == colunas))
                            vizinho = vizinho;
                        else if ((borda[filas +a][colunas +b] == 'O') || (borda[filas +a][colunas +b] == 1) || (borda[filas +a][colunas +b] == 0))
                            vizinho++;
                }
                if ((vizinho == 3))
                    borda[filas][colunas] = 2;
            }
        }
    }
}
/*Checagem de celulas vivas e/ou mortas */
int checkexistencia (int borda[ALTURA][LARGURA])
{
    int filas;
    int colunas;
    int creatures =0;
    for (filas =1; filas <ALTURA -1; filas++)
    {
        for (colunas = 1; colunas <LARGURA -1; colunas ++)
        {
            if (borda[filas][colunas] == 'O')
                creatures++;
        }
    }
    if (creatures == 0)
        return TRUE; /*Todas as criaturas morrem*/
    else return FALSE; /*Ainda tem criaturas vivas*/
}

/*Criação da matriz*/
void filarray(int borda[ALTURA][LARGURA])
{
    int i,j;
    for(i =1; i <ALTURA-1; i++)
        for(j=1; j <LARGURA-1; j++)
            borda[i][j] = ' ';
}
/*Criação da borda do jogo*/
void fronteira (int borda[ALTURA][LARGURA])
{
    int colunas, filas;
    for (colunas =0; colunas <LARGURA; colunas++)
    {
        borda[0][colunas] = '_';
        borda[ALTURA -1][colunas]= '_';
    }
    for (filas =1; filas <ALTURA; filas++)
    {
        borda[filas][0] = '|';
        borda[filas][LARGURA -1] = '|';
    }
}
/*Criação do display do jogo*/
void display(int borda[ALTURA][LARGURA])
{
int filas;
int colunas;
    for (filas = 0; filas <ALTURA; filas++)
    {
        for(colunas =0; colunas <LARGURA; colunas++)
            printf ("%3c", borda[filas][colunas]);
        printf ("\n");
    }
}
/*Essa funçao é responsavel por fazer o jogo rodar*/
void inicio (int borda[ALTURA][LARGURA], int numgeneration)
{
    int i, c, check;
    for (i = 1; (i <= numgeneration) && (c != 32); i++)
    {
        system("cls");
        vizinhos(borda);
        checknovager(borda);
        novager(borda);
        printf ("Geracao: %i\n", i);
        display(borda);
        if(kbhit())
        {
            c = getch();
            if(c == 32)
                break;
        }
        check = checkexistencia(borda);
        if ((check= checkexistencia(borda)) ==TRUE)
        {
            printf ("\nTodas as celulas morreram");
            c = 32;
        }
    }
}
/*Essa funçao é responsavel por colocar as criaturas em lugares aleatórios no começo*/
void filarandom(int borda[ALTURA][LARGURA])
{
    int i, j, num;
    srand((unsigned)time(NULL));
    for(i =1; i <ALTURA -1; i++)
        for(j=1; j <LARGURA -1;j++)
        {
            num = rand()%11;
            if (num == 1)
                borda[i][j] = 'O';
            else borda[i][j] = ' ';
        }
}
/*Essa funçao é como se fosse o "main"*/
void jogodavida(int borda[ALTURA][LARGURA])
{
    int i, generation, c;
    filarandom(borda);
    display(borda);
    printf ("\nSelecione o numero de geracoes: ");
    scanf ("%i", &generation);

    inicio(borda, generation);


}

int main (void)
{
    int borda[ALTURA][LARGURA], mode;
    fronteira(borda);
    filarray(borda);

    printf ("-------------- JOGO DA VIDA DE CONWAY-------------\n");
    printf ("Modo Automático  \n");
    printf("Digite o número de Gerações que deseja ver\n");

    jogodavida(borda);
return 0;
}

/*
  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome:
  NUSP:

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:

  - função mallocSafe copiada de: 

  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>  /* fprintf() */
#include <stdlib.h> /* exit(), EXIT_FAILURE  */

#include "io.h"  /* graveImagemPPM(), carregueImagemPPM() */
#include "imagem.h" /* LIMIAR, AVISO(), Byte, Imagem, CelPixel, CelRegiao, 
                       mallocImagem(), freeImagem(),   freeRegioes()
                       copieImagem(),  segmenteImagem()
                     */
#include "graphic.h" /* myInit() */
#include "main.h"    /* quit(), graveImagem() */

/*---------------------------------------------------------------*/
/* 
 *  C O N S T A N T E S 
 */

/* suposto numero maximo de caracteres em um nome de arquivo */
#define MAX_NOME 128

/*---------------------------------------------------------------*/
/*
 *  P R O T Ó T I P O S
 */

static void 
mostreUso(char *nomePrograma);

/*---------------------------------------------------------------*/
/* 
 *  M A I N 
 */

int 
main(int argc, char *argv[])
{
    Imagem *imgOriginal   = NULL; /* ponteiro para a imagem original */
    Imagem *tela          = NULL; /* ponteiro para a imagem corrente ou atual */
    CelRegiao *iniRegioes = NULL; /* ponteiro para a lista de regioes */
    char *nomeArquivo;

    /* 1. pegue da linha de comando o nome do arquivo com a imagem */
    //printf("TEEEEEESTE");
    nomeArquivo = argv[1];
    //printf("%s", nomeArquivo);

    /* 2. carregue de uma arquivo, no formato PPM, a imagem original */
    //printf("TEEEEESTE1");
    imgOriginal = carregueImagemPPM(nomeArquivo);
    //printf("TEEEEESTE2");
    if (imgOriginal == NULL) 
    {
        AVISO(main: Vixe! ainda nao li a imagem original.);
        return 0;    
    }
  
    /* 3 crie a imagem corrente (tela) em que trabalharemos */

        tela = mallocImagem(imgOriginal -> width, imgOriginal -> height);

    /* 4 copie a imagem original (lida) para a imagem corrente (tela) */ 

        copieImagem(tela, imgOriginal);

    if (tela == NULL) 
    {
        AVISO(main: Vixe! ainda nao criei a imagem corrente.);
        return 0;    
    }

    /* 5 segmente a imagem corrente (tela) criando a lista de regioes */

    if (iniRegioes == NULL) 
    {
        AVISO(main: Vixe! ainda nao segmentei a imagem.);
        /* apesar disso ainda e possivel visualizar a imagem lida,
           vamos em frente */
    }

    /* 6 passe a bola para a parte grafica */  
    myInit(&argc, argv, tela, imgOriginal, iniRegioes);
  
    return 0; /* we never return here; this just keeps the compiler happy
                 http://www.cs.umd.edu/class/fall2011/cmsc427/lectures.shtml */
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   
 *                 O B R I G A T O R I A S
 */

/*---------------------------------------------------------------*/

/* 
   quit()

   Chamada quando 'q' e teclada.

   Recebe ponteiros TELA e IMG para estruturas que representam
   uma imagem.
 
   Libera toda a memoria que foi alocada dinamicamente para IMG,
   TELA e INIREGIOES. Depois de liberar a memoria a função 
   encerra a execução do programa.
   
   Esta funcao usa as funcoes freeImagem() e freeRegioes(), 
   ambas do modulo imagem.
*/

void 
quit(Imagem *tela, Imagem *img, CelRegiao *iniRegioes)
{
    AVISO(main.c: Vixe Ainda nao fiz a funcao quit.);
    exit(EXIT_SUCCESS); /* a execução do programa termina neste ponto */
}

/*---------------------------------------------------------------*/
/* 
   graveImagemRPG()

   Chamada quando 'g' e teclada.

   Recebe um ponteiro IMG para uma estrutura que representa
   uma imagem.

   Pede que o usuario digite o nome de um arquivo e 
   grava a imagem IMG (que tipicamente sera a imagem correte na tela) 
   nesse arquivo.

   Esta funcao usa a funcao graveImagemPPM do modulo io.
*/

void
graveImagem(Imagem *img)
{
    char nomeArquivo[MAX_NOME];
    printf("Digite o nome do arquivo em que a imagem deve ser gravada: ");
    scanf("%s", nomeArquivo);
    graveImagemPPM(nomeArquivo, img);
    AVISO(main.c: Vixe Ainda nao fiz a funcao graveImagem.);
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                     A U X I L I A R E S 
 */

static void 
mostreUso(char *nomePrograma)
{
    fprintf(stderr,"%s: Uso \n"
            "meu_prompt> %s <nome arq. imagem>\n"
            "    <nome arq. image> = nome arq. com Portable PixMap Binary.\n",
            nomePrograma, nomePrograma);
}


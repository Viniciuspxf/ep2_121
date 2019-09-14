/* 
 * MAC0121 Algoritmos e Estruturas de Dados I
 */

/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/

/*
  Neste exercicio programa usaremos apenas o Portable pixmap binary.

  http://netpbm.sourceforge.net/doc/ppm.html

  Funcoes para manipulacao de arquivos no formato Netpbm:
    
  Magic Number       Type                  Encoding
  P1              Portable bitmap          ASCII
  P2              Portable graymap         ASCII
  P3              Portable pixmap          ASCII
  P4              Portable bitmap          Binary
  P5              Portable graymap         Binary
  P6              Portable pixmap          Binary
 
  fonte: http://en.wikipedia.org/wiki/Netpbm_format

  ou ainda 
 
  meu_prompt> > man Netpbm
  
  netpbm(1)      General Commands Manual          netpbm(1)
  
  NAME
  netpbm - package of graphics manipulation programs and libraries
  [...]

*/

#undef DEBUG_CARREGA
#undef DEBUG_COR

#include <stdio.h>  /* fprintf, sprintf */
#include <stdlib.h> /* fopen, fclose, exit, EXIT_SUCCESS, EXIT_FAILURE */ 
#include <string.h> /* strncpy, strcat,... */
#include "imagem.h" /* Imagem */
#include "io.h"  /* graveImagemPPM(), carregueImagemPPM()  */

/* tamanho maximo de uma linha no arquivo */
#define MAX_NOME 128

/* *****************************************************************
   graveImagemPPM.
   
   Recebe o nome de um arquivo atraves de nomeArquivo e recebe 
   a representacao de uma imagem colorida (RGB) atraves de img. 
   A funcao grava a imagem em um arquivo com o nome dado.

   A gravacao e feita segundo o formato "Portable pixmap binary" com 
   maxValue 255.
   Isto significa que usaremos 1 byte (= 8 bits) por cor, 3 byte (= 24 bits)
   por pixel.
   
   AUTOR: Carlos Hitoshi Morimoto
*/


void 
graveImagemPPM(char *nomeArquivo, Imagem *img)
{
    FILE *fSaida;
    int   w, h;
    char  nome[MAX_NOME];
  
    /* nao acrescentamos mais a extensao .ppm ao nome do arquivo */
    strncpy(nome, nomeArquivo, MAX_NOME-1);
    /* strcat(nome,".ppm"); */

    /* criaremos um arquivo binario (w = write, b = binary) */
    fSaida = fopen(nome, "wb");
    if (fSaida == NULL) 
    {
        fprintf(stderr, 
                "graveImagemPPM: ERRO: arquivo '%s' nao pode ser criado\n", 
                nomeArquivo);
        return;
    }

    /* P6       Portable pixmap       Binary */
    /* http://netpbm.sourceforge.net/doc/ppm.html */
    /* whitespace = blanks, TABs, CRs, LFs */
    fprintf(fSaida, "P6\n");              /* magic number   + whitespace  */
    /* Strings starting with "#" may be comments */
    fprintf(fSaida, "# %s: imagem criada com o EP2 de MAC0121 2019\n", nome);
    fprintf(fSaida, "%d " , img->width);  /* width  ASCII   + whitespace  */
    fprintf(fSaida, "%d\n", img->height); /* height ASCII   + whitespace  */
    fprintf(fSaida, "255\n");             /* maxValue ASCII + whitespace  */

    /* A raster of Height rows, in order from top to bottom. */
    for (h = 0; h < img->height; h++)
    {
        for (w = 0; w < img->width; w++)
	{ 
            Byte red   = img->pixel[h][w].cor[RED]   ; /* intens. vermelho */
            Byte green = img->pixel[h][w].cor[GREEN] ; /* intens. verde    */
            Byte blue  = img->pixel[h][w].cor[BLUE]  ; /* intens. azul     */
	  
            fprintf(fSaida, "%c%c%c", red, green, blue);

#ifdef DEBUG_COR
            if (190 < h && h < 200 && 290 < w && w < 300 )
                fprintf(stderr, "Pixel w=%d h=%d cor = (%d,%d,%d)\n", 
                        w, h, red, green, blue);
#endif

	}
    }

    fclose(fSaida);

    fprintf(stdout, "graveImagemPPM: A imagem foi salva no arquivo: '%s'\n", nome);
}

/* *****************************************************************
   carregueImagemPPM.
 
   Recebe o nome de um arquivo com sua extensao e le desse arquivo 
   uma imagem no formato Portable PixMap binary.
 
   A funcao retorna a representacao  da imagem colorida 
   'true colors' (estrutura Imagem).

*/

Imagem *
carregueImagemPPM(char *nomeArquivo)
{
    FILE *fEntrada;
    char magicNumber = '\0';
    char ch = '\0';
    int height;
    int width;
    int maxValue;  
    Imagem *img;
    int w, h;


    fEntrada = fopen(nomeArquivo, "rb");
    if (fEntrada == NULL) 
    {
        fprintf(stderr, 
                "carregueImagemPPM: ERRO: Nao consegui abrir o arquivo '%s'\n",
                nomeArquivo);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, 
            "carregueImagemPPM: Arquivo '%s' com a imagem foi aberto.\n", 
            nomeArquivo);

    /* confira o magicNumber */
    /* fgets(magicNumber, 3, fEntrada); */
    fscanf(fEntrada, "P%c\n", &magicNumber);
    if (magicNumber != '6')
    {
        fprintf(stderr, 
                "carregueImagemPPM: ERRO: '%s' nao contem uma imagem no"
                " formato Portable pixmap binary\n"
                "      MagicNumber '%c'\n", nomeArquivo, magicNumber);
        exit(EXIT_FAILURE);
    }

    /* remove linhas com comentarios. 
       Hmmm tenho duvida se um comentario pode aparecer so nessa posicao...
       http://www0.cs.ucl.ac.uk/staff/a.steed/book_tmp/CGVE/code/Lib3D1.0/maintexture.c
     */
    ch = getc(fEntrada);
    while (ch == '#') 
    { /* remove linha com comentario */
        fprintf(stdout,"Comentario: %c", ch);
        do 
        {
            ch = getc(fEntrada);
            fprintf(stdout,"%c", ch);
        }
        while (ch != '\n');
        ch = getc(fEntrada); /* primeiro caractere da proxima linha */
    }
    ungetc(ch, fEntrada); /* coloca ultimo caractere devolta no buffer */

    /* leitura da largura a imagem */
    if (fscanf(fEntrada, "%d ", &width) != 1) 
    {
        fprintf(stderr, "carregueImagemPPM: ERRO: problema na leitura (width)\n");
        exit(EXIT_FAILURE);
    }

    if (fscanf(fEntrada, "%d\n", &height) != 1) 
    {
        fprintf(stderr, "carregueImagemPPM: ERRO: problema na leitura (height)\n");
        exit(EXIT_FAILURE);
    }

    if (fscanf(fEntrada, "%d\n", &maxValue) != 1) 
    {
        fprintf(stderr, "ERRO! problema na leitura (maxValue)\n");
        exit(EXIT_FAILURE);
    }
  
    /* cria estrutura para armazenar a imagem */
    img = mallocImagem(width, height);
    img->width  = width;
    img->height = height;

#ifdef DEBUG_CARREGA
    fprintf(stderr, "Criei a imagem, width=%d, height=%d maxValue=%d\n", 
            width, height, maxValue);
#endif

    /* A raster of Height rows, in order from top to bottom. */
    for (h = 0; h < img->height; h++)
    {
        for (w = 0; w < img->width; w++)
	{ 
            Byte red, green, blue;

            if (fscanf(fEntrada, "%c%c%c", &red, &green, &blue) != 3)
	    {
                fprintf(stderr, "ERRO! problema na leitura (pixel [%d][%d])\n", h, w);
                freeImagem(img);
                exit(EXIT_FAILURE);
	    }

            img->pixel[h][w].cor[RED]   =  red   ; /* intensidade vermelho */
            img->pixel[h][w].cor[GREEN] =  green ; /* intensidade verde */
            img->pixel[h][w].cor[BLUE]  =  blue  ; /* intensidade azul */

#ifdef DEBUG_COR
            if (190 < h && h < 200 && 290 < w && w < 300 )
                fprintf(stderr, "Pixel w=%d h=%d cor = (%d,%d,%d)\n", 
                        w, h, red, green, blue);
#endif

#ifdef DEBUG_CARREGA
            fprintf(stderr, "Pixel w=%d h=%d cor = (%f,%f,%f)\n", 
                    w, h, 
                    img->pixel[h][w].cor[RED], 
                    img->pixel[h][w].cor[GREEN], 
                    img->pixel[h][w].cor[BLUE]);
#endif
	}
    }

    fclose(fEntrada);

    fprintf(stdout, "A imagem foi carregada e o "
            "arquivo '%s' foi fechado.\n", nomeArquivo);

    return img;
}


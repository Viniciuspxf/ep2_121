/*
 * MAC0121 Algoritmos e Estruturas de Dados I
 *
 */

/*
    NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/

/**************************************************************** 
  Neste EP utiliza True Color (24 bits) 

      http://en.wikipedia.org/wiki/True_Color#True_color_.2824-bit.29

  Neste EP todas as cores sao representadas atraves de True Color.

  Declaracoes das representacoes referentes a uma imagem:
     pixel, Image, CelPixel, CelRegiao,
 
  Prefixo 'Cel' em um tipo indica a definicao de um elemento 
    de um lista ligada/encadeada.
 
  Sufixo  'TC' em um tipo indica a definicao de um valor
    relativo a True Color. Serve apenas para nos lembrar
    a representacao de cores que esta sendo utilizada. 

  Neste arquivo tambem estao os prototipos das funcoes que 
  manipulam imagens.
    
****************************************************************/

#ifndef _IMAGEM_H
#define _IMAGEM_H 

/* algumas macros uteis */
#define AVISO(msg) fprintf(stdout,"AVISO: %s\n", #msg)
#define ERRO(msg)  fprintf(stderr,"ERRO: %s\n", #msg)

/* limiar default usado para a determinacao de pixels de borda */
#define LIMIAR 120

/*-------------------------------------------------------------*/
/* indices de uma cor/canal */
enum cores
{
    RED   /* = 0 */,
    GREEN /* = 1 */,
    BLUE  /* = 2 */
};

/*-------------------------------------------------------------*/
enum bool 
{
    FALSE /* = 0 */,
    TRUE  /* = 1 */
};

/* Byte = valores entre 0 e 255 (8 bits) */
typedef unsigned char Byte;

/* Bool = valores FALSE e TRUE */
typedef Byte Bool;

/* Color = nivel/intensidade de uma cor/canal = valores entre 0 e 255 
   no momento nao esta sendo usado */
typedef Byte Color; 

/*-------------------------------------------------------------*/
/* celula de um lista de pixels */
typedef struct celPixel CelPixel;
struct celPixel 
{ 
    int        col, lin; /* [lin][col] e a posicao do pixel */
    CelPixel *proxPixel; /* ponteiro para o proximo pixel */
};

/*-------------------------------------------------------------*/
/* celula de uma lista de regioes */
typedef struct celRegiao CelRegiao;
struct celRegiao 
{        
    int           nPixels; /* no. de pixels na regiao */
    Byte           cor[3]; /* cor dos pixels na regiao */
    Bool            borda; /* indica se a regiao e ou nao de borda */
    CelPixel   *iniPixels; /* ponteiro para a lista de pixels na regiao */
    CelRegiao *proxRegiao; /* ponteiro para a proxima regiao */  
};

/*-------------------------------------------------------------*/
/* pixel True Color */
/* http://en.wikipedia.org/wiki/True_Color#True_color_.2824-bit.29 */
typedef struct pixel Pixel;
struct pixel
{
    Byte cor[3];      
         /* cor[RED]   eh um valor entre 0 e 255 */
         /* cor[GREEN] eh um valor entre 0 e 255 */
         /* cor[BLUE]  eh um valor entre 0 e 255*/
    CelRegiao  *regiao; /* ponteiro para a celula da regiao do pixel 
                           se == NULL indica que o pixel nao 
                           pertence a regiao alguma */
}; 

/*------------------------------------------------------------*/
/* representacao para uma imagem colorida */
typedef struct imagem Imagem;
struct imagem 
{
    int     width; /* no. de colunas (width/largura) da imagem em pixels */
    int    height; /* no. de linhas  (height/altura) da imagem em pixels */
    Pixel **pixel; /* matriz height x width de pixels com os níveis RGB  */
}; 

/*
  Funcoes globais que manipulam uma imagem:
*/

/*-------------------------------------------------------------*/ 
/*  prototipos de funcoes */
 
Imagem *
mallocImagem(int width, int height);

void 
freeImagem(Imagem *img);

Pixel
getPixel(Imagem *img, int col, int lin);

void 
freeRegioes(CelRegiao *iniRegioes);

void 
copieImagem(Imagem *destino, Imagem *origem);

void 
pinteImagem(Imagem *img, Byte cor[]);

void
pinteRegioes(Imagem *img, CelRegiao *iniRegioes, Bool borda);

void
repinteRegiao(Imagem *img, int col, int lin, Byte cor[]);

void
repinteRegioes(Imagem *img, CelRegiao *iniRegioes, int col, int lin, Byte cor[]);

CelRegiao * 
segmenteImagem(Imagem *img, int limiar);  

#endif /* _IMAGEM_H */

/* 
 * MAC0121 Algoritmos e Estruturas de Dados I
 */

/*
  Interface para as funcoes do main que sao chamadas 
  pelo modulo graphics quando ocorre um evento do teclado
  ou do mouse, ou seja,

       -  um caractere e teclado ou
       -  ha um clique do mouse 
*/

#ifndef _MAIN_H
#define _MAIN_H

# include "imagem.h" /* Imagem */

void 
graveImagem(Imagem *img);

void 
quit (Imagem *tela, Imagem *img, CelRegiao *listaRegioes);

#endif

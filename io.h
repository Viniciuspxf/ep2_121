/* 
 * MAC0121 Algoritmos e Estruturas de Dados I
 */

/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/

/*
 * Interface para uso do modulo io 
 *
 */

#ifndef _IO_H
#define _IO_H

#include "imagem.h" /* Imagem */

void 
graveImagemPPM(char *nomeArquivo, Imagem *img);

Imagem *
carregueImagemPPM(char *nomeArquivo);

#endif /* _IO_H */

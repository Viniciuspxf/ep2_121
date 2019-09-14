/*
 * MAC0121 Algoritmos e Estruturas de Dados I
 */

/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/


/*
    graphics.h

    Interface das rotinas grÃ¡ficas utilizadas por
    main.c e 
*/

#ifndef _GRAPHIC_H
#define _GRAPHIC_H

/* tipos e prototipos de funcoes que manipulam imagens */
# include "imagem.h" /* Imagem, CelRegiao */

void 
myInit(int *argc, char *argv[], Imagem *tela, Imagem *imgOriginal,
       CelRegiao *iniRegioes);

#endif  /* _GRAPHIC_H */

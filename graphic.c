/*
  MAC0121 Algoritmos e Estruturas de Dados I

  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/

/*
  Funcoes responsaveis pela parte grafica.
*/

#define  _GRAPHIC_C

#include <stdio.h>    /* fprintf(), printf() */
#include <stdlib.h>   /* exit() */

#ifdef __APPLE__
   /* em http://web.eecs.umich.edu/~sugih/courses/eecs487/glut-howto/ 
      e dito que 
      "Despite Apple's documentation, you don't need to include 
       gl.h and glu.h, as they are already included in glut.h. " 

#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
   */
#include <GLUT/glut.h>
#else
#include <GL/glut.h>  /* funcoes do glut */
#endif


#include "cores.h"   /* BACK_GROUND, NUM_CORES, cores[0..NUM_CORES] */
#include "graphic.h" /* myInit() */
#include "main.h"    /* graveImagem(), quit() */
#include "imagem.h"  /* LIMIAR, pinteImagem(), pinteRegiao(), 
                        pinteRegioes(), pinteBordas(), 
                        segmenteRegioes(), AVISO() */
                  
#undef DEBUG

/* 
 * Constantes
 */

/* canto da janela */
#define X0     100
#define Y0      50

/*-------------------------------------------------------------*/
/*
 * VARIAVEIS GLOBAIS: iniciam com o caractere '_' (underscore) 
 * 
 */

static Imagem   *_imgOriginal = NULL; /* imagem original, nao e alterada */
static Imagem          *_tela = NULL; /* imagem corrente */
static CelRegiao *_iniRegioes = NULL;
static int        _iCor   = 0;      /* indice de uma cor no vetor cores */  
static int        _limiar = LIMIAR; /* limiar inicial usada para determinar
                                          pontos de borda */ 

/*-------------------------------------------------------------*/
/*
 * P R O T O T I P O S   D A    F U N C O E S   D A   P A R T E
 *                  G R A F I C A
 */

static void 
myReshape(int w, int h);

static void 
myKeyboard(unsigned char key, int x, int y);

static void 
myDisplay();

static void 
myMouse(int b, int s, int x, int y);

static void  
mostreUso();

static void  
copiePonteirosRegiao(Imagem *destino, Imagem *origem);

/*-------------------------------------------------------------*/
/* 
 *  F U N C O E S   A U X I L I A R E S
 *
 */

void 
myInit(int *argc, char *argv[], Imagem *tela, Imagem *imgOriginal,
       CelRegiao *iniRegioes)
{
    _tela        =        tela;
    _imgOriginal = imgOriginal;
    _iniRegioes  =  iniRegioes;

    /* GLUT */
    glutInit(argc, argv);

    /* inicialize o glut */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    /* crie uma janela */
    glutInitWindowSize (_tela->width, _tela->height);

    /* canto superior esquerdo da janela tem coordenada (X0,Y0) */ 
    glutInitWindowPosition(X0, Y0);

    /* desenhe a janela de nome EP2 MAC... */ 
    glutCreateWindow ("EP2 MAC0121 2019");

    /* 
     * registre as funções de callback 
     */
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc (myReshape);
    glutDisplayFunc (myDisplay);
    glutMouseFunc   (myMouse);

    
    /* myDisplay();  precisa? */

    /* mostre no shell as opcoes do programa */
    mostreUso();

    /* turn control over to glut */
    glutMainLoop();
}


/*-------------------------------------------------------------*/
/* 
 * F U N C O E S   P A R A   T R A T A R   O S   E V E N T O S 
 *
 *  CALLBACK == EVENT HANDLER
 */

/* *********************************************
   myReshape: funcao de callback
   Chamada quando a janela muda de tamanho       
*/

/* 
 * Chamada quando alguma tecla e pressionada
 */

static void 
myKeyboard (unsigned char key, int mx, int my)
{
    switch (key)
    {

        /* ------------------------------------------------------------ */
    case 'A': /* aumenta o limiar para determinar as bordas e regioes */
    case 'a':
        AVISO(graphic: aumentando limiar.);
        printf("AVISO: graphic: limiar atual = %d\n", _limiar);
        _limiar += 1;
        printf("AVISO: graphic: novo  limiar = %d\n", _limiar);
        AVISO(graphic: limiar aumentado.);
        break;

        /* ------------------------------------------------------------ */
    case 'b': /* pinte bordas da imagem   */
    case 'B': /* testa piteImagem e pinteRegioes(... ,TRUE) */

        if (_iniRegioes == NULL) 
        {
            AVISO(graphic: lista de regioes esta vazia.);
        }

        AVISO(graphic: chamando a funcao pinteImagem.);
        pinteImagem(_tela, BACK_GROUND);
        AVISO(graphic: voltei da funcao pinteImagem.);

        AVISO(graphic: chamando a funcao pinteRegioes/Bordas.);
        pinteRegioes(_tela, _iniRegioes, TRUE); 
        AVISO(graphic: voltei  da funcao pinteRegioes/Bordas.);

        myDisplay();
        break;

        /* ------------------------------------------------------------ */
    case 'd': /* diminua o limiar para determinar as bordas e regioes */
    case 'D':
        AVISO(graphic: diminuindo limiar.);
        printf("AVISO: graphic: limiar atual = %d\n", _limiar);
        _limiar -= 1;
        printf("AVISO: graphic: novo  limiar = %d\n", _limiar);
        AVISO(graphic: limiar diminuido.);
        break;

        /* ------------------------------------------------------------ */  
    case 'g': /* grave imagem corrente em um arquivo no formato ppm */
    case 'G': /* testa graveImagem() */
        AVISO(graphic: chamando a funcao graveImagem.);
        graveImagem(_tela);
        AVISO(graphic: voltei da funcao graveImagem.);
        break;

        /* ------------------------------------------------------------ */
    case 'l': /* limpa tela */
    case 'L': /* testa pinteImagem */
        AVISO(graphic: chamando a funcao pinteImagem.);
        pinteImagem(_tela, BACK_GROUND);
        AVISO(graphic: voltei da funcao pinteImagem.);

        myDisplay();
        break;

        /* ------------------------------------------------------------ */
    case 'o': /* imagem corrente passa a ser a original */
    case 'O': /* testa copieImagem */
        /* a gambiarra e para nao perdermos os ponteiros de cada 
           pixel para a celula da regiao que ele pertence */
        copiePonteirosRegiao(_imgOriginal, _tela); 

        AVISO(graphic: chamando a funcao copieImagem.);
        copieImagem(_tela, _imgOriginal);
        AVISO(graphic: voltei  da funcao copieImagem.);

        myDisplay();
        break;

        /* ------------------------------------------------------------ */
    case 'r': /* pinte todas as regioes da imagem, bordas ou nao */
    case 'R': /* testa pinteImagem e pinteRegioes(..., FALSE) */
        if (_iniRegioes == NULL) 
        {
            AVISO(graphic: lista de regioes vazia.);
        }

        AVISO(graphic: chamando a funcao pinteImagem.);
        pinteImagem(_tela, BACK_GROUND);
        AVISO(graphic: voltei  da funcao pinteImagem.);
	  
        AVISO(graphic: chamando a funcao pinteRegioes.);
        pinteRegioes(_tela, _iniRegioes, FALSE);
        AVISO(graphic: voltei da funcao pinteRegioes.);
 
        myDisplay();
        break;

        /* ------------------------------------------------------------ */
    case 's': /* segmente a imagem __corrente__ nao a original */
    case 'S': /* testa freeRegioes, segmenteImagem e pinteRegioes */ 
        /* primeiro vamos liberar a memoria alocada pela listas
           de regioes */

        if (_iniRegioes == NULL)
        {
            AVISO(graphic: lista de regioes vazia.);
        }
        else
        {
            AVISO(graphic: chamando a funcao freeRegioes.);
            freeRegioes(_iniRegioes); 
            AVISO(graphic: voltei  da funcao freeRegioes.);
            _iniRegioes = NULL;
        }
        
        AVISO(graphic: chamando a funcao segmenteImagem.);
         _iniRegioes = segmenteImagem(_tela, _limiar);
        AVISO(graphic: voltei  da funcao segmenteImagem.);

        if (_iniRegioes == NULL)
        {
            AVISO(graphic: lista de regioes vazia.);
        }

        AVISO(graphic: chamando a funcao pinteRegioes.);
        pinteRegioes(_tela, _iniRegioes, FALSE);
        AVISO(graphic: voltei da funcao pinteRegioes.);

        myDisplay();
        break;


        /* ------------------------------------------------------------ */
    case 'x': /* abandona a execucao do programa  */
    case 'X': /* testa quit */
        /* gostaria de fazer 'cleanup' do glut...
           freeglut parece apresentar algumas opcoes para isso ..
 
           http://www.lighthouse3d.com/cg-topics/glut-and-freeglut/
        */
        AVISO(graphic: chamando a funcao quit.);
        quit(_tela, _imgOriginal, _iniRegioes);
        AVISO(graphic: Hmmm sua funcao quit nao encerrou a execucao...);
        AVISO(graphic: Eu mesmo vou terminar a execucao.);
        exit(EXIT_SUCCESS); 
        break; /* superfluo, nao chega aqui */ 
 
    default:
        break;
    }

    if (key != '\n') /* este if evita que a mensagem fique "soluçando"... */
    { 
        mostreUso();
    }
}


/*-------------------------------------------------------------*/
/* 
 * Chamada quando ocorre um clique na janela
 */

static void 
myMouse(int b, int s, int col, int lin)
{
  
    if (b == GLUT_LEFT_BUTTON /*  b indicates the button */
        && s == GLUT_DOWN) /* button pressed */
    {   
        /* troque a cor da regiao do pixel na posicao [lin][col]*/
        AVISO(graphic: chamando a funcao repinteRegiao.);
        repinteRegiao(_tela, col, lin, cores[_iCor]); 
        AVISO(graphic: voltei da funcao repinteRegiao.);
        _iCor = (_iCor+1) % NUM_CORES;

        myDisplay();
        mostreUso();
    }
    else if (b == GLUT_RIGHT_BUTTON /*  b indicates the button */
        && s == GLUT_DOWN) /* button pressed */
    {
        /* troque a cor de _todos_ os pixels que estao em regios que
           tem a mesma cor que o pixel [lin][col] */
        AVISO(graphic: chamando a funcao repinteRegioes.);
        repinteRegioes(_tela, _iniRegioes, col, lin, cores[_iCor]); 
        AVISO(graphic: voltei da funcao repinteRegioes.);
        _iCor = (_iCor+1) % NUM_CORES;

        myDisplay();
        mostreUso();
    }
  
}

/*-------------------------------------------------------------*/
/* 
 * chamada quando a janela precisa ser desenhada 
 */

static void 
myDisplay(void)
{
    int col, lin;
    /* GLubyte cor[3]; */

#ifdef DEBUG
    printf("Entrei myDisplay (%d,%d)\n",_tela->width, _tela->height);
#endif
  
    glBegin(GL_POINTS);
    for (lin = 0; lin < _tela->height; lin++) 
    {
        for (col = 0; col < _tela->width; col++) 
        {
            Pixel pixel = getPixel(_tela, col, lin);
            glColor3ubv(pixel.cor);
            /* pinte o pixel [lin][col*/
            glVertex2f(col, _tela->height-lin-1); 
        }
    }
    glEnd();

    /* mostra o buffer */
    glutSwapBuffers();  
}

/*-------------------------------------------------------------*/
/* 
 * Chamada quando a janela muda de tamanho       
 */
static void 
myReshape(int col, int lin)
{
#ifdef DEBUG
    AVISO(Entrei myReshape);
#endif
    glViewport (0, 0, col, lin);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* map drawing area to viewport */
    gluOrtho2D(0, col, 0, lin); 
    glMatrixMode(GL_MODELVIEW);

    /* request redisplay */
    glutPostRedisplay(); 
}



/*-------------------------------------------------------------*/
static void
mostreUso()
{
    fprintf(stdout, "\n" 
            "Tecle:  'a' para (a)umentar o limiar das bordas\n"
            "        'b' para mostrar as (b)ordas (pinteImagem, pinteRegioes)\n"
            "        'd' para (d)iminuir o limiar das bordas\n"
            "        'g' para (g)ravar a imagem atual em um arquivo (graveImagem)\n"
            "        'l' para (l)impar a tela (pinteImagem)\n"
            "        'o' para mostrar a imagem (o)riginal (copieImagem)\n"
            "        'r' para mostrar as (r)egioes (pinteImagem, pinteRegioes)\n"
            "        's' para (s)egmentar a imagem (freeRegioes, segmenteImagem, pinteRegioes)\n");

    fprintf(stdout,
            "        'x' para e(x)it (quit)\n"
            "Clique: em um pixel com \n"
            "         botao esquerdo para alterar a cor da regiao (repinteRegiao)\n" 
            "         botao direito para alterar a cor (repinteRegioes).\n\n"); 
}


static void  
copiePonteirosRegiao(Imagem *destino, Imagem *origem)
{
    int lin, col;
    
    for (lin = 0; lin < origem->height; lin++)
    {
        for (col = 0; col < origem->width; col++)
        {
            destino->pixel[lin][col].regiao = origem->pixel[lin][col].regiao;
        }
    }

}


#undef _GRAPHIC_C


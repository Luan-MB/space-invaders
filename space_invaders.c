/* Trabalho: Space Invaders     |    Disicplina: Programacao I     */
/* Aluno: Luan Machado Bernardt     |     GRR20190363     |     Turma: c     */

#include <stdio.h>
#include "lib_lista_si.h"
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

/* Inicializacao de todos os elementos do jogo */

/* Tipos:
 
 * 0 = Sentinela	
 * 1 = Alien1
 * 2 = Alien2
 * 3 = Alien3
 * 4 = Barreira1
 * 5 = Barreira2
*/

void inicializa_jogo (t_game *g, int nlin, int ncol) {

	t_elem *ini, *fim;
	int i, j, k;
	
	ini = (t_elem *) malloc (sizeof(t_elem));
	fim = (t_elem *) malloc (sizeof(t_elem));

	g->ini = ini;
	g->ini->prox = g->fim;
	g->ini->prev = NULL;
	g->fim = fim;
	g->fim->prev = g->ini;
	g->fim->prox = NULL;
	g->ini->tipo = 0;
	g->fim->tipo = 0;

	
	t_elem* new_elem;

/* Inicializacao da nave-mae */

	new_elem = (t_elem *) malloc (sizeof(t_elem));
	g->n_mae = new_elem;
	insere_elem(g->n_mae,g);
	g->n_mae->pos_x = 1;
	g->n_mae->pos_y = 3;
	g->n_mae->estado = 0;
	
/* Inicialização sentinela aliens */

	new_elem = (t_elem *) malloc (sizeof(t_elem));
	g->aliens = new_elem;
	insere_elem(g->aliens,g);
	g->aliens->tipo = 0;

/* Inicializacao dos aliens */
	
	int linha = 1;
	
	for (i=0;i<11;i++) {
	
		new_elem = (t_elem *) malloc (sizeof(t_elem));
		new_elem->estado = 1;
		new_elem->pos_x = (2 + 7*i);
		new_elem->pos_y = (g->n_mae->pos_y + 4*linha) - 1;
		new_elem->tipo = 1;
		insere_elem(new_elem,g);
	}
	linha++;

	for (j=0;j<2;j++) {
		for (i=0;i<11;i++) {

			new_elem = (t_elem *) malloc (sizeof(t_elem));
			new_elem->estado = 1;
			new_elem->pos_x = (1 + 7*i);
			new_elem->pos_y = (g->n_mae->pos_y + 4*linha) - 1;
			new_elem->tipo = 2;
			insere_elem(new_elem,g);
		}
		linha++;
	}
	
	for (j=0;j<2;j++) {
		for (i=0;i<11;i++) {

			new_elem = (t_elem *) malloc (sizeof(t_elem));
                        new_elem->estado = 1;
                        new_elem->pos_x = (1 + 7*i);
                        new_elem->pos_y = (g->n_mae->pos_y + 4*linha) - 1;
                        new_elem->tipo = 3;
                        insere_elem(new_elem,g);
                }
                linha++;
        }

/* Inicializacao das barreiras */

	new_elem = (t_elem *) malloc (sizeof(t_elem));
	g->barreira = new_elem;
	insere_elem(g->barreira,g);
	g->barreira->tipo = 0;

	for (i=0;i<4;i++) {
			 
		new_elem = (t_elem *) malloc (sizeof(t_elem));
		new_elem->pos_y = g->n_mae->pos_y+28;
		new_elem->pos_x = 16 + 21*i;
		new_elem->estado = 1;
		new_elem->tipo = 4;
		insere_elem(new_elem,g);
		for (k=1;k<=3;k++) {

			new_elem = (t_elem*) malloc (sizeof(t_elem));
			new_elem->pos_y = g->n_mae->pos_y+28;
			new_elem->pos_x = 16+21*i+k;
			new_elem->tipo = 5;
			new_elem->estado = 1;
			insere_elem(new_elem,g);
		}
		new_elem = (t_elem *) malloc (sizeof(t_elem));
                new_elem->pos_y = g->n_mae->pos_y+28;
                new_elem->pos_x = 16 + 21*i+4; 
                new_elem->estado = 1;
                new_elem->tipo = 4;
                insere_elem(new_elem,g);
		
		new_elem = (t_elem *) malloc (sizeof(t_elem));
                new_elem->pos_y = g->n_mae->pos_y+29;
                new_elem->pos_x = 15 + 21*i;
                new_elem->estado = 1;
                new_elem->tipo = 4;
                insere_elem(new_elem,g);
		
		for (k=1;k<=5;k++) {

                        new_elem = (t_elem*) malloc (sizeof(t_elem));
                        new_elem->pos_y = g->n_mae->pos_y+29;
                        new_elem->pos_x = 15+21*i+k;
                        new_elem->tipo = 5;
                        new_elem->estado = 1;
                        insere_elem(new_elem,g);
                }
		new_elem = (t_elem *) malloc (sizeof(t_elem));
                new_elem->pos_y = g->n_mae->pos_y+29;
                new_elem->pos_x = 15 + 21*i+6;
                new_elem->estado = 1;
                new_elem->tipo = 4;
                insere_elem(new_elem,g);	
	
		for (j=0;j<2;j++) {
			new_elem = (t_elem *) malloc (sizeof(t_elem));
                	new_elem->pos_y = g->n_mae->pos_y+30;
                	new_elem->pos_x = ((15+j) + (21*i));
                	new_elem->estado = 1;
                	new_elem->tipo = 5;
                	insere_elem(new_elem,g);
		}
		for (j=0;j<2;j++) {
			new_elem = (t_elem *) malloc (sizeof(t_elem));
                        new_elem->pos_y = g->n_mae->pos_y+30;
                        new_elem->pos_x = ((20+j) + (21*i));
                        new_elem->estado = 1;
                        new_elem->tipo = 5;
                        insere_elem(new_elem,g);
		}
	}

/* Inicializacao do canhao */

	new_elem = (t_elem *) malloc (sizeof(t_elem));
	g->fim->prev->prox = new_elem;
	new_elem->prev = g->fim->prev;
	g->fim->prev = new_elem;
	new_elem->prox = g->fim;
	new_elem->pos_x = 1;
	new_elem->pos_y = 35;
	new_elem->estado = 1;
	g->cannon = new_elem;

/* Inicializacao dos projeteis */

	new_elem = (t_elem *) malloc (sizeof(t_elem));
	g->fim->prev->prox = new_elem;
	new_elem ->prev = g->fim->prev;
	g->fim->prev = new_elem;
	new_elem->prox = g->fim;
	new_elem->estado = 0;
	g->tiro = new_elem;

	new_elem = (t_elem *) malloc (sizeof(t_elem));
	g->fim->prev->prox = new_elem;
        new_elem ->prev = g->fim->prev;
        g->fim->prev = new_elem;
        new_elem->prox = g->fim;
        new_elem->estado = 0;
        g->bomba = new_elem;

}

/* Funcao que move os os aliens levando em conta a colisao com as bordas da tela */

void move_aliens (t_game* g) {

	t_elem* elem;
	int wall = 0;
	
	if (g->aliens->prox->pos_y % 2 == 0) {
		for (elem=g->aliens->prox;elem!=g->barreira;elem=elem->prox) {
			if (elem->estado == 1) {
				if (elem->tipo == 1) {
					if ((98 - elem->pos_x) == 3) {
						wall = 1;
						break;
					} 
				} else if ((elem->tipo == 2) || (elem->tipo == 3)) {
					if ((98 - elem->pos_x) == 4) {
						wall = 1;
						break;
					}	
				}
			}
		}
		if (wall == 1)
			for (elem=g->aliens->prox;elem!=g->barreira;elem=elem->prox)
				elem->pos_y++;
		else
			for (elem=g->aliens->prox;elem!=g->barreira;elem=elem->prox)
				elem->pos_x++;
	} else {
		for (elem=g->aliens->prox;elem!=g->barreira;elem=elem->prox) {
			if (elem->estado == 1) {
				if (elem->tipo == 1) {
					if ((1 - elem->pos_x) == -1) {
						wall = 1;
						break;
					}
				 } else if ((elem->tipo == 2) || (elem->tipo == 3)) {
					if ((1 - elem->pos_x) == 0) {
						wall = 1;
						break;
					}	
				}
			}
		}
		if (wall == 1) { 	
				for (elem=g->aliens->prox;elem!=g->barreira;elem=elem->prox)
					elem->pos_y++;
		} else
			for (elem=g->aliens->prox;elem!=g->barreira;elem=elem->prox)
				elem->pos_x--;
	}
}

void atira (t_game* g) {

	t_elem *tiro = g->tiro;

	if (tiro->estado == 0) {
		tiro->estado = 1;	
		tiro->pos_y = g->cannon->pos_y-1;
		tiro->pos_x = g->cannon->pos_x+2;
	}
}

void solta_bomba (t_game *g) {

	t_elem *bomba = g->bomba;
	t_elem *p = g->barreira->prev;
	t_elem *p_acima;
	int alien, i;
	int linha = 2;

	if (bomba->estado == 0) {
		alien = (rand() % 11);
		for (i=0;i<alien;i++)
			p = p->prev;
		if (p->estado == 1) {
			bomba->estado = 1;
			bomba->pos_y = p->pos_y+3;
			bomba->pos_x = p->pos_x+2;
		} else {
			p_acima = (t_elem *) malloc (sizeof(t_elem));
			p_acima->estado = 0;
			while ((p_acima->estado == 0) && (linha <= 5)) {
				for (i=0;i<11;i++)
					p = p->prev;
				p_acima->estado = p->estado;
				linha++;
			}
			if (p_acima->estado == 1) {
				bomba->estado = 1;
				bomba->pos_y = p->pos_y+3;
				bomba->pos_x = p->pos_x+2;
			}
			free(p_acima);
		}
	}	
}

void move_cannon (t_elem* cannon, int ch, t_game *g) {

	switch(ch) {
	
		case ' ':
			atira(g);
			break;
		case KEY_LEFT:
			if (cannon->pos_x > 1)
				cannon->pos_x -= 1;
			break;
		case KEY_RIGHT:
			if (cannon->pos_x < 94)
				cannon->pos_x += 1;
			break;
	}
}

void move_tiro (t_game *g) {

	if (g->tiro->pos_y-1 > 0)
		g->tiro->pos_y += -1;
	else
		g->tiro->estado = 0;
}

void move_bomba (t_game *g) {

	if (g->bomba->pos_y < 37)
		g->bomba->pos_y++;
	else
		g->bomba->estado = 0;
}

/* Funcoes de colisao para os elementos do jogo */

int colisao_tiro (t_game *g, int *pontos, int *spd) {


	t_elem *p;

	if (g->tiro->estado == 1) {
		for (p=g->n_mae;p!=g->cannon;p=p->prox) {
			if (p->estado == 1) {
				if (p->tipo == 1) {
					if (((p->pos_x - g->tiro->pos_x) > -3) && ((p->pos_x - g->tiro->pos_x <= 0)))
						if ((p->pos_y - g->tiro->pos_y) == -2) {
							p->estado=0;
							*pontos += 200;
							*spd += 2;
							return 1;
						}	
				} else if ((p->tipo == 2) || (p->tipo == 3)) {
					if (((p->pos_x - g->tiro->pos_x) > -5) && ((p->pos_x - g->tiro->pos_x <= 0)))
                                                if ((p->pos_y - g->tiro->pos_y) == -2) {
                                                        p->estado=0;
                                                        *pontos += 150;
							*spd += 1;
							return 1;
                                                }
				} else if ((p->tipo == 4) || (p->tipo == 5)) {
				       if ((p->pos_x - g->tiro->pos_x) == 0)
                                                if ((p->pos_y - g->tiro->pos_y) == 0) {
                                                        p->estado=0;
							return 1;
                                                }	
				} else if (p == g->n_mae) {
					if (((p->pos_x - g->tiro->pos_x) > -9) && ((p->pos_x - g->tiro->pos_x <= 0)))
						if ((p->pos_y - g->tiro->pos_y) == -2) {
                                                        p->estado=0;
                                                        *pontos += 1000;
							*spd += 10;
							return 1;
						}
				}
			}
		}
		return 0;
	}
	return 0;
}

int colisao_bomba (t_game *g) {

	t_elem *p = g->barreira;

	if (g->bomba->estado == 1) {
		while (p != g->cannon->prox) {
			if (p->estado == 1) {
				if ((p->tipo == 4) || (p->tipo == 5)) {
					if (((p->pos_x - g->bomba->pos_x) == 0) && ((p->pos_y - g->bomba->pos_y) == 1 )) {
						p->estado = 0;
						return 1;
					}
				} else if (p == g->cannon) {
					if (((p->pos_x - g->bomba->pos_x) < 0 ) && (p->pos_x - g->bomba->pos_x) > -4) {
						if ((p->pos_y - g->bomba->pos_y) == 0) {
							p->estado = 0;
							return 1;
						}
					} else if (((p->pos_x - g->bomba->pos_x) <= 0) && ((p->pos_x - g->bomba->pos_x) >= -4)) {
						if ((p->pos_y+1 - g->bomba->pos_y) == 0) {
							p->estado = 0;
							return 1;
						}
					}	
				}
			}
			p = p->prox;
		}
		return 0;
	}
	return 0;
}
		
void colisao_barreira (t_game *g) {

	t_elem *p, *b;

	for (p=g->aliens->prox;p!=g->barreira;p=p->prox) {
		if (p->estado == 1) {
			for (b=g->barreira->prox;b!=g->cannon;b=b->prox) {
				if (b->estado == 1) {
					if ((p->tipo == 2) || (p->tipo == 3)) {
						if ((p->pos_y + 2) == (b->pos_y))
							if (((p->pos_x - b->pos_x) <= 0) && ((p->pos_x - b->pos_x) >= -4))
								b->estado = 0;
					}
					else if (p->tipo == 1) {
						if ((p->pos_y + 2) == (b->pos_y))
							if (((p->pos_x - b->pos_x) <= 0) && ((p->pos_x - b->pos_x) >= -2))
								b->estado = 0;
					}
				}
			}
		}
	}
} 

/* Funcao que analisa se o jogador perdeu */

int fim_game (t_game *g) {

	t_elem *p;

	for (p=g->aliens->prox;p!=g->barreira;p=p->prox) {
		if (p->estado == 1) {
			if (p->pos_y + 2 == g->cannon->pos_y)
				return 1;
		}
	}
	if (g->cannon->estado == 0)
		return 1;
	return 0;
}

/* Funcao que confere se todos os aliens foram mortos */

int all_dead (t_game *g) {

	t_elem *p;

	for (p=g->aliens->prox;p!=g->barreira;p=p->prox)
		if (p->estado == 1)
			return 0;
	return 1;
}

/* Funcao que revive os aliens na posicao original e recomeca o jogo com a velocidade atual */

void reseta_aliens (t_game *g) {

	int i, j;
	int linha = 1;
	t_elem *p = g->aliens->prox;

        for (i=0;i<11;i++) {

                p->estado = 1;
                p->pos_x = (2 + 7*i);
                p->pos_y = ((g->n_mae->pos_y + 4*linha) - 1);
        	p=p->prox;
	}
        linha++;

        for (j=0;j<2;j++) {
                for (i=0;i<11;i++) {

                        p->estado = 1;
                        p->pos_x = (1 + 7*i);
                        p->pos_y = ((g->n_mae->pos_y + 4*linha) - 1);
                	p=p->prox;
		}
                linha++;
        }

        for (j=0;j<2;j++) {
                for (i=0;i<11;i++) {

                        p->estado = 1;
                        p->pos_x = (1 + 7*i);
                        p->pos_y = ((g->n_mae->pos_y + 4*linha) -1 );
                	p=p->prox;
		}
                linha++;
        }
}

/* Funcao que tem a chance de dar spawn a nave mae */

void spawn_nmae (t_game *g) {

	int spawn = (rand() % 100);

	if (g->n_mae->estado == 0) { 
		if (spawn % 23 == 0) {
			g->n_mae->estado = 1;
			g->n_mae->pos_x = 1;
		}
	}
}

void move_nmae (t_game *g) {

	if (g->n_mae->estado == 1) {
		if (98 - g->n_mae->pos_x == 9) {
			g->n_mae->estado = 0;
			g->n_mae->pos_x = 1;
			return;
		}
		g->n_mae->pos_x++;
	}
}

/* Sprites dos elementos */

#define CANNON_TOP (" /^\\\0")
#define CANNON_BOT ("H-+-H\0")

#define N_MAE_TOP (" /MMMMM\\\0")
#define N_MAE_MID ("<+-+-+-+>\0")
#define N_MAE_BOT (" \\/'-'\\/\0")

#define ALIEN3_TOP ("|---|\0")
#define ALIEN3_MID ("|+++|\0")
#define ALIEN3_BOT ("_/-\\_\0")
#define ALIEN3_MOV ("_|-|_\0")

#define ALIEN2_TOP (".v_v.\0")
#define ALIEN2_MID ("{WMW}\0")
#define ALIEN2_BOT (" (+)\0")
#define ALIEN2_MOV (" )+(\0")

#define ALIEN1_TOP (" A\0")
#define ALIEN1_MID ("<+>\0")
#define ALIEN1_BOT (")^(\0")
#define ALIEN1_MOV ("(^)\0")

#define EXPLOSION_TOP (" \\'/\0")
#define EXPLOSION_MID ("- + -\0")
#define EXPLOSION_BOT (" /'\\\0")

void print_game (WINDOW** game_scr, t_game* si, int mov) {

	t_elem* p;

	p = si->n_mae;
	if (p->estado == 1) {
		wmove(*game_scr,p->pos_y,p->pos_x);
		waddstr(*game_scr,N_MAE_TOP);
		wmove(*game_scr,p->pos_y+1,p->pos_x);
       		waddstr(*game_scr,N_MAE_MID);
		wmove(*game_scr,p->pos_y+2,p->pos_x);
       		waddstr(*game_scr,N_MAE_BOT);
	}
	for (p=si->aliens;p!=si->barreira;p=p->prox) {
		if (p->estado == 1) {
			if (p->tipo == 3) {
				wmove(*game_scr,p->pos_y,p->pos_x);
				waddstr(*game_scr,ALIEN3_TOP);
				wmove(*game_scr,p->pos_y+1,p->pos_x);
				waddstr(*game_scr,ALIEN3_MID);
				wmove(*game_scr,p->pos_y+2,p->pos_x);
				if (mov == 0)
					waddstr(*game_scr,ALIEN3_BOT);
				else 
					waddstr(*game_scr,ALIEN3_MOV);
			} else if (p->tipo == 2) {
				wmove(*game_scr,p->pos_y,p->pos_x);
                                waddstr(*game_scr,ALIEN2_TOP);
                                wmove(*game_scr,p->pos_y+1,p->pos_x);
                                waddstr(*game_scr,ALIEN2_MID);
                                wmove(*game_scr,p->pos_y+2,p->pos_x);
                                if (mov == 0) 
					waddstr(*game_scr,ALIEN2_BOT);
				else 
					waddstr(*game_scr,ALIEN2_MOV);
			} else if (p->tipo == 1) {
                	        wmove(*game_scr,p->pos_y,p->pos_x);
                 	        waddstr(*game_scr,ALIEN1_TOP);
                 	        wmove(*game_scr,p->pos_y+1,p->pos_x);
                        	waddstr(*game_scr,ALIEN1_MID);
                        	wmove(*game_scr,p->pos_y+2,p->pos_x);
                        	if (mov == 0)
					waddstr(*game_scr,ALIEN1_BOT);
				else 
					waddstr(*game_scr,ALIEN1_MOV);
			}
		} else if (p->estado == 2) {
			wmove(*game_scr,p->pos_y,p->pos_x);
			waddstr(*game_scr,EXPLOSION_TOP);
			wmove(*game_scr,p->pos_y+1,p->pos_x);
			waddstr(*game_scr,EXPLOSION_MID);
			wmove(*game_scr,p->pos_y+2,p->pos_x);
			waddstr(*game_scr,EXPLOSION_BOT);
		}
	}
	
	for (p=si->barreira->prox;p!=si->cannon;p = p->prox) {
		if (p->estado == 1) {
			if (p->tipo == 4) {
				wmove(*game_scr,p->pos_y,p->pos_x);
				waddch(*game_scr,'A');
			} else {
				wmove(*game_scr,p->pos_y,p->pos_x);
				waddch(*game_scr,'H');
			}
		}
	}
	p = si->cannon;
	wmove(*game_scr,p->pos_y,p->pos_x);
       	waddstr(*game_scr,CANNON_TOP);
	wmove(*game_scr,p->pos_y+1,p->pos_x);
       	waddstr(*game_scr,CANNON_BOT);	
	
	p = si->tiro;
	if (p->estado == 1) {
		wmove(*game_scr,p->pos_y,p->pos_x);
		waddch(*game_scr,'!');
	}
	
	p = si->bomba;
	if (p->estado == 1) {
		wmove(*game_scr,p->pos_y,p->pos_x);
		waddch(*game_scr,'$');
	}
}

int main () {

	int nlin, ncol;

        initscr();
        getmaxyx(stdscr,nlin,ncol);
        if (ncol<100 || nlin<38) {
                printf("Tamanho do terminal insuficiente\n");
                endwin();
                return 0;
        }
	
	int win_lin = ((nlin-38)/2);
	int win_col = ((ncol-100)/2);
	t_game si;
	WINDOW *game_scr = newwin(38,100,win_lin,win_col);
	
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr,TRUE);
	keypad(stdscr,TRUE);
	curs_set(FALSE);
	inicializa_jogo(&si,win_lin,win_col);
	srand(time(NULL));
	refresh();
	
	int ch;
	int delay_tiro = 0;
	int delay_bomb = 0;
	int delay_alien = 0;
	int delay_nmae = 0;
	int mov = 0;
	int pontos = 0;
	int spd = 0;
	int wave = 0;
	
	while ((ch=getch()) != 'q') {
		if (! fim_game(&si)) {
			if (all_dead(&si)) {
				reseta_aliens(&si);
				wave++;
				delay_bomb = 0;
				werase(game_scr);
				wmove(game_scr,19,40);
				wprintw(game_scr,"NEXT WAVE INCOMING!");
				wrefresh(game_scr);
				sleep(3);
			}
			werase(game_scr);
			move_cannon(si.cannon,ch,&si);
			
/* A velocidade dos elementos equivale ao valor comparado ao seu respectivo delay x 5000 micro segundos (1 ciclo) 
 * Por exemplo a expressao (delay_tiro == 3) quer dizer que a cada 3 x 5000, ou seja 15000 micro segundos (3 ciclos) o tiro sera movido */

			if (delay_tiro == 3) {
				move_tiro(&si);
				if (colisao_tiro(&si,&pontos,&spd))
					si.tiro->estado = 0;
				delay_tiro = 0;
			}
			if (delay_nmae == 200) {
				spawn_nmae(&si);
				delay_nmae = 0;
			}
			if ((delay_nmae % 10) == 0)
				move_nmae(&si);
			if (delay_alien >= (100 - (spd/2))) {
				move_aliens(&si);
				colisao_barreira(&si);
				delay_alien = 0;
				if (mov == 0)
					mov++;
				else
					mov--;
			}
			if (delay_bomb == ((40) - wave*5)) {
				solta_bomba(&si);
				delay_bomb = 0;
			}		
			if (delay_bomb % (20 - (wave*5)) == 0) {
				move_bomba(&si);
				if (colisao_bomba(&si))
					si.bomba->estado = 0;
			}
			if (mov == 0)
				print_game(&game_scr,&si,0);
			else
				print_game(&game_scr,&si,1);
			wmove(game_scr,1,46);
			wprintw(game_scr,"%08d",pontos);
			wrefresh(game_scr);
			delay_tiro++;
			delay_alien++;
			delay_bomb++;
			delay_nmae++;
			usleep(5000);
		} else {
		werase(game_scr);
		wmove(game_scr,13,45);
		wprintw(game_scr,"FIM DE JOGO!");
		wmove(game_scr,14,38);
		wprintw(game_scr,"Sua pontuacao: %09d",pontos);
		wmove(game_scr,15,40);
		wprintw(game_scr,"Aperte 'Q' para sair");
		wrefresh(game_scr);
		}
	}
	destroi_lista(&si);
	delwin(game_scr);
	endwin();
	return 1;
}

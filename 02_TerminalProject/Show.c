#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define DX 3

struct item {
	char *sp;
	struct item *next;
};

void del_list (struct item *l)
{
	struct item *t = l;
	while ((l) != NULL)
	{
		free(l -> sp);
		t = l;
		(l) = (l) -> next;
		free(t);
	}
}


struct item *add_list(struct item *ls, char *buff)
{
	struct item *p, *q;
	p = malloc(sizeof(*p));
	p -> sp = buff;
	p -> next = NULL;
	if(ls == NULL)
	{
		ls = p;
	}else
	{
		q = ls;
		while(q -> next != NULL)
		{
			q = q -> next;
		}
		q -> next = p;
	}
	return ls;
}


int main(int argc, char **argv)
{
    if (argc < 2) {
		printf("No input file\n");
		exit(1);
	}

	struct item *list = NULL;
	char *buff;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Can't open file %s\n", argv[1]);
        exit(1);
    }

    WINDOW *win;
    
    initscr();
    noecho();
    cbreak();
    printw("File: %s", argv[1]);
    refresh();
    int winheight = LINES - 2 * DX;
    int winwidth = COLS - 2 * DX;
    win = newwin(winheight, winwidth, DX, DX);

    keypad(win, TRUE);
    scrollok (win, TRUE);
    box(win, 0, 0); 
    wmove(win, 1, 0); 

    buff = malloc(winwidth * sizeof(*buff));
	int tmp;
    while(fgets(buff, (winwidth - 1), fp)) {
		if (strchr(buff, '\n') == NULL) {
			buff[strlen(buff)] = '\n';
			while((tmp = fgetc(fp)) != '\n' && tmp != EOF) {}
		}
        list = add_list(list, buff);
        buff = malloc(winwidth * sizeof(*buff));
    }
	fclose(fp);

    struct item *cur_line = list;
    int i = 0;
    int key_pressed;
    while((i < (winheight - 3)) && cur_line) {
		wprintw(win," %s", cur_line -> sp);
		i++;
        cur_line = cur_line -> next;
	}
    box(win, 0, 0);

	i = 0;
    while((key_pressed = wgetch(win)) != 27) {
		if (key_pressed == ' ' && cur_line) {
			werase(win);
			wprintw(win, " \n");
			while((i < (winheight - 3)) && cur_line) {
				wprintw(win, " %s", cur_line -> sp);
				i++;
                cur_line = cur_line -> next;
			}
			i = 0;
		}
        box(win, 0, 0);
    }
    
    del_list(list);
    endwin();
	return 0;
}


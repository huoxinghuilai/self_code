#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

struct symbol *find_symbol(struct symbol *sb, char *p)
{
	struct symbol *s;
	s = sb->next;

	while (s != sb) {
		if (!strcmp(s->key, p)) {
			return s;
		}
		
		s = s->next;
	}

	return NULL;
}

int equ_api(struct symbol *sb, struct arg *argv)
{
	struct symbol *s, *tmp;
	s = sb->next;

	while (s != sb) {
		if (!strcmp(s->key, argv->res)) {
			if (tmp = find_symbol(sb, argv->d2)) {
				free(s->val);
				s->val = (char *)malloc(sizeof(strlen(tmp->val) + 1));
				memcpy(s->val, tmp->val, strlen(tmp->val));
				strcat(s->val, "\0");
				break;
			}
			break;
		}

		s = s->next;
	}
}

int add_api(struct symbol *sb, struct arg *argv)
{
	int tmp;
	int a = 0;
	char str[10] = {0};
	struct symbol *s, *s1, *tmp1, *tmp2;
        s = sb->next;

        tmp1 = find_symbol(sb, argv->d1);
	tmp2 = find_symbol(sb, argv->d2);
	a = atoi(tmp1->val) + atoi(tmp2->val);
	sprintf(str, "%d", a);

	while (s != sb) {
                if (!strcmp(s->key, argv->res)) {
                        if (s->val) {
                                free(s->val);
                                s->val = (char *)malloc(sizeof(strlen(str) + 1));
                                memcpy(s->val, &a, strlen(str));
                                strcat(s->val, "\0");
                        }
                        break;
                }

                s = s->next;
        }
	
	s1 = (struct symbol *)malloc(sizeof(struct symbol));

	s1->key = (char *)malloc(sizeof(strlen(argv->res) + 1));
	memcpy(s1->key, argv->res, strlen(argv->res));
	strcat(s1->key, "\0");

	s1->val = (char *)malloc(sizeof(strlen(str) + 1));
        memcpy(s1->val, str, strlen(str));
        strcat(s1->val, "\0");	

	s1->next = sb;
	s1->prev = sb->prev;
	sb->prev->next = s1;
	sb->prev = s1;

	return 0;
}

int sub_api(struct symbol *sb, struct arg *argv)
{
	return 0;
}

int mul_api(struct symbol *sb, struct arg *argv)
{
        return 0;
}

int div_api(struct symbol *sb, struct arg *argv)
{
        return 0;
}

int print_api(struct symbol *sb, struct arg *argv)
{
        struct symbol *s;
	s = sb->next;

	while (s != sb) {
		if (!strcmp(s->key, argv->d2)) {
			printf("execute result: %s->%s\n", s->key, s->val);
			break;
		}
		s = s->next;
	}
	
	return 0;
}

int execute(struct symbol *sb, struct opcode *opline)
{
	struct opcode *p;
	p = opline->next;

	while (p != opline) {
		if (!strcmp(p->op, "="))
			equ_api(sb, p->argv);
		else if (!strcmp(p->op, "+"))
			add_api(sb, p->argv);
		else if (!strcmp(p->op, "-"))
                        sub_api(sb, p->argv);
		else if (!strcmp(p->op, "*"))
                        mul_api(sb, p->argv);
		else if (!strcmp(p->op, "/"))
                        div_api(sb, p->argv);
		else if (!strcmp(p->op, "print"))
                        print_api(sb, p->argv);

		p = p->next;
	} 
}

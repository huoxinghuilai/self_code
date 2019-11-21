#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct va_list {
	char *str;
	struct va_list *next;
};

struct arg {
	char *res;
	char *d1;
	char *d2;
	struct arg *next;
	struct arg *prev;
};

struct opcode {
	char *op;
	struct arg *argv;
	struct opcode *next;
	struct opcode *prev;
};

struct symbol {
	char *key;
	char *val;
	struct symbol *next;
	struct symbol *prev;
};


int get_opline(FILE *fp, struct opcode *opline)
{
	int i = 0, start = 0;
	char buffer[100] = {0};
	struct va_list *list, *q;

	list = (struct va_list *)malloc(sizeof(struct va_list));
	
	while (1) {

		struct opcode *op;

                op = (struct opcode *)malloc(sizeof(struct opcode));
                op->argv = (struct arg *)malloc(sizeof(struct arg));

		fgets(buffer, 100, fp);
		if (feof(fp)) {
			break;
		}
		
		q = list;
		while (buffer[i] != '\n') {
			
			if (buffer[i] == ' ') {
				
				if (i - start) {
					
					struct va_list *p;
					p = (struct va_list *)malloc(sizeof(struct va_list));
					p->str = (char *)malloc(sizeof(i - start + 1));
					memcpy(p->str, &buffer[start], i - start);
					strcat(p->str, "\0");
					q->next = p;
					q = p;
					
					start = ++i;
				} else {
					start = ++i;
				}
			} else {
				i++;
			}
					
		}
		
		struct va_list *p;
		p = (struct va_list *)malloc(sizeof(struct va_list));
		p->str = (char *)malloc(sizeof(i - start + 1));
		memcpy(p->str, &buffer[start], i - start);
		strcat(p->str, "\0");
		q->next = p;

		q = list->next;
		while (q) {
			if (q->next) {
				if (!strcmp(q->next->str, "=")) {
					op->argv->res = (char *)malloc(sizeof(strlen(q->str) + 1));
					memcpy(op->argv->res, q->str, strlen(q->str));
					strcat(op->argv->res, "\0");
					q = q->next;
					continue;
				}
			
				if (!strcmp(q->next->str, "+") || !strcmp(q->next->str, "-") || !strcmp(q->next->str, "*") || !strcmp(q->next->str, "/")) {
                                	op->argv->d1 = (char *)malloc(sizeof(strlen(q->str) + 1));
                                	memcpy(op->argv->d1, q->str, strlen(q->str));
                                	strcat(op->argv->d1, "\0");
                                	q = q->next;
                                	continue;
                        	}
			}

			//这里的处理仅对c=a+b这类表达式进行处理。
			if (!strcmp(q->str, "=") || !strcmp(q->str, "print") || !strcmp(q->str, "+") || !strcmp(q->str, "-") || !strcmp(q->str, "*") || !strcmp(q->str, "/")) {
				if (op->op == NULL) {
					op->op = (char *)malloc(sizeof(strlen(q->str) + 1));
				} else if (op->op && !strcmp(op->op, "=")){
					free(op->op);
					op->op = (char *)malloc(sizeof(strlen(q->str) + 1));
				}

				memcpy(op->op, q->str, strlen(q->str));
				strcat(op->op, "\0");
				q = q->next;
				continue;
			}

			op->argv->d2 = (char *)malloc(sizeof(strlen(q->str) + 1));
			memcpy(op->argv->d2, q->str, strlen(q->str));
			strcat(op->argv->d2, "\0");
			q = q->next;
			continue;
		}
		
		op->next = opline;
		op->prev = opline->prev;
		opline->prev->next = op;
		opline->prev = op;

		i = 0;
		start = 0;
		list->next = NULL;
	}
}

int get_symbol(struct symbol *sb, struct opcode *opline)
{
	struct symbol *s;
	struct opcode *p;

	p = opline->next;
	while (p != opline) {
		if (!strcmp(p->op, "=")) {
			s = (struct symbol *)malloc(sizeof(struct symbol));
			
			s->key = (char *)malloc(sizeof(strlen(p->argv->res) + 1));
			memcpy(s->key, p->argv->res, strlen(p->op));
			strcat(s->key, "\0");

			s->val = (char *)malloc(sizeof(strlen(p->argv->d2) + 1));
			memcpy(s->val, p->argv->d2, strlen(p->argv->d2));
			strcat(s->val, "\0");

			s->next = sb;
			s->prev = sb->prev;
			sb->prev->next = s;
			sb->prev = s;
		}
		
		p = p->next;
	}
}

#include <stdio.h>
#include <stdlib.h>
//#include "parser.h"
#include "execute.h"

int main(int argc, char *argv[])
{
	FILE *fp;
	struct opcode *opline, *p;
	struct symbol *sb, *q;

	if (argc != 2) {
		printf("command line is wrong!\n");
		return -1;
	}

	fp = fopen(argv[1], "r");
	if (!fp) {
		printf("this execute file can't find!\n");
		return -1;
	}
	
	opline = (struct opcode *)malloc(sizeof(struct opcode));
	opline->next = opline;
	opline->prev = opline;

	get_opline(fp, opline);
	p = opline->next;

	printf("%8s %8s %8s %8s\n", "op", "res", "d1", "d2");
	while (p != opline) {
		printf("%8s %8s %8s %8s\n", p->op, p->argv->res, p->argv->d1, p->argv->d2);
		p = p->next;
	}
	printf("---------------------------------------\n");

	sb = (struct symbol *)malloc(sizeof(struct symbol));
	sb->next = sb;
	sb->prev = sb;
	get_symbol(sb, opline);
	q = sb->next;

	while (q != sb) {
		printf("%8s %8s\n", q->key, q->val);
		q = q->next;
	}
	printf("----------------------------------------\n");

	execute(sb, opline);

	return 0;
}

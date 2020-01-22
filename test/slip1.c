#include <stdio.h>
#include <string.h>

int main()
{
	char *word1 = "wo shi shui?";
	char word2[20][20];
    	char *flag1, *flag2;
	int n = 0;
	int i = 0;
	printf("%s\n", word1);
	flag1 = word1;
	flag2 = flag1;
	while ((*flag1) != '\0')
	{
		if((*flag1 == ' '))
		{
			strncpy(word2[i],flag2,n);
			printf("%s\n",word2[i]);
			word2[i][n]='\0';
			i++;
			flag2=flag2+n+1;
			n=0;
			flag1++;			
			continue;
		}
		n++;
		flag1++;
	}
	strncpy(word2[i],flag2,n);
	word2[i][n]='\0';
	printf("%s\n",word2[i]);
}

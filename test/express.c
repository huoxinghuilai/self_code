#include <stdio.h>
#include <math.h>

main()
{
	int i, j;
	char s[36][68];
	float x = 0.0, h = 3.14159265/18;
	for(i = 0; i < 36; i++)
	{
		s[i][0] = '|';
		s[i][67] = '\0';
		for(j = 1; j < 67; j++)
			s[i][j]=' ';
	}
	s[22][0] = '+';
	for(j = 1; j < 66; j++)
		s[22][j] = '-';
	s[22][66] = '>';
	s[23][66] = 'x';
	printf("exp(-x) * cos(x)\n   ^\n");
	for(j = 0; j < 64; j++)
	{
		i = (int)(22.5 - 22 * exp(-x / 6.0) * cos(x));
		s[i][j] = '*';
		x += h;
	}
	for(i = 0; i < 36; i++)
		printf("   %s\n", s[i]);
        
        return 0;
}


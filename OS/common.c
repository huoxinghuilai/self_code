volatile unsigned int *UART0DR = (unsigned int *)0x101f1000;

void print_uart0(char *s) {
    while (*s != '\0') {
        *UART0DR = (unsigned int)(*s);
        s++;
    }
}

int _strlen(char *str)
{
    int count = 0;

    while (*str++ != '\0') {
        count++;
    }

    return count;
}

int _memcpy(char *dst, char *src, int len)
{
    int i = 0;

    for (i; i <= len && *src != '\0'; i++) {
        *dst = *src;
        dst++; src++;
    }

    *dst = '\0';

    return i;
}

int _memset(char *src, int num, int len)
{
    while (len--) {
        src[len] = (char)num;
    }

    return 0;
}

int _itos(int num, char *str) {
    int num_tmp = num;
    char str_tmp[256];
    int i = 0;
    int k = 0;
    
    _memset(str_tmp, 0, 256);

    if (num_tmp == 0) {
        str[k++] = 48;

        return 0;
    }

    while (num_tmp) {
        str_tmp[i] = num_tmp % 10 + 48;
        num_tmp = num_tmp / 10;
        i++;
    }

    for (i = i - 1; i >= 0; i--) {
        str[k++] = str_tmp[i];
    }

    return 0;
}
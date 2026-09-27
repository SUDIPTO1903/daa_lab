#include <stdio.h>
#include <stdlib.h>

void dec2bin(int num, char *bin, int i)
{
    if (i < 0)
        return;
    bin[i] = (num % 2) + '0';
    dec2bin(num / 2, bin, i - 1);
}

int main(int argc, char *argv[])
{
    FILE *fin, *fout;
    int n, i, num;
    char bin[17], line[100];

    if (argc != 4)
    {
        printf("Usage: %s n source dest\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    fin = fopen(argv[2], "r");
    fout = fopen(argv[3], "w");

    for (i = 0; i < n; i++)
    {
        if (fscanf(fin, "%d", &num) != 1)
            break;
        bin[16] = '\0';
        dec2bin(num, bin, 15);
        fprintf(fout, "The binary equivalent of %d is %s\n", num, bin);
    }

    fclose(fin);
    fclose(fout);

    fout = fopen(argv[3], "r");
    while (fgets(line, 100, fout) != NULL)
        printf("%s", line);
    fclose(fout);

    return 0;
}

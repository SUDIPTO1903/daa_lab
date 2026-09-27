#include <stdio.h>

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main(int argc, char *argv[])
{
    FILE *fin, *fout;
    int a, b;
    char line[100];

    if (argc != 3)
    {
        printf("Usage: %s source dest\n", argv[0]);
        return 1;
    }

    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    while (fscanf(fin, "%d %d", &a, &b) == 2)
        fprintf(fout, "The GCD of %d and %d is %d\n", a, b, gcd(a, b));

    fclose(fin);
    fclose(fout);

    fout = fopen(argv[2], "r");
    while (fgets(line, 100, fout) != NULL)
        printf("%s", line);
    fclose(fout);

    return 0;
}

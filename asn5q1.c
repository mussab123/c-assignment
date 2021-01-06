// Mussab Assefa
// 11219197
// maa392


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXLEN 500

/**
 * counts the number of columns
 * @param s character array
 * @return counts
 */
int getColCount(char *s)
{
    int count = 1;
    for (char *t = s; *t != '\0'; t++)
    {
        if (*t == ' ')
        {
            count++;
        }
    }
    return count;
}



char *getOutputFile(char *s)
{
    int c = strlen(s) - 1;
    char *res = malloc((c + 10) * sizeof(char));
    int pos = c;
    int i = c;
    while (pos >= 0)
    {
        if (s[pos] == '.')
        {
            break;
        }
        pos--;
    }
    if (pos == -1)
    {
        pos = c + 1;
    }
    i = 0;
    while (i < pos)
    {
        res[i] = s[i];
        i++;
    }

    res[i++] = '-';
    res[i++] = 'r';
    res[i++] = 'e';
    res[i++] = 'v';
    res[i++] = 'i';
    res[i++] = 's';
    res[i++] = 'e';
    res[i++] = 'd';

    while (pos <= c)
    {
        res[i++] = s[pos++];
    }
    res[i] = '\0';
    return res;
}



int main(int argc, char *argv[])
{
    FILE *file1, *file2, *out1, *out2;
    int c1 = 0, c2 = 0;
    char t1[MAXLEN], t2[MAXLEN];
    if (argc < 3)
    {
        printf("Please enter two filenames\n");
        exit(1);
    }

    if ((file1 = fopen(argv[1], "r")) == NULL)
    {
        printf("Error! opening file\n");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    if ((file2 = fopen(argv[2], "r")) == NULL)
    {
        printf("Error! opening file\n");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    out1 = fopen(getOutputFile(argv[1]), "w");

    out2 = fopen(getOutputFile(argv[2]), "w");

    fscanf(file1, "%[^\n]", t1);
    fscanf(file2, "%[^\n]", t2);

    c1 = getColCount(t1);
    c2 = getColCount(t2);

    //Output headers
    fprintf(out1, "%s\n", t1);
    fprintf(out2, "%s\n", t2);

    while (!feof(file1))
    {
        for (int i = 1; i < c1; i++)
        {
            fscanf(file1, "%s", t1);
            fprintf(out1, "%s ", t1);
        }

        for (int i = 1; i < c2; i++)
        {
            fscanf(file2, "%s", t2);
            fprintf(out2, "%s ", t2);
        }
        fscanf(file1, "%s", t1);
        fscanf(file2, "%s", t2);
        fprintf(out1, "%s\n", t2);
        fprintf(out2, "%s\n", t1);
    }

    fclose(file1);
    fclose(file2);
    fclose(out1);
    fclose(out2);
}
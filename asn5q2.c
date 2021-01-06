//
// Mussab Assefa
// 11219197
// maa392
//


#include <stdio.h>
#include <stdlib.h>


/**
 * Counts the lines of the given pointer
 * @param fruit a pointer of  fruit-revised.txt
 * @param f_count counts the number of lines in fruit-revised.txt
 * @param dairy a pointer of dairy-revised.tx
 * @param d_count counts the number of lines in dairy-revised.txt
 */
void count_line(FILE *fruit, int *f_count, FILE *dairy, int *d_count)
{
    char buf[100];
    char heading[100];
    char heading1[20];
    char heading2[20];
    char heading3[20];
    char heading4[20];


    if(fruit == NULL){
        printf("couldn't open file");
    }

    if(dairy == NULL){
        printf("couldn't open file");
    }


    int c;


    fscanf(fruit, "%s %s %s %s %s", heading, heading1, heading2, heading3, heading4);

    *f_count = *f_count + 1;

    while(!feof(fruit)){
        fgets(buf, sizeof(buf), fruit);
        for(c = getc(fruit); c!= EOF; c = getc(fruit))
            if(c == '\n')
                *f_count = *f_count + 1;
    }




    fscanf(dairy, "%s %s %s %s %s", heading, heading1, heading2, heading3, heading4);

    *f_count = *f_count + 1;


    while(!feof(dairy)){
        fgets(buf, sizeof(buf), dairy);
        for(c = getc(dairy); c!= EOF; c = getc(dairy))
            if(c == '\n')
                *d_count = *d_count + 1;
    }



    fclose(fruit);
    fclose(dairy);
}

/**
 * reads the pointer and calculates the total sales of each individual products in the column
 * @param fruit pointer to fruit.txt
 * @param dairy pointer to dairy.txt
 * @param label two dimensional array to hold labels of the fruits and dairy
 * @param data the values of the fruits and dairy
 * @param c_fruit counts the fruits
 * @param c_dairy counts the dairy
 */
void read(FILE *fruit, FILE *dairy, char label[][25], int data[][6],
          int c_fruit, int c_dairy)
{

    int a, b, c;
    int all;
    char week_d[20];


    fscanf(fruit, "%s", week_d);


    for(a = 0; a < 5; a++)
        fscanf(fruit, "%s", label[a]);


    fscanf(dairy, "%s", week_d);

    for(a = 5; a < 10; a++)
        fscanf(dairy, "%s", label[a]);

    for(a = 0; a < c_fruit; a++)
    {
        fscanf(fruit, "%s", week_d);

        for(b = 0; b < 5; b++)
            fscanf(fruit, "%d", &data[a][b]);
    }

    for(b = 0; b < c_fruit; b++ )
    {
        all = 0;
        for(c = 0; c < 5; c++)
            all += data[c][b];

        data[b][5] = all;
    }

    for(a = c_fruit; a < (c_fruit + c_dairy); a++)
    {
        fscanf(dairy, "%s", week_d);

        for(int d = 0; d < 5; d++)
            fscanf(dairy, "%d", &data[a][d]);
    }

    int cur = c_dairy;


    for(c = 0; c < 5; c++)
    {
        all = 0;
        for(b = c_fruit-1; b < (c_fruit + c_dairy); b++)
            all += data[b][c];
        data[cur++][5] = all;
    }
}


/**
 * displays the total sales of each product and prints to the console the names of the product and the value
 * @param label two dimensional array holding the value of the label
 * @param data two dimensinal array holding the value of the data
 * @param r counts of the fruit plus the count of the dairy
 */
void display_sales(char label[][25], int data[][6], int r)
{
    int i;
    for(i = 0; i < r; i++)

        printf("\n All %s sold: %d\n", label[i], data[i][5]);
}


int main(int argc, char **argv)
{
    int c_fruit = 0, c_dairy = 0;

    char label[200][25];
    int data[200][6];

    if(argc < 2){
        printf("please enter the right amount of arguments");
        exit(0);
    }


    FILE *fruit, *dairy;

    fruit = fopen(argv[1], "r+");
    dairy = fopen(argv[2], "r+");


    count_line(fruit, &c_fruit, dairy, &c_dairy);


    if(c_dairy > 2 && c_fruit > 2)
    {
        fruit = fopen(argv[1], "r");
        dairy = fopen(argv[2], "r");
        c_dairy--;
        c_fruit--;

        read(fruit, dairy, label, data, c_fruit, c_dairy);
        display_sales(label, data, c_fruit + c_dairy);
    }



    return 0;
}


//
// Mussab Assefa
// 11219197
// maa392

#include<stdio.h>
#define STATION_CODE_LENGTH 8
#include <stdlib.h>
#include<string.h>


typedef struct _station
{
    char code[STATION_CODE_LENGTH];
    struct _station *next;
}Station;

typedef struct _route{
    Station *first_station;
    unsigned int num_stations;
}Route;


/**
 * creates a node
 * @param code
 * @return returns the station
 */
Station* createNode(char code[STATION_CODE_LENGTH])
{
    Station * station = (Station*)malloc(sizeof(Station));
    strcpy(station->code, code);
    station->next = NULL;
    return station;
}

/**
 * Displays every station code in the list
 * @param route route structure
 */
void display(Route* route)
{
    unsigned int i = 0;
    Station * head = route->first_station;
    for(i=0;i<route->num_stations;i++)
    {
        printf("%s",head->code);
        head = head->next;
    }
}


/**
 * Reads the codes in the pointer to a new dynamically allocated
 * Route structure that contains a linked list of Station nodes in
 * the reverse order that they appear in the file
 *
 * @param fp a pointer to a file
 * @return a pointer to a new dynamically allocated Route structure
 * that contains a linked list of station nodes in a reverse order
 */
Route* read_stations(FILE *fp)
{
    Route * route = (Route* )malloc(sizeof(Route));
    route->num_stations=0;

    if (fp == NULL)
    {
        printf("unable to retrieve the file");
        return NULL;
    }
    char line [600]; /* or other suitable maximum line size */
    while ( fgets ( line, sizeof line, fp ) != NULL ) /* read a line */
    {

        //printf("%s\n",line);
        Station* node = createNode(line);
        node->next=route->first_station;
        route->first_station=node;
        route->num_stations++;
        //printf("%s\n",route->first_station->code);
        //  fputs ( line, stdout ); /* write the line */
    }
    fclose ( fp );
    return route;
}

/**
 * displays the position number of the station
 * @param route pointer
 * @param code 3 character station code
 */
void search(Route *route, char code[STATION_CODE_LENGTH])
{
    Station *head = route->first_station;
    unsigned int cnt=1;
    int flag=1;
    while(cnt<=route->num_stations)
    {

        if(head->code[0]==code[0] && head->code[1]==code[1] && head->code[2]==code[2])
        {
            printf("route code found at position %d\n",cnt);
            flag=0;

        }
        cnt++;

        head = head->next;


    }
    if(flag)
    {
        printf("Route doesn't found\n");
    }
    return ;
}



int main()
{

    char train[100];
    FILE* fp = fopen("code.txt", "r");
    Route *route= read_stations(fp);
    display(route);
    printf("Enter your train code ");
    fgets(train, 10, stdin);

    search(route,train);
    return 0;
}

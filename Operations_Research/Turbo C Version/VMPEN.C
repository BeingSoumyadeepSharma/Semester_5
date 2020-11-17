#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LIMIT 20

void row_pen(int a[MAX_LIMIT][MAX_LIMIT], int m, int n) {
    int row_penalty[m];
    int i, j, min, secondmin;
    for(i=0;i < m;i++) {
        min = secondmin = INT_MAX;
        for(j=0;j < n;j++) {
            if(a[i][j] < min) {
                secondmin = min;
                min = a[i][j];
            }
            else if (a[i][j] < secondmin && a[i][j] != min) 
                secondmin = a[i][j];
        }
        row_penalty[i] = secondmin - min;
    }
    printf("The Row Penalty: \n");
    for(i = 0;i < m;i++) {
        printf("%d\t", row_penalty[i]);
    }
    printf("\n\n");
}

void col_pen(int a[MAX_LIMIT][MAX_LIMIT], int m, int n) {
    int col_penalty[n];
    int i, j, min, secondmin;
    for(i=0;i < n;i++) {
        min = secondmin = INT_MAX;
        for(j=0;j < m;j++) {
            if(a[j][i] < min) {
                secondmin = min;
                min = a[j][i];
            }
            else if (a[j][i] < secondmin && a[j][i] != min) 
                secondmin = a[j][i];
        }
        col_penalty[i] = secondmin - min;
    }
    
    printf("The Column Penalty: \n");
    for(j = 0;j < n;j++) {
        printf("%d\t", col_penalty[j]);
    }
    printf("\n");
}


void main() {
    int cp[MAX_LIMIT] = {0};
    int req[MAX_LIMIT] = {0};
    int cost[MAX_LIMIT][MAX_LIMIT] = {0};
    int count_cp, count_req;
    int i, j, total_cp = 0, total_req = 0;

    clrscr();
    printf("Enter the no.of supplies (1-20): ");
    scanf("%d",&count_cp);
    printf("Enter the no.of demands (1-20): ");
    scanf("%d",&count_req);

    printf("Enter the supplies: \n");
    for(i = 0;i < count_cp;i++){
        printf("Supply[%d]: ",(i+1));
        scanf("%d",&cp[i]);
        total_cp = total_cp + cp[i];
    }

    printf("Enter the demands: \n");
    for(i = 0;i < count_req;i++){
        printf("Demand[%d]: ",(i+1));
        scanf("%d",&req[i]);
        total_req = total_req + req[i];
    }

    printf("Enter the cost matrix: \n");
    for(i=0;i<count_cp;i++){
        for(j=0;j<count_req;j++){
            printf("Cost[%d][%d]: ",(i+1),(j+1));
            scanf("%d",&cost[i][j]);
        }
    }

    if(total_req < total_cp) {
        printf("The Matrix is Unbalanced! Balancing it...\n");
        req[count_req] = total_cp - total_req;
        count_req++;
    }
    else if(total_cp < total_req) {
        printf("The Matrix is Unbalanced! Balancing it...\n");
        cp[count_cp] = total_req - total_cp;
        count_cp++;
    }

    printf("The New Matrix: \n");
    for(i=0;i<count_cp;i++){
        for(j=0;j<count_req;j++){
            printf("%d\t", cost[i][j]);
        }
        printf("\n");
    }

    row_pen(cost, count_cp, count_req);
    col_pen(cost, count_cp, count_req);

    getch();
}
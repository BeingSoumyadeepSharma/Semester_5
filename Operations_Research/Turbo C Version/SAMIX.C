#include <stdio.h>
#include <stdlib.h>

// Defining Limits
#define CAP_ROW_SIZE 2
#define CAP_COLUMN_SIZE 2

typedef struct Value_Pos
{
    int val, index;
} INDICATOR;


int payoff_mat[CAP_ROW_SIZE][CAP_COLUMN_SIZE] = {0};
int row_min_arr[CAP_ROW_SIZE] = {0};
int col_max_arr[CAP_COLUMN_SIZE] = {0};

void min_row(int m,int n) {
    int min;
    int i, j;
    for(i = 0;i < m;i++) {
        min = payoff_mat[i][0];
        for(j = 1;j < n;j++) {
            if(payoff_mat[i][j] < min) {
                min = payoff_mat[i][j];
            }
        }
        row_min_arr[i] = min;
    }
}

void max_col(int m, int n) {
    int max;
    int i, j;
    for(j = 0;j < n;j++) {
        max = payoff_mat[0][j];
        for(i = 1;i < m;i++) {
            if(payoff_mat[i][j] > max) {
                max = payoff_mat[i][j];
            }
        }
        col_max_arr[j] = max;
    }
}

INDICATOR maxi_min(int m,int n) {
    INDICATOR A;
    int pos;
    int max;
    int i;
    max = row_min_arr[0];
    pos = 0;
    for(i = 1;i < m;i++) {
        if(max < row_min_arr[i]) {
            max = row_min_arr[i];
            pos = i;
        }
    }
    A.val = max;
    A.index = pos;
    return A;
}

INDICATOR mini_max(int m,int n) {
    INDICATOR A;
    int pos;
    int min;
    int j;
    min = col_max_arr[0];
    pos = 0;
    for(j = 1;j < n;j++) {
        if(min > col_max_arr[j]) {
            min = col_max_arr[j];
            pos = j;
        }
    }
    A.val = min;
    A.index = pos;
    return A;
}

void mixedStrategy(int a[CAP_ROW_SIZE][CAP_COLUMN_SIZE], int m, int n) {
    float x1 = 0, x2 = 0, y1 = 0, y2 = 0, v = 0;
    x1 = (float)((a[1][1] - a[1][0]) / ((float)(a[0][0] + a[1][1]) - (a[0][1] + a[1][0])));
    x2 = (float)((a[0][0] - a[0][1]) / ((float)(a[0][0] + a[1][1]) - (a[0][1] + a[1][0])));
    y1 = (float)((a[1][1] - a[0][1]) / ((float)(a[0][0] + a[1][1]) - (a[0][1] + a[1][0])));
    y2 = (float)((a[0][0] - a[1][0]) / ((float)(a[0][0] + a[1][1]) - (a[0][1] + a[1][0])));
    v = (float)(((a[0][0] * a[1][1]) - (a[0][1] * a[1][0])) / ((float)(a[0][0] + a[1][1]) - (a[0][1] + a[1][0])));
    printf("x1 = %.2f\n", x1);
    printf("x2 = %.2f\n", x2);
    printf("y1 = %.2f\n", y1);
    printf("y2 = %.2f\n", y2);
    printf("Value of the Game: %.2f\n", v);
}

void main() {
    int num_playerA_strategy = 2, num_playerB_strategy = 2, i, j;
    INDICATOR minimax, maximin; 
    int saddle_point = 0;

    clrscr();
    printf("Enter the elements of the 2 x 2 Payoff Matrix one by one: \n");
    for(i = 0;i < num_playerA_strategy;i++) {
        for(j = 0;j < num_playerB_strategy;j++) {
            printf("Enter element[%d][%d]: ", (i+1), (j+1));
            scanf("%d", &payoff_mat[i][j]);
        }
    }

    printf("The Payoff Matrix: \n");
    for(i = 0;i < num_playerA_strategy;i++) {
        for(j = 0;j < num_playerB_strategy;j++) {
            printf("%d\t", payoff_mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    min_row(num_playerA_strategy, num_playerB_strategy);
    max_col(num_playerA_strategy, num_playerB_strategy);

    printf("The Row Minimums: \n");
    for(i = 0;i < num_playerA_strategy;i++) {
        printf("%d\t", row_min_arr[i]);
    }
    printf("\n\n");

    printf("The Column Maximums: \n");
    for(j = 0;j < num_playerB_strategy;j++) {
        printf("%d\t", col_max_arr[j]);
    }
    printf("\n\n");

    minimax = mini_max(num_playerA_strategy, num_playerB_strategy);
    printf("Minimax = %d\n", minimax.val);
    maximin = maxi_min(num_playerA_strategy, num_playerB_strategy);
    printf("Maximin = %d\n", maximin.val);

    if(minimax.val == maximin.val) {
        saddle_point = minimax.val;
        printf("Saddle Point found at location (%d, %d)\n", (maximin.index + 1), (minimax.index + 1));
        printf("The Saddle Point (Value of the Game): %d\n", saddle_point);
    }
    else {
        printf("Saddle Point is not present!! Going for Mixed Strategy....\n");
        printf("Mixed Strategy Solution: \n");
        mixedStrategy(payoff_mat, num_playerA_strategy, num_playerB_strategy);
    }

    getch();
}


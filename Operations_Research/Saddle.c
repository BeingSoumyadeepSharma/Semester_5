#include <stdio.h>
#include <stdlib.h>

// Defining Limits
#define CAP_ROW_SIZE 20
#define CAP_COLUMN_SIZE 20

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

int maxi_min(int m,int n) {
    int max;
    int i;
    max = row_min_arr[0];
    for(i = 1;i < m;i++) {
        if(max < row_min_arr[i]) {
            max = row_min_arr[i];
        }
    }
    return max;
}

int mini_max(int m,int n) {
    int min;
    int j;
    min = col_max_arr[0];
    for(j = 0;j < n;j++) {
        if(min > col_max_arr[j]) {
            min = col_max_arr[j];
        }
    }
    return min;
}

int main(void) {
    int num_playerA_strategy, num_playerB_strategy, i, j;
    int minimax, maximin, saddle_point = 0;
    printf("Enter the number of Player A Strategies (1-20): ");
    scanf("%d", &num_playerA_strategy);

    printf("Enter the number of Player B Strategies (1-20): ");
    scanf("%d", &num_playerB_strategy);

    printf("Enter the elements of the Payoff Matrix one by one: \n");
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
    printf("Minimax = %d\n", minimax);
    maximin = maxi_min(num_playerA_strategy, num_playerB_strategy);
    printf("Maximin = %d\n", maximin);

    if(minimax == maximin) {
        saddle_point = minimax;
        printf("The Saddle Point: %d\n", saddle_point);
    }
    else {
        printf("Saddle Point is not present!!\n");
    }

    return 0;
}


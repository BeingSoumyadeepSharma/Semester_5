#include <stdio.h>
#include <stdlib.h>

#define MAX_LIMIT 20

int main(void) {
    int n_jobs, n_operators, i, j;
    int assign_mat[MAX_LIMIT][MAX_LIMIT] = {0};
    int assign_mat_copy[MAX_LIMIT][MAX_LIMIT] = {0};
    int row_min[MAX_LIMIT] = {0};
    int col_min[MAX_LIMIT] = {0};
    int r_min, c_min;

    printf("Enter the number of Operators (1-20): ");
    scanf("%d",&n_operators);

    printf("Enter the number of Jobs (1-20): ");
    scanf("%d",&n_jobs);

    printf("Enter the elements of the assignment matrix one by one: \n");
    for(i = 0;i < n_operators;i++) {
        for(j = 0;j < n_jobs;j++) {
            printf("Element[%d][%d] = ", (i+1),(j+1));
            scanf("%d",&assign_mat[i][j]);
            assign_mat_copy[i][j] = assign_mat[i][j];
        }
    }

    if(n_jobs < n_operators) {
        printf("The Matrix is Unbalanced! Balancing it...\n");
        n_jobs = n_operators;
    }
    else if(n_jobs > n_operators) {
        printf("The Matrix is Unbalanced! Balancing it...\n");
        n_operators = n_jobs;
    }

    printf("The Assignment Matrix: \n");
    for(i = 0;i < n_operators;i++) {
        for(j = 0;j < n_jobs;j++) {
            printf("%d\t", assign_mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(i = 0;i < n_operators;i++) {
        r_min = assign_mat_copy[i][0];
        for(j = 0;j < n_jobs;j++) {
            if(assign_mat_copy[i][j] < r_min) {
                r_min = assign_mat_copy[i][j];
            }
        }
        row_min[i] = r_min;
    }

    printf("\nThe Row Minimum: \n");
    for(i = 0;i < n_operators;i++) {
        printf("%d\t", row_min[i]);
    }
    printf("\n");

    printf("\nThe Row Reduced Matrix: \n");
    for(i = 0;i < n_operators;i++) {
        for(j = 0;j < n_jobs;j++) {
            assign_mat_copy[i][j] = assign_mat_copy[i][j] - row_min[i];
            printf("%d\t", assign_mat_copy[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(i = 0;i < n_jobs;i++) {
        c_min = assign_mat_copy[0][i];
        for(j = 0;j < n_operators;j++) {
            if(assign_mat_copy[j][i] < c_min) {
                c_min = assign_mat_copy[j][i];
            }
        }
        col_min[i] = c_min;
    }

    printf("\nThe Column Minimum: \n");
    for(i = 0;i < n_jobs;i++) {
        printf("%d\t", col_min[i]);
    }
    printf("\n");

    printf("\nThe Column Reduced Matrix: \n");
    for(i = 0;i < n_operators;i++) {
        for(j = 0;j < n_jobs;j++) {
            assign_mat_copy[i][j] = assign_mat_copy[i][j] - col_min[j];
            printf("%d\t", assign_mat_copy[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}
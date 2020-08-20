#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int cp[20] = {0};
    int req[20] = {0};
    int cost[20][20] = {0};
    int allot[20][20] = {0};
    int count_cp, count_req;
    int i,j;
    int total = 0;

    // No.of capacities and requirements
    printf("Enter the no.of capacities (1-20): ");
    scanf("%d",&count_cp);
    printf("Enter the no. of requirements (1-20): ");
    scanf("%d",&count_req);

    // Entering capacity of every origin
    printf("\033[01;33m");
    printf("Enter the capacities: \n");
    printf("\033[0m");
    for(i = 0;i < count_cp;i++){
        printf("Capacity[%d]: ",(i+1));
        scanf("%d",&cp[i]);
    }
    // Entering requirement of every destination
    printf("\033[01;33m");
    printf("Enter the requirements: \n");
    printf("\033[0m");
    for(i = 0;i < count_req;i++){
        printf("Requirements[%d]: ",(i+1));
        scanf("%d",&req[i]);
    }

    // Entering the cost matrix
    printf("\033[01;33m");
    printf("Enter the cost matrix: \n");
    printf("\033[0m");
    for(i=0;i<count_cp;i++){
        for(j=0;j<count_req;j++){
            printf("Cost[%d][%d]: ",(i+1),(j+1));
            scanf("%d",&cost[i][j]);
        }
    }

    // Main Logic
    i = 0,j = 0;
    while(i < count_cp && j < count_req) {
        if(cp[i] < req[j]){
            // if capacity less than requirement
            total = total + (cost[i][j] * cp[i]);
            allot[i][j] = cp[i];
            req[j] = req[j] - cp[i];
            cp[i] = 0;
            i++;
        }
        else if(cp[i] > req[j]){
            // if capacity more than requirement
            total = total + (cost[i][j] * req[j]);
            allot[i][j] = req[j]; 
            cp[i] = cp[i] - req[j];
            req[j] = 0;
            j++;
        }
        else if(cp[i] == req[j]){
            // if capacity equal to requirement
            total = total + (cost[i][j] * cp[i]);
            allot[i][j] = cp[i];
            cp[i] = 0;
            req[j] = 0;
            i++;
            j++;
        }
    }

    // Displaying the final allotment matrix according to NWCM
    printf("\033[1;32m");
    printf("The Final Allotment Matrix: \n");
    printf("\033[0m");
    for(i=0;i<count_cp;i++){
        for(j=0;j<count_req;j++){
            if(allot[i][j] == 0){
                printf("X\t");
            }
            else {
                printf("%d\t",allot[i][j]);
            }            
        }
        printf("\n");
    }

    // Displaying the Total Cost for Transportation
    printf("Total Cost in NWCM: %d\n",total);
    return 0;
}
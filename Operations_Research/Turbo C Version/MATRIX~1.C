#include <stdio.h>
#include <stdlib.h>

// Defining Limits
#define CAP_ROW_SIZE 20
#define CAP_COLUMN_SIZE 20

// Structure to store the row index and column index of the minimum element
typedef struct Index {
    int a, b;
} Index;

// Declaring Globals
int cost_mat[CAP_ROW_SIZE][CAP_COLUMN_SIZE] = {0};
int allot_mat[CAP_ROW_SIZE][CAP_COLUMN_SIZE] = {0};
char sign_mat[CAP_ROW_SIZE][CAP_COLUMN_SIZE];
int supply[CAP_ROW_SIZE] = {0};
int demand[CAP_ROW_SIZE] = {0};

// Function to initialize the Sign Matrix which we will use to get the result
void initSignMat(int m, int n) {
    int i, j;
    for(i = 0;i < m;i++) {
	for(j = 0;j < n;j++) {
	    sign_mat[i][j] = '+';
	}
    }
}

// Function to check sign of cell in the Sign Matrix
int checkSign(int m, int n) {
    int i, j, flag = 0;
    for(i = 0;i < m;i++) {
	for(j = 0;j < n;j++) {
	    if(sign_mat[i][j] == '+') {
		flag = 1;
		goto end;
	    }
	}
    }
    end: return flag;
}

// Function to find the minimum element in the Cost Matrix
Index minElement(int m, int n) {
    Index x;
    int i, j, i1, j1, min = 0;
    for(i1 = 0;i1 < m;i1++) {
	for(j1 = 0;j1 < n;j1++) {
	    if(sign_mat[i1][j1] == '+') {
		goto start;
	    }
	}
    }
    start:
    min = cost_mat[i1][j1];
    x.a = i1;
    x.b = j1;
    for(i = i1;i < m;i++) {
	for(j = j1;j < n;j++) {
	    if(sign_mat[i][j] == '+') {
		if(min > cost_mat[i][j]) {
		    min = cost_mat[i][j];
		    x.a = i;
		    x.b = j;
		}
	    }
	}
    }
    return x;
}

// Function to delete column after allocation
void delColumn(int m, int v) {
    int i;
    for(i = 0; i < m;i++) {
	sign_mat[i][v] = '-';
    }
}

// Function to delete row after allocation
void delRow(int n, int v) {
    int i;
    for(i = 0; i < n;i++) {
	sign_mat[v][i] = '-';
    }
}

void main() {
    Index x;
    int supply_size, demand_size, i, j;
    int total_supply = 0, total_demand = 0;
    int total_sum = 0; // storing sum of allotted matrix
    clrscr();
    printf("Enter the no.of supplies: (1-20) ");
    scanf("%d", &supply_size);
    printf("Enter the no.of demands: (1-20) ");
    scanf("%d", &demand_size);
    printf("Enter the supply amounts one by one: \n");
    for(i = 0;i < supply_size;i++) {
	printf("Enter supply[%d] = ",(i+1));
	scanf("%d", &supply[i]);
	total_supply = total_supply + supply[i];
    }
    printf("Enter the demand amounts one by one: \n");
    for(i = 0;i < demand_size;i++) {
	printf("Enter demand[%d] = ",(i+1));
	scanf("%d", &demand[i]);
	total_demand = total_demand + demand[i];
    }
    printf("Enter the cost matrix: \n");
    for(i = 0;i < supply_size;i++) {
	for(j = 0;j < demand_size;j++) {
	    printf("Enter cost[%d][%d] = ", (i+1), (j+1));
	    scanf("%d", &cost_mat[i][j]);
	}
    }
	printf("The Cost Matrix: \n");
	for(i = 0;i < supply_size;i++) {
	for(j = 0;j < demand_size;j++) {
	    printf("%d\t", cost_mat[i][j]);
	}
	printf("\n");
    }

    // Logic for handling unbalanced situation
    if(total_demand < total_supply) {
	demand[demand_size] = total_supply - total_demand;
	demand_size++;
    }
    else if(total_supply < total_demand) {
	supply[supply_size] = total_demand - total_supply;
	supply_size++;
    }

    // Initializing Sign Matrix
    initSignMat(supply_size, demand_size);

    // Main Logic
    while(checkSign(supply_size, demand_size)) {
	x = minElement(supply_size, demand_size);
	i = x.a;
	j = x.b;
	if(supply[i] > demand[j]) {
	    total_sum = total_sum + (cost_mat[i][j] * demand[j]);
	    allot_mat[i][j] = demand[j];
	    supply[i] = supply[i] - demand[j];
	    delColumn(supply_size, j);
	}
	else if(demand[j] > supply[i]) {
	    total_sum = total_sum + (cost_mat[i][j] * supply[i]);
	    allot_mat[i][j] = supply[i];
	    demand[j] = demand[j] - supply[i];
	    delRow(demand_size, i);
	}
	else if(demand[j] == supply[i]) {
	    total_sum = total_sum + (cost_mat[i][j] * supply[i]);
	    allot_mat[i][j] = supply[i];
	    supply[i] = 0;
	    demand[j] = 0;
	    delColumn(supply_size, j);
	    delRow(demand_size, i);
	}
    }
    // Final allocation matrix: output
    printf("The Final Allotment Matrix: \n");
    for(i=0;i<supply_size;i++){
	for(j=0;j<demand_size;j++){
	    if(allot_mat[i][j] == 0){
		printf("X\t");
	    }
	    else {
		printf("%d\t",allot_mat[i][j]);
	    }
	}
	printf("\n");
    }

    printf("Total Cost in Matrix Minima: %d\n",total_sum);

    getch();
}

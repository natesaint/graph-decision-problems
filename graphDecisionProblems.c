// Nathen St. Germain
// CIS*3150 - Assignment 2 - Question 9
//
// Determine if graphs represented as an edge 
// listing have a: dominating set, independent 
// set, clique, or vertex cover of size k

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 101

int n, m, k, binaryString[MAX_N], isDom, isInd, isCliq, isVert;

// Check for a dominating set
int checkDominatingSet(int matrix[MAX_N][MAX_N]) {
    int checkCol = 1;

    for (int i = 1; i < n + 1; i++) {
        int checkRow = 0;
        for (int j = 1; j < n + 1; j++) {
            if (binaryString[j] == 1 && matrix[i][j] == 1) {
                j = n + 1;
                checkRow = 1;
            }
        }
        if (!checkRow) {
            i = n + 1;
            checkCol = 0;
        }
    }

    if (checkCol)
        return 1;
    return 0;
}

// Check for an independent set
int checkIndependentSet(int matrix[MAX_N][MAX_N]) {
    return 0;
}

// Check for a clique
int checkClique(int matrix[MAX_N][MAX_N]) {

    for (int i = 1; i < n + 1; i++) {
        if (binaryString[i] == 1) {

        }
    }

    return 0;
}

// Check for a vertex cover
int checkVertexCover(int matrix[MAX_N][MAX_N]) {
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (matrix[i][j] == 1 && i != j) {// If theres an edge
                int found = 0;
                if (binaryString[i] == 1 || binaryString[j] == 1)//Check that it is covered
                    found = 1;
                if (!found) return 0;
            }
        }
    }
    return 1;
}

// Generate binary strings of length n with k 1s
void listBinary(int t, int numOnes, int matrix[MAX_N][MAX_N]) {
    // Strings of length n with k ones
    if (t > n) {
        /*for (int i = 1; i < n + 1; i++) {
            printf("%d", binaryString[i]);
        }
        printf("\n");*/

        isDom += checkDominatingSet(matrix);
        isInd += checkIndependentSet(matrix);
        isCliq += checkIndependentSet(matrix);
        isVert += checkVertexCover(matrix);
        printf("\n");
    // Concat. new parts of binary string
    } else {
        if (n - t + 1 > k - numOnes) {
            binaryString[t] = 0;
            listBinary(t + 1, numOnes, matrix);
        }

        if (numOnes < k) {
            binaryString[t] = 1;
            listBinary(t + 1, numOnes + 1, matrix);
        }
    }
}

// Read in edge listing, and update the adjancency matrix
void readEdgeListing(char *filename, int matrix[MAX_N][MAX_N]) {
    int readFirst = 0;
    char line[20];
    FILE *fp = fopen(filename, "r");

    while (fgets(line, 20, fp)) {
        char *token = strtok(line, " \n");
        if (readFirst) {
            int x, y;
            x = (int)strtol(token, NULL, 10);
            token = strtok(NULL, " \n");
            y = (int)strtol(token, NULL, 10);
            matrix[x][y] = 1;
            matrix[y][x] = 1;
        } else {
            n = (int)strtol(token, NULL, 10);
            token = strtok(NULL, " \n");
            m = (int)strtol(token, NULL, 10);
            token = strtok(NULL, " \n");
            k = (int)strtol(token, NULL, 10);
        }
        readFirst = 1;
    }

    for (int i = 1; i < n + 1; i++) matrix[i][i] = 1;

    fclose(fp);
}

// Handle the calling of functions to read data, gen strings, check dom. set
void checkGraph(char *filename) {
    int matrix[MAX_N][MAX_N];

    // Initialize matrix for repeated runs
    for (int i = 0; i < MAX_N; i++)
        for (int j = 0; j < MAX_N; j++)
            matrix[i][j] = 0;

    readEdgeListing(filename, matrix);
    listBinary(1, 0, matrix);

    // Print results
    isDom  ? printf(" (a) YES") : printf(" (a) NO");
    isInd  ? printf(" (b) YES") : printf(" (b) NO");
    isCliq ? printf(" (c) YES") : printf(" (c) NO");
    isVert ? printf(" (d) YES\n") : printf(" (d) NO\n");
}

int main () {
    int i = 0;
    /*printf("Graph %d:  ", ++i); checkGraph("ass3_g1.txt");
    printf("Graph %d:  ", ++i); checkGraph("ass3_g2.txt");
    printf("Graph %d:  ", ++i); checkGraph("ass3_g3.txt");
    printf("Graph %d:  ", ++i); checkGraph("ass3_g4.txt");
    printf("Graph %d:  ", ++i); checkGraph("ass3_g5.txt");*/
    printf("Graph %d:  ", ++i); checkGraph("ass3_g6.txt");
    return 0;
}
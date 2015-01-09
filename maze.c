#include <stdio.h>
#include <stdlib.h>

void print(char**, int);
void printint(int**, int,int);
void step(int**, int, int);
void find_path(int**, int, int, int, int, int, int);

int main(int argv, char* argc[]) {
    if (argv == 1) {
        printf("input the maze file! ./maze <mazefile>\n");
        return 1;
    }

    FILE* fp = fopen(argc[1], "r");
    int width, height, w, h;
    int ir, ic, or, oc;

    fscanf(fp, "w:%d h:%d\n", &width, &height);

    printf("width:%d height:%d\n", width, height);

    char** maze = malloc(sizeof(char*) * height);
    int** mazedat = malloc(sizeof(int*) * height);


    for (h = 0; h < height; h++) {
        maze[h] = malloc(sizeof(char) * width);
        mazedat[h] = malloc(sizeof(int) * width);
        fgets(maze[h], width+2, fp);
        for (w = 0; w < width; w++) {
            switch (maze[h][w]) {
                case '#':
                    mazedat[h][w] = -1;
                    break;
                case ' ':
                    mazedat[h][w] = 0;
                    break;
                case 'I':
                    mazedat[h][w] = 1;
                    ir = h;
                    ic = w;
                    break;
                case 'O':
                    mazedat[h][w] = 0;
                    or = h;
                    oc = w;
                    break;
                default:
                    mazedat[h][w] = -2;
                    break;
            }
        }
    }


    while (mazedat[or][oc] == 0) {
        step(mazedat,height, width);
    }

    find_path(mazedat, height, width, or, oc, ir, ic);

    printint(mazedat, height, width);


}



void printint(int** matrix, int height, int width) {
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (matrix[i][j] > -1) {
                if (matrix[i][j] > 0)
                    printf("%2d", matrix[i][j] % 100);
                else
                    printf("  ");
            } else if (matrix[i][j] == -3) {
                printf("--");
            } else {
                printf("##");
            }
        }
        printf("\n");
    }
}

void step(int** matrix, int height, int width) {
    int i, j;

    int** old = malloc(sizeof(int*) * height);

    // copies matrix
    for (i = 0; i < height; i++) {
        old[i] = malloc(sizeof(int) * width);
        for (j = 0; j < width; j++) {
            old[i][j] = matrix[i][j];
        }
    }

    int t, b, l, r;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            t = (i > 0) && (old[i-1][j] > 0);
            b = (i < height - 1) && (old[i+1][j] > 0);
            l = (j > 0) && (old[i][j-1] > 0);
            r = (j < width - 1) && (old[i][j+1] > 0);

            if ((matrix[i][j] > 0) || ((matrix[i][j] > -1) && (t || b || l || r ))    ) {
                matrix[i][j]++;
            }
        }
    }

    for (i = 0; i < height; i++) {
        free(old[i]);
    }
    free(old);
}

void find_path(int** matrix, int height, int width, int oi, int oj, int ii, int ij) {
    int i, j, next;
    i = oi;
    j = oj;

    next = 2; // matrix[oi][oj] + 1;
    matrix[i][j] = -3; // sign for path.

    while ( i != ii || j != ij) {
        if ((i > 0) && (matrix[i-1][j] == next)) {
            i--;
        } else if ((i < height - 1) && (matrix[i+1][j] == next)) {
            i++;
        } else if ((j > 0) && (matrix[i][j-1] == next)) {
            j--;
        } else if ((j < width - 1) && (matrix[i][j+1] == next)) {
            j++;
        } else {
            printf("this broke while converting data to readable path\n");
            exit(-1);
        }

        matrix[i][j] = -3;

        next++;
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if ((matrix[i][j] != -3) && (matrix[i][j] != -1)) {
                matrix[i][j] = 0;
            }
        }
    }


}


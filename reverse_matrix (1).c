#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define N 4

int GAUSS[N][2*N];
float GAUSS_fl[N][2*N];
float GAUSS_fl_mass[N][N][2*N];

/* void preobraz(int otkuda, int koeff, int kuda) {
    for(int j = 0; j < 2*N; ++j){
        GAUSS[kuda][j] += koeff*GAUSS[otkuda][j];
    }
} */

void print_matrix(float matrix[N][2*N]) {
    puts("\n");
    for(int i=0; i<N; ++i) {
        for(int j=0; j<2*N; ++j) {
                printf("%3.3f ", matrix[i][j]);
        }
        puts("\n");
    }
    puts("\n");
}

void elementrnoe(float matrix[N][2*N]) {
    float diag1 = matrix[0][0];
    for(int j = 0; j < 2*N; ++j){
        matrix[0][j] = matrix[0][j]/diag1;
    }

    for(int i = 1; i < N; ++i) {
        int koeff = matrix[i][0];
        for(int j = 0; j < 2*N; ++j) {
            matrix[i][j] = matrix[i][j] -koeff * matrix[0][j];
        }
    }
}

int main (void)
{
    //������������� ���������� � ��������:
    setlocale(LC_ALL, "Rus");
    int A[N][N];
    int A_help[N][N];
    int A_help_transp[N][N];
    float A_help_transp_fl[N][N];
    int i,j, line, floor;
    int determinant = 0;
    float reverse_determinant;
    int MASS[N][N-1];
    int massives_minor[N][N][N-1][N-1];
    int key;
    int key2;
    int det[N][N];
    float rev_det_module;
    float GAUSS_fl_1[N-1][N-1];
    float GAUSS_fl_2[N-2][N-2];

    //����������: ���� ������� � ���������� � ����� �� � �������:
    /*for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            scanf("%3d", &p);
            A[i][j] = p;
        }
    }
    printf("\n\n");
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            printf("%3d ",A[i][j]);
        }
        puts("\n");
    }
    */

    //����� ��������� ������� 4*4:
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            A[i][j] = rand() % 30 + 1;
            printf("%3d ",A[i][j]);
        }
        puts("\n");
    }

    //Outlining floors and lines:
    printf("\n\n");
    //key - �������
    //key2 - ������
    for(key = 0; key < N; ++key) {
        for(key2 = 0; key2 < N; ++key2) {
            for(i = 0; i < N - 1; ++i) {
                for(j = 0; j < N - 1; ++j) {
                    if( j < key) {
                        if( i < key2) {
                            MASS[i][j] = A[i][j];
                            // printf("%3i ", MASS[i][j]);
                            massives_minor[key][key2][i][j] = MASS[i][j];
                        }
                        else {
                            MASS[i][j] = A[i+1][j];
                            // printf("%3i ", MASS[i][j]);
                            massives_minor[key][key2][i][j] = MASS[i][j];
                        }
                    }
                    else {
                        if( i < key2) {
                            MASS[i][j] = A[i][j+1];
                            //printf("%3i ", MASS[i][j]);
                            massives_minor[key][key2][i][j] = MASS[i][j];
                        }
                        else {
                            MASS[i][j] = A[i+1][j+1];
                            //printf("%3i ", MASS[i][j]);
                            massives_minor[key][key2][i][j] = MASS[i][j];
                        }
                    }
                }
                //puts("\n");
            }
            //puts("\n\n");
        }
    }

    //Calculating dets of matrix'es 3*3:
    for(line = 0; line < N; ++line) {
        for(floor = 0; floor < N; ++floor) {
            det[line][floor] = massives_minor[line][floor][0][0]*massives_minor[line][floor][1][1]*massives_minor[line][floor][2][2] +
                               massives_minor[line][floor][1][0]*massives_minor[line][floor][2][1]*massives_minor[line][floor][0][2] +
                               massives_minor[line][floor][0][1]*massives_minor[line][floor][1][2]*massives_minor[line][floor][2][0] -
                               massives_minor[line][floor][2][0]*massives_minor[line][floor][1][1]*massives_minor[line][floor][0][2] -
                               massives_minor[line][floor][1][0]*massives_minor[line][floor][0][1]*massives_minor[line][floor][2][2] -
                               massives_minor[line][floor][1][2]*massives_minor[line][floor][2][1]*massives_minor[line][floor][0][0];
        }
    }

    //Calculating determinant of 4*4 matrix:
    for(line = 0; line < N; ++line) {
        if(line%2 == 0) {
            determinant = determinant + A[0][line]*det[line][0];
        }
        else {
            determinant = determinant - A[0][line]*det[line][0];
        }
    }

    //Getting minor matrix:
    printf("Minor matrix: \n\n");
    for(floor = 0; floor < N; ++floor) {
        for(line = 0; line < N; ++line) {
            if((line+floor)%2 == 0) {
                A_help[line][floor] = det[line][floor];
                printf("%5d ",A_help[line][floor]);
            }
            else {
                A_help[line][floor] = -det[line][floor];
                printf("%5d ",A_help[line][floor]);
            }
        }
        puts("\n");
    }

    //Transposing minor matrix:
    printf("Transposed minor matrix: \n\n");
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            A_help_transp[i][j] = A_help[i][j];
            printf("%5d ", A_help_transp[i][j]);
        }
        puts("\n");
    }

    printf("DET: %i \n\n", determinant);
    reverse_determinant = 1/(float)determinant;


    printf("reverse det : %f \n\n", reverse_determinant);

    //Showing reverse matrix:
    printf("Reverse matrix: \n\n");
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            A_help_transp_fl[i][j] = A_help_transp[i][j];
            A_help_transp_fl[i][j] = A_help_transp_fl[i][j] * reverse_determinant;
            printf("%6f ", A_help_transp_fl[i][j]);

        }
        puts("\n");
    }

    //Check:
    /*
    printf("Line and floor you want to outline, sir: \n\n");
    scanf("%i %i", &line, &floor);
    line = line - 1;
    floor = floor - 1;

    printf("Your matrix, sir: \n\n");
    for(i = 0; i < N - 1; ++ i) {
        for(j = 0; j < N - 1;++ j) {
            printf("%3d", massives_minor[line][floor][i][j]);
        }
        puts("\n");
    }

    printf("det you needed: %i \n\n", det[2][3]);
    */

    printf("Gauss method: \n\n");
    //Creating Gauss matrix:
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j){
            GAUSS[i][j] = A[i][j];
        }
    }

    for(i = 0; i < N; ++i) {
        for(j = 4; j < 2*N; ++j) {
            if(i == j - 4) {
                GAUSS[i][j] = 1;
            }
            else{
                GAUSS[i][j] = 0;
            }
        }
    }

    //Showing Gauss matrix:
    for(i = 0; i < N; ++i) {
        for(j = 0; j < 2*N; ++j) {
            GAUSS_fl[i][j] = (float)GAUSS[i][j];
            printf("%3.3f ", GAUSS_fl[i][j]);
        }
        puts("\n");
    }


    elementrnoe(GAUSS_fl);
    print_matrix(GAUSS_fl);

    for(i = 0; i < N - 1; ++i) {
        for(j = 0; j < 2*N - 1; ++j) {
            GAUSS_fl_1[i][j] = GAUSS_fl[i+1][j+1];
            printf("%3.3f  ", GAUSS_fl_1[i][j]);
        }
        puts("\n");
    }


    /* for (line = 0; line < N -1; ++line) {
    elementrnoe(GAUSS_fl_mass[line]);
        for(i = 0; i < N; ++i) {
            for(j = 0; j < N; ++j) {
            GAUSS_fl_mass[line + 1][i][j] = GAUSS_fl[i+1][j+1];
            }
        }
        print_matrix(GAUSS_fl_mass[line]);
    }*/

    /* preobraz(2, -1, 0);
    for(i = 0; i < N; ++i) {
        for(j = 0; j < 2*N; ++j) {
            printf("%3d", GAUSS[i][j]);
        }
        puts("\n");
    }
    printf("\n"); */



    return 0;
}





#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main (void)
{
    //������������� ���������� � ��������:
    setlocale(LC_ALL, "Rus");
    int N = 5;
    int i,j,o,p, line, line2;
    long int determinant = 0;
    long int minor_det = 0;
    int A[N][N];
    int MASS[N-1][N-1];
    int MASS2[N-2][N-2];
    int massives[N][N-1][N-1];
    int massives_little[N][N-1][N-2][N-2];
    int mass_det[N];
    int det[N][N-1];
    int minor_dets[N];



    //��� ������ � �������:
    FILE *file;
    file = fopen("new_file.tex", "w");

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

    //����� ��������� ������� 5*5:
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            A[i][j] = rand() % 30 + 1;
            printf("%3d ",A[i][j]);
        }
        puts("\n");
    }

    printf("\n\n");

    //"���������" ����� � �������� � ��������� �������� ������ 4*4:
    for(line = 0; line < N; ++line) {
        for(i = 1; i < N; ++i) {
            for(j = 0; j < N; ++j) {
                if(j != line) {

                    if(j < line + 1) {
                        MASS[i-1][j] = A[i][j];
                        /*printf("%3d ", MASS[i-1][j]);*/
                        massives[line][i-1][j] = MASS[i-1][j];

                    }
                    else {
                        MASS[i-1][j-1] = A[i][j];
                        /* printf("%3d ", MASS[i-1][j-1]);*/
                        massives[line][i-1][j-1] = MASS[i-1][j-1];
                    }

                }
            }
            /*puts("\n");*/


        }
        printf("\n\n");
    }

    //"���������" ����� � �������� � ��������� �������� ������ 3*3:
    for(line = 0; line < N; ++line) {
        for(line2 = 0; line2 < N - 1; ++line2)  {
            for(i = 1; i < N - 1; ++i) {
                for(j = 0; j < N - 1; ++j) {
                    if(j != line2) {
                        if(j < line2 + 1) {
                            MASS2[i-1][j] = massives[line][i][j];
                            /* printf("%3d ", MASS2[i-1][j]);*/
                            massives_little[line][line2][i-1][j] = MASS2[i-1][j];

                        }
                        else {
                            MASS2[i-1][j-1] = massives[line][i][j];
                            /* printf("%3d ", MASS2[i-1][j-1]); */
                            massives_little[line][line2][i-1][j-1] = MASS2[i-1][j-1];
                        }
                    }
                }
                /* puts("\n"); */
            }
            printf("\n\n");
        }
    }

    //���������� ������������� ������ 3*3:
    for(line = 0; line < N; ++line) {
        for(line2 = 0; line2 < N -1; ++line2) {
            det[line][line2] = massives_little[line][line2][0][0]*massives_little[line][line2][1][1]*massives_little[line][line2][2][2] +
                               massives_little[line][line2][1][0]*massives_little[line][line2][2][1]*massives_little[line][line2][0][2] +
                               massives_little[line][line2][0][1]*massives_little[line][line2][1][2]*massives_little[line][line2][2][0] -
                               massives_little[line][line2][2][0]*massives_little[line][line2][1][1]*massives_little[line][line2][0][2] -
                               massives_little[line][line2][1][0]*massives_little[line][line2][0][1]*massives_little[line][line2][2][2] -
                               massives_little[line][line2][1][2]*massives_little[line][line2][2][1]*massives_little[line][line2][0][0];
        }
    }

    //���������� ������������� ������ 4*4, ������ �� � ������:
    for(line = 0; line < N;  ++line) {
        for(line2 = 0; line2 < N-1; ++line2 ) {
            if(line2%2 == 0) {
                minor_det = minor_det + massives[line][0][line2]*det[line][line2];
            }
            else {
                minor_det = minor_det - massives[line][0][line2]*det[line][line2];
            }
        }
        minor_dets[line] = minor_det;
        minor_det = 0;
    }

    //���������� ������������ ������� 5*5:
    for(line = 0; line < N;  ++line) {
        if(line%2 == 0) {
            determinant = determinant + minor_dets[line]*A[0][line];
        }
        else {
            determinant = determinant - minor_dets[line]*A[0][line];
        }
    }

    //���������� ��������:
    /*printf(" ������� �������� ����� 4*4 :\n\n");
    for(o = 0; o < N-1; ++o) {
        for(p = 0; p < N-1; ++p) {
            printf("%3d", massives[4][o][p]);
        }
        puts("\n");
    }

    printf("\n");

    printf(" ������� �������� ����� 3*3:\n\n");
    for(o = 0; o < N-2; ++o) {
        for(p = 0; p < N-2; ++p) {
            printf("%3d", massives_little[1][0][o][p]);
        }
        puts("\n");
    } */

    printf("\n");
    printf("��������� ������������ �������� ������� 3*3: %i\n", det[1][2]);

    printf("\n");
    printf("��������� ������������ �������� ������� 4*4: %i\n", minor_dets[0]);

    printf("\n");
    printf("�����: %li\n", determinant);

    printf("\n");

    //������ � �������:
    if(file != NULL) {
        printf("New file created successfully\n");
        fputs("\\documentclass{article}\n", file);
        fputs("\\usepackage[utf8]{inputenc}\n", file);
        fputs("\\usepackage[russian]{babel}\n", file);
        fputs("\\usepackage{amsmath}\n", file);
        fputs("\\usepackage{hyperref}\n", file);
        fputs("\\begin{document}\n", file);
        fputs("\\title{Task 1; Raschetka 3}\n", file);
        fputs("\\date{}\n", file);
        fputs("\\maketitle\n", file);
        fputs("$\n", file);
        fputs("\\begin{vmatrix}\n", file);
        for(i = 0; i < N; ++i) {
            for(j = 0; j < N; ++j) {
                if(j != N - 1) {
                    fprintf(file,"%d & ", A[i][j]);
                }
                else {
                    fprintf(file,"%d\\\\\n", A[i][j]);
                }
            }
        }
        fputs("\\end{vmatrix}\n", file);
        fputs("$\n", file);
        fputs("\\end{document}\n", file);
    }

    else {
        fprintf(stderr, "Can not create a file\n");
    }

    return 0;
}






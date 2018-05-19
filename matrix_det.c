#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define N 5

void print_matrix(FILE *pfile ,int* pA, int n, int m) {
    fputs("\\begin{vmatrix}\n", pfile);
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            if(j != m - 1) {
//            printf("%3d &",*(pA+i*n+j));
                fprintf(pfile,"%3d & ",*(pA+i*n+j));
            }
            else {
//			printf("%3d\\\\\n ",*(pA+i*n+j));
                fprintf(pfile,"%3d\\\\\n",*(pA+i*n+j));
            }
        }
    }
    fputs("\\end{vmatrix}\n", pfile);
}

int main (void)
{
    //Initializing values and massives:
    setlocale(LC_ALL, "Rus");
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

    //For file work:
    FILE *pf;
    pf = fopen("new_file.tex", "w");

    //Hidden: taking matrix to terminal:
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

    //Showing random matrix 5*5:
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            A[i][j] = rand() % 30 + 1;
            printf("%3d ",A[i][j]);
        }
        puts("\n");
    }

    printf("\n\n");

    //Taking out floors and lines of matrix 4*4:
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
//       printf("\n\n");
    }

    //Taking out floors and lines of matrix 3*3:
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
            //          printf("\n\n");
        }
    }

    //Calculating determinant of matrix'es 3*3, saving them to massives:
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

    //Calculating determinant of matrix'es 4*4, saving them to massives:
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

    //Calculating determinant of matrix 5*5:
    for(line = 0; line < N;  ++line) {
        if(line%2 == 0) {
            determinant = determinant + minor_dets[line]*A[0][line];
        }
        else {
            determinant = determinant - minor_dets[line]*A[0][line];
        }
    }

    //Different verifications:
    /*printf(" Show needed minor 4*4 :\n\n");
    for(o = 0; o < N-1; ++o) {
        for(p = 0; p < N-1; ++p) {
            printf("%3d", massives[4][o][p]);
        }
        puts("\n");
    }

    printf("\n");

    printf(" Show needed minor 3*3:\n\n");
    for(o = 0; o < N-2; ++o) {
        for(p = 0; p < N-2; ++p) {
            printf("%3d", massives_little[1][0][o][p]);
        }
        puts("\n");
    } */

    printf("\n");
    printf("Calculate determinant of needed matrix 3*3: %i\n", det[1][2]);

    printf("\n");
    printf("Calculate determinant of needed matrix 4*4: %i\n", minor_dets[0]);

    printf("\n");
    printf("ANSWER: %li\n", determinant);

    printf("\n");

    //File work:
    if(pf != NULL) {
        printf("New file created successfully\n");
        fputs("\\documentclass{article}\n", pf);
        fputs("\\usepackage[utf8]{inputenc}\n", pf);
        fputs("\\usepackage[russian]{babel}\n", pf);
        fputs("\\usepackage{amsmath}\n", pf);
        fputs("\\usepackage{hyperref}\n", pf);
        fputs("\\textwidth= 18 cm\n", pf);
        fputs("\\oddsidemargin= -0.5 cm\n", pf);
        fputs("\\mathsurround=2pt\n", pf);
        fputs("\\renewcommand{\\baselinestretch}{2.0}\n", pf);
        fputs("\\begin{document}\n", pf);
        fputs("\\title{Task 1; Raschetka 3}\n", pf);
        fputs("\\date{}\n", pf);
        fputs("\\maketitle\n", pf);
        fputs("$\n", pf);
        print_matrix(pf, A, N, N);
        fputs("=\n", pf);
        for(i = 0; i < N; ++i) {
            if(i%2 == 0) {
                fprintf(pf, "+\n");
            }
            else {
                fprintf(pf, "-\n");
            }
            fprintf(pf, "%i\n", A[0][i]);
            print_matrix(pf, massives[i], N-1, N-1);
        }
        fputs("$\n", pf);
        fputs("=\n", pf);
        //
        fputs("$$\n", pf);
        fputs("=\n", pf);
        for(i = 0; i < N; ++i) {
            if(i%2 == 0) {
                fprintf(pf, "+\n");
            }
            else {
                fprintf(pf, "-\n");
            }
            fprintf(pf, "%i\n",  A[0][i]);
            fprintf(pf, "(%i)", minor_dets[i]);
        }
        fputs("=\n", pf);
        fprintf(pf, "%i", determinant);
        fputs("$$\n", pf);
        fputs("\\hrulefill\n", pf);
        fputs("\\vspace{6pt}\n", pf);
        fputs("\\begin{enumerate}\n", pf);
        for(line = 0; line < N; ++line) {
            fputs("\\item\n", pf);
            fputs("$\n", pf);
            print_matrix(pf, massives[line], N-1, N-1);
            fputs("=\n", pf);
            for(i = 0; i < N-1; ++i) {
                if(i%2 == 0) {
                    fprintf(pf, "+\n");
                }
                else {
                    fprintf(pf, "-\n");
                }
                fprintf(pf, "%i\n", massives[line][0][i]);
                print_matrix(pf, massives_little[line][i], N-2, N-2);
            }
            fputs("=\n", pf);
            fputs("$\n", pf);
            fputs("$$\n", pf);
            fputs("=\n", pf);
            for(i = 0; i < N -1; ++i) {
                if(i%2 == 0) {
                    fprintf(pf, "+\n");
                }
                else {
                    fprintf(pf, "-\n");
                }
                fprintf(pf, "%i\n", massives[line][0][i]);
                fprintf(pf, "(%i)", det[line][i] );
            }
            fputs("=\n", pf);
            fprintf(pf, "%i", minor_dets[line]);
            fputs("$$\n", pf);
            fputs("\\vspace{6pt}\n", pf);
        }
        fputs("\\end{enumerate}\n", pf);
        fprintf(pf, "ANSWER: %i", determinant);
        fputs("\\end{document}\n", pf);

    }
    else {
        fprintf(stderr, "Can not create a file\n");
    }

    fclose(pf);

    return 0;
}






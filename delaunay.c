#include <stdio.h>
#include <stdlib.h>

// vector type for easily reading in ordered pairs
typedef struct vec2_s {
    double x, y;
} vec2;

/*
* Matrix to check if point is in circumcircle
*
*      --                                 --
*      | ax-dx, ay-dx, (ax-dx)^2+(ay-dy)^2 |
*  A = | bx-dx, by-dy, (bx-dx)^2+(by-dy)^2 |
*      | cx-dx, cy-dy, (cx-dx)^2+(cy-dy)^2 |
*      --                                 --
*/

// calculate determinant of a 3x3 matrix
double det(double* A) {
    return (
        A[0] * (A[4]*A[8] - A[5]*A[7]) -
        A[1] * (A[3]*A[8] - A[5]*A[6]) +
        A[2] * (A[3]*A[7] - A[4]*A[6])
   );
}

// test if triangle formed by a, b, and c is in Delaunay triangulation
int test_triangle (vec2* data, int N, int a, int b, int c) {
    double M[3*3] = {
        data[a].x, data[a].y, 1,
        data[b].x, data[b].y, 1,
        data[c].x, data[c].y, 1
    };

    // check if order is counterclockwise
    if (det(M) <= 0) {
        int temp = c;
        c = b;
        b = temp;
    }

    // check each point d against triangle
    double A[3*3];
    for (int d = 0; d < N; d++) {
        if (d == a || d == b || d == c) continue;
        // generate matrix for current iteration
        A[0] = data[a].x - data[d].x; 
        A[1] = data[a].y - data[d].y; 
        A[2] = A[0]*A[0] + A[1]*A[1]; // row 1
        A[3] = data[b].x - data[d].x; 
        A[4] = data[b].y - data[d].y; 
        A[5] = A[3]*A[3] + A[4]*A[4]; // row 2
        A[6] = data[c].x - data[d].x; 
        A[7] = data[c].y - data[d].y; 
        A[8] = A[6]*A[6] + A[7]*A[7]; // row 3
        
        // check if d is contained in circumcircle
        if (det(A) > 0 ) {
            return 0;
        }
    }
    return 1;
}


// Run the test_triangle function to locate the Delaunay triangulation
int main (int argc, char** argv) {
    if (argc < 3) {
        printf("Command usage: %s filename N\n", argv[0]);
        return 0;
    }
    // read data file
    FILE* fp;
    fp = fopen(argv[1], "r");
    int N = atoi(argv[2]);
    int i = 0;
    // initialize dataset vector array
    vec2 data[N];
    // int i = 0;
    while(fscanf(fp, "%lf %lf", &data[i].x, &data[i].y) == 2) {
        i++; 
    }

    // check all possible triangles
    for (int a = 0; a < N - 2; a++) {
        for (int b = a + 1; b < N - 1; b++) {
            for (int c = b + 1; c < N; c++) {
                if (test_triangle(data, N, a, b, c)) {
                   printf("%d %d %d\n", a, b, c); 
                }
            }
        }
    }
    return 0;
}


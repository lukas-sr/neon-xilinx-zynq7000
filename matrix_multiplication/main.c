#include <stdio.h>
#include <stdint.h>
#include "neoh.h"
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"

#define DIM_MATRIX 4

void mat_product_c(float **mat_A, float **mat_B, float **mat_C) {
    for (int i = 0; i < DIM_MATRIX; i++) {
        for (int j = 0; j < DIM_MATRIX; j++) {
            mat_C[i][j] = 0;
            for (int k = 0; k < DIM_MATRIX; k++) {
                mat_C[i][j] += mat_A[i][k] * mat_B[k][j];
            }
        }
    }
}

int main()
{
    init_platform();

    print("Sum of array in Zybo7\n\r");

    float A[DIM_MATRIX][DIM_MATRIX];
    float B[DIM_MATRIX][DIM_MATRIX];
    float C[DIM_MATRIX][DIM_MATRIX];

    XTime tStartC, tEndC, tStartNi, tEndNi;

    for (int i = 0; i < DIM_MATRIX; i++){
        for (int j = 0; j < DIM_MATRIX ; j++){
            A[i][j] = 1;
            B[i][j] = 2;
        }
    }

    XTime_GetTime(&tStartC);
    mat_product_c(A, B, C);
    XTime_GetTime(&tEndC);
    
    // XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ = 650000000
    double timeElapsedC = (double) (tEndC - tStartC) / (double) XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ;
    printf("time elapsed: %f \n", timeElapsedC);
    
    XTime_GetTime(&tStartNi);
    mat_product_ni(A, B, C);
    XTime_GetTime(&tEndNi);

    // XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ = 650000000
    double timeElapsedNi = (double) (tEndNi - tStartNi) / (double) XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ;

    printf("time elapsed: %f \n", timeElapsedNi);
    // printf("sum: %d \n", sum_16x8);

    cleanup_platform();
    return 0;
}
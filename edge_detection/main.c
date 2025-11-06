#include <stdio.h>
#include <stdint.h>
#include "neon.h"
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"

#define MAX_SIZE_ARRAY 10

// arr_a in the input image and arr_b is the output with edge detection 
void edge_c(uint8_t **arr_a, uint8_t **arr_b){
    for (uint8_t i = 0 ; i < MAX_SIZE_ARRAY ; i++){
        for (uint8_t j = 0 ; j < MAX_SIZE_ARRAY ; j++){
            // |G| = |E - W| + |N - S|
            if (i == 0 || j == 0 || i == MAX_SIZE_ARRAY - 1 || j == MAX_SIZE_ARRAY - 1){
                arr_b[i][j] = 0;
            } else {
                int8_t Gx = (int8_t)arr_a[i][j+1] - (int8_t)arr_a[i][j-1];
                int8_t Gy = (int8_t)arr_a[i-1][j] - (int8_t)arr_a[i+1][j];
                int8_t G = (int8_t)(abs(Gx) + abs(Gy));

                if (G > 255){
                    arr_b[i][j] = 255;
                } else {
                    arr_b[i][j] = (uint8_t)G;
                }
            }
        }
    }

}

int main()
{
    init_platform();

    print("Edge Detection in Zybo7\n\r");

    uint8_t arr_x[MAX_SIZE_ARRAY][MAX_SIZE_ARRAY];
    uint8_t arr_y[MAX_SIZE_ARRAY][MAX_SIZE_ARRAY];

    for (uint8_t i = 0, sub = 0 ; i < MAX_SIZE_ARRAY ; i++){
        for (uint8_t j = 0 ; j < MAX_SIZE_ARRAY ; j++){
            if ((i + j) <= MAX_SIZE_ARRAY){
                arr_x[i][j] = 0;
            } else {
                arr_x[i][j] = 100;
            }
        }
    }

    XTime tStart, tEnd, tStartNi, tEndNi;

    XTime_GetTime(&tStart);
    edge_c(arr_x, arr_y);
    XTime_GetTime(&tEnd);
    
    // XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ = 650000000
    double timeElapsed = (double) (tEnd - tStart) / (double) XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ;
    printf("time elapsed: %f \n", timeElapsed);
    
    XTime_GetTime(&tStartNi);
    int16_t sum_16x8 = sum_ni(arr);
    XTime_GetTime(&tEndNi);

    // XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ = 650000000
    double timeElapsed2 = (double) (tEndNi - tStartNi) / (double) XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ;

    printf("time elapsed: %f \n", timeElapsed2);
    printf("sum: %d \n", sum_16x8);


    cleanup_platform();
    return 0;
}
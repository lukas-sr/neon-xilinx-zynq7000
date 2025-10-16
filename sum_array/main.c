#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"

#include <arm_neon.h>

int32_t sum_ni(int16_t *array);

#define MAX_SIZE_ARRAY 2048

int16_t sum_c(int16_t *array) {
    int16_t summ = 0;
    for (int i = 0; i < MAX_SIZE_ARRAY; i++) {
        summ += (int16_t)array[i];
    }

    return summ;
}

int main()
{
    init_platform();

    print("Sum of array in Zybo7\n\r");

    int16_t arr[MAX_SIZE_ARRAY];
    XTime tStart, tEnd, tStartNi, tEndNi;

    for (int i = 0; i < MAX_SIZE_ARRAY; i++){
        arr[i] = 1;
    }

    XTime_GetTime(&tStart);
    int16_t sum = sum_c(arr);
    XTime_GetTime(&tEnd);
    
    // XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ = 650000000
    double timeElapsed = (double) (tEnd - tStart) / (double) XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ;
    printf("time elapsed: %f \n", timeElapsed);
    printf("sum: %d \n", sum);

    
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
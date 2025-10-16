#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"

int main()
{
    init_platform();

    print("Timers in Zybo7\n\r");

    XTime tStart, tEnd;
    
    XTime_GetTime(&tStart);
    for (int i = 0 ; i < 1000000000 ; i++);
    XTime_GetTime(&tEnd);
    
    printf("tEnd: %f \n", (double) tEnd);
    printf("tStart: %f \n", (double) tStart);
    // XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ = 650000000
    double timeElapsed = (double) (tEnd - tStart) / XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ;

    printf("%f \n", timeElapsed);

    cleanup_platform();
    return 0;
}
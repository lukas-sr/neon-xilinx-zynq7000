#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"

int main()
{
    init_platform();

    float time = 0;
    XTime_SetTime(XTime Xtime);

    print("Timers in Zybo7\n\r");

    // XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ = 650000000
    for (int i = 0 ; i < (100) ; i++){
        XTime_GetTime(XTime *Xtime);
        time = (float) *Xtime
    }
    print("%f \n", time);

    cleanup_platform();
    return 0;
}
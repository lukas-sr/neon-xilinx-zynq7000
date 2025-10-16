#include <arm_neon.h>

#define MAX_SIZE_ARRAY 2048

int32_t sum_ni(int16_t *array) {
    int16x8_t va, vacc;
    vacc = vdupq_n_s16(0);

    int32_t summ = 0;
    for (int i = 0; i < MAX_SIZE_ARRAY; i+=8) {
        va = vld1q_s16(&array[i]);
        vacc = vaddq_s16(vacc, va);
    }
    summ = vgetq_lane_s16(vacc,0);
    summ += vgetq_lane_s16(vacc,1);
    summ += vgetq_lane_s16(vacc,2);
    summ += vgetq_lane_s16(vacc,3);
    summ += vgetq_lane_s16(vacc,4);
    summ += vgetq_lane_s16(vacc,5);
    summ += vgetq_lane_s16(vacc,6);
    summ += vgetq_lane_s16(vacc,7);
    return summ;
}


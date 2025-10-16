#include <arm_neon.h>

#define MAX_SIZE_ARRAY 2048

int32_t mat_product_c(float **mat_A, float **mat_B, float **mat_C) {
    int16x8_t va, vacc;
    vacc = vdupq_n_s16(0);

    int32_t mult = 0;
    for (int i = 0; i < MAX_SIZE_ARRAY; i+=8) {
        va = vld1q_s16(&array[i]);
        vacc = vmulq_s16(vacc, va);
    }
    mult = vgetq_lane_s16(vacc,0);
    mult += vgetq_lane_s16(vacc,1);
    mult += vgetq_lane_s16(vacc,2);
    mult += vgetq_lane_s16(vacc,3);
    mult += vgetq_lane_s16(vacc,4);
    mult += vgetq_lane_s16(vacc,5);
    mult += vgetq_lane_s16(vacc,6);
    mult += vgetq_lane_s16(vacc,7);
    return mult;
}


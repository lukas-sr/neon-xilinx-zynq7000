#include <arm_neon.h>

#define DIM_MATRIX 4

void mat_product_c(float **mat_A, float **mat_B, float **mat_C) {
    int16x8_t neon_mat_A, neon_mat_B, neon_mat_C;

    for (int i = 0; i < DIM_MATRIX; i+=8) {
        for (int j = 0; j < DIM_MATRIX; j+=8) {
            mat_C[i][j] = 0;
            for (int k = 0; k < DIM_MATRIX; k+=8) {
                mat_C[i][j] += mat_A[i][k] * mat_B[k][j];
                neon_mat_A = vld1q_s16(&mat_A[i][k]);
                neon_mat_B = vld1q_s16(&mat_B[k][j]);
                neon_mat_C = vmulq_s16(neon_mat_A, neon_mat_B);
            }
        }
    }
    

    // int16x8_t va, vacc;
    // vacc = vdupq_n_s16(0);

    // int32_t mult = 0;
    // for (int i = 0; i < MAX_SIZE_ARRAY; i+=8) {
    //     va = vld1q_s16(&array[i]);
    //     vacc = vmulq_s16(vacc, va);
    // }
    // mult = vgetq_lane_s16(vacc,0);
    // mult += vgetq_lane_s16(vacc,1);
    // mult += vgetq_lane_s16(vacc,2);
    // mult += vgetq_lane_s16(vacc,3);
    // mult += vgetq_lane_s16(vacc,4);
    // mult += vgetq_lane_s16(vacc,5);
    // mult += vgetq_lane_s16(vacc,6);
    // mult += vgetq_lane_s16(vacc,7);
    return mult;
}


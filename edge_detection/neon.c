#include "neon.h"

// arr_a in the input image and arr_b is the output with edge detection using NEON Engine instructions
void edge_ni(uint8_t **arr_a, uint8_t **arr_b){


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
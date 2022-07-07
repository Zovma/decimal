#include <stdio.h>

unsigned int maxInt = 4294967295;

typedef struct {
    unsigned int bits[4];
} s21_decimal;

// провекрка бита
unsigned isSetBit(int number, int index) {
    return (number&(1<<index))!=0;
}

// установка бита в 1
unsigned int setBit(int number, int index) {
    return number | (1 << index);
}

// инверсия бита
int inverseBit(int number, int index) {
    return number^(1 << index);
}

// установка бита в 0
int resetBit(int number, int index) {
    return number &~(1 << index);
}

void scaling_factor(unsigned value_1, int *arr) {
    unsigned int scaling = 0;
    unsigned int count = 0;
    for (int i = 16; i < 24; i++) {
        if (isSetBit(value_1, i)) {
           scaling = setBit(scaling, count);
        }
        count++;
    }
    printf("%u\n", value_1);

    arr[0] = isSetBit(value_1, 31);
    arr[1] = scaling;
}

int shift(s21_decimal value_1, s21_decimal *result, int bits) {
    for (int i = 0; i < 2; i++) {
        result->bits[i] = value_1.bits[i] << bits;
    }

    int count = 0;

    for (int b = 0; b < 2; b++) {
        for (int i = 32 - bits; i < 32; i++) {
            if (isSetBit(value_1.bits[b], i)) {
                result->bits[b+1] = setBit(result->bits[b+1], count);
                count++;
            }
        }
    }

    return 0;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int credit = 0;
    for (int b = 0; b < 3; b++) {
        for (int i = 0; i < 32; i++) {
            int check_value_1 = isSetBit(value_1.bits[b], i);
            int check_value_2 = isSetBit(value_2.bits[b], i);

            if (!credit && check_value_1 && !check_value_2) {
                result->bits[b] = setBit(result->bits[b], i);
            } else if (credit && check_value_1 && !check_value_2) {
                credit = 0;
            } else if (!credit && !check_value_1 && check_value_2) {
                result->bits[b] = setBit(result->bits[b], i);
                credit = 1;
            } else if (credit && !check_value_1 && !check_value_2) {
                result->bits[b] = setBit(result->bits[b], i);
            } else if (credit && check_value_1 && check_value_2) {
                result->bits[b] = setBit(result->bits[b], i);
            }
        }
    }
    return 0;
}


int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int scaling_arr_1[2] = {0};
    int scaling_arr_2[2] = {0};
    scaling_factor(value_1.bits[3], scaling_arr_1);
    scaling_factor(value_2.bits[3], scaling_arr_2);

    int scaling = scaling_arr_1[0] - scaling_arr_2[0];
    // scaling_arr_1[1] == scaling_arr_2[1];


    int newRank = 0;
    for (int b = 0; b < 3; b++) {
        for (int i = 0; i < 32; i++) {

            int check_value_1 = isSetBit(value_1.bits[b], i);
            int check_value_2 = isSetBit(value_2.bits[b], i);

            int twoUnits = check_value_1 == 1 && check_value_2 == 1;
            int twoZero = check_value_1 == 0 && check_value_2 == 0;

            if (newRank && twoZero ) {
                result->bits[b] = setBit(result->bits[b], i);
                newRank = 0;
            } else if (newRank && twoUnits) {
                result->bits[b] = setBit(result->bits[b], i);
                newRank = 1;
            } else if (newRank && !twoUnits && !twoZero) {
                newRank = 1;
            } else if (!newRank && !twoUnits && !twoZero) {
                result->bits[b] = setBit(result->bits[b], i);
            } else if (!newRank && twoUnits) {
                newRank = 1;
            }
        }
    }
    return 0;
}

int main() {
    s21_decimal x = {maxInt, 0, 0, 1835008};
    s21_decimal y = {0, 0, 0, 0};
    int arr[2];
    // s21_decimal r = y;
    s21_decimal z = {0,0,0,2148499456};
    s21_sub(x, y, &z);
    scaling_factor(z.bits[3], arr);
    printf("%u %u", arr[0], arr[1]);
    // shift(x, &z, 31);
    // for (int i = 3; i > -1; i--) {
    //     for (int n = 31; n > -1; n--) {
    //     printf("%d", isSetBit(z.bits[i], n));
    //     }
    //     printf(" ");
    // }
    // printf("\n");
    return 0;
}

#include <stdio.h>

unsigned int maxInt = 4294967295;

typedef struct {
    unsigned int bits[4];
} s21_decimal;

// провкрка бита
int isSetBit(int number, int index) {
    return (number&(1<<index))!=0;
}

// установка бита в 1
int setBit(int number, int index) {
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



int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    for (int i = 0; i < 3; i++) {
        unsigned long long sum = value_1.bits[i];
        sum += value_2.bits[i];
        if (sum <= maxInt) {
            result->bits[i] += value_1.bits[i] + value_2.bits[i];
        } else {
            result->bits[i] = maxInt;
            result->bits[i+1] = value_1.bits[i] + value_2.bits[i] - maxInt;
        }
        // printf("%u\n", result->bits[i]);
    }
    // unsigned long long sum = value_1.bits[i] + value_2.bits[i];
    // // if (sum > maxInt) {
    // //     result->bits[i] = sum - maxInt;
    // //     result->bits[i] = maxInt;
    // // }
    // result->bits[0] = 10;

    // }
    // result->bits[0] = value_1.bits[0] + value_2.bits[0];

    // printf("%u", result->bits[0]);

    // printf("%u", result.bits[0]);
}

int main() {
    s21_decimal x = {4294967294, 4294967294, 0, 0};
    s21_decimal y = {2,2,4294967294,0};
    // s21_decimal r = y;
    s21_decimal z = {0,0,0,0};
    s21_add(x, y, &z);
    for (int i = 2; i > -1; i--) {
        for (int n = 31; n > -1; n--) {
        printf("%d", isSetBit(z.bits[i], n));
        }
        printf(" ");
    }
    printf("\n");
    return 0;
}

#include <stdio.h>

unsigned int maxInt = 4294967295;

typedef struct {
    unsigned int bits[4];
} s21_decimal;

// провекрка бита
int isSetBit(int number, int index) {
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


int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int newRank = 0;
    for (int b = 0; b < 3; b++) {
        for (int i = 0; i < 32; i++) {
            int twoUnits = isSetBit(value_1.bits[b], i) == 1 && isSetBit(value_2.bits[b], i) == 1;
            int twoZero = isSetBit(value_1.bits[b], i) == 0 && isSetBit(value_2.bits[b], i) == 0;
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
}

int main() {
    s21_decimal x = {1835008, 0, 0, 0};
    s21_decimal y = {0, 0, 0, 0};
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

00000000 00011100 0000000000000000
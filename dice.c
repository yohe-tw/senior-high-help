#include <stdio.h>
#include <stdlib.h>

int globalarray[60];

// if equal, return the number, else return 0, checknum is to check how many edge could approach, the value is 2~4
int checkequal(int high, int wide, int order[], int checknum) {
    //for(int i = 0; i < 2 * (high + wide - 2); i++) printf("%d ", order[i]);
    int sum = 0, sum1 = 0;
    for(int i = 0; i < high; i++) sum += order[i];
    for(int i = high - 1; i < high + wide - 1; i++) sum1 += order[i];
    if(sum != sum1) return 0;
    //printf("sum2: %d\n", sum);
    if(checknum == 2) return sum;
    sum = 0;
    for(int i = high + wide - 2; i < high * 2 + wide - 2; i++) sum += order[i];
    if(sum != sum1) return 0;
    //printf("sum3: %d\n", sum);
    if(checknum == 3) return sum;
    sum1 = 0;
    for(int i = high * 2 + wide - 3; i < high * 2 + wide * 2 - 4; i++) sum1 += order[i];
    sum1 += order[0];
    if(sum != sum1) return 0;
    //printf("sum4: %d\n", sum);
    globalarray[sum] += 1;
    
    if(sum == 3) {
        for(int i = 0; i < 2 * (high + wide - 2); i++) printf("%d ", order[i]);printf("\n");
    }
    return sum;
}

void fill(int dice[28][3], int order[], int high, int wide, int fillnum) {
    //for(int i = 0; i < 2 * (high + wide - 2); i++) printf("%d ", order[i]);printf("\n");
    if(fillnum == high * 2 + wide * 2 - 4) {
        //printf("debug");
        checkequal(high, wide, order, 4);
        return;
    } else if (fillnum == high * 2 + wide - 2 || fillnum == high * 2 + wide - 1) {
        if(!checkequal(high, wide, order, 3)) return;
    } else if(fillnum == high + wide) {
        if(!checkequal(high, wide, order, 2)) return;
    }
    for(int i = 0; i < 28; i++) {
        if(dice[i][2] == 1) continue;
        dice[i][2] = 1;
        order[fillnum] = dice[i][0];
        order[fillnum + 1] = dice[i][1];
        fill(dice, order, high, wide, fillnum + 2);
        if(dice[i][0] != dice[i][1]) {
            order[fillnum + 1] = dice[i][0];
            order[fillnum] = dice[i][1];    
            fill(dice, order, high, wide, fillnum + 2);
        }
        
        
        dice[i][2] = 0;
    }
}

int main() {
    int high = 4, wide = 4;
    int dice[28][3], order[2 * (high + wide - 2)], recurnum[28];
    int count = 0;
    for(int i=0; i<=6; i++) for(int j=i; j<=6; j++) {
        dice[count][0] = i;
        dice[count][1] = j;
        dice[count][2] = 0; // if 0 then it have not been put, else it put
        count++;
    }
    for(int i = 0; i < 60; i++) globalarray[i] = 0;
    fill(dice, order, high, wide, 0);
    for(int i = 0; i < 60; i++) printf("%d ", globalarray[i]);
    return 0;
}
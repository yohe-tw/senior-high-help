#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int globalarray[60];

// if equal, return the number, else return 0, checknum is to check how many edge could approach, the value is 1~4
bool checkequal(int high, int wide, int *order, int number, int checknum) {
    //for(int i = 0; i < 2 * (high + wide - 2); i++) printf("%d ", order[i]);
    
    int sum = 0;
    for(int i = 0; i < high; i++) sum += order[i];
    if(number != sum) return false;
    if(checknum == 1) return true;
    sum = 0;
    for(int i = high - 1; i < high + wide - 1; i++) sum += order[i];
    if(number != sum) return false;
    if(checknum == 2) return true;
    sum = 0;
    for(int i = high + wide - 2; i < high * 2 + wide - 2; i++) sum += order[i];
    if(number != sum) return false;
    
    if(checknum == 3) return true;
    sum = 0;
    for(int i = high * 2 + wide - 3; i < high * 2 + wide * 2 - 4; i++) sum += order[i];
    sum += order[0];
    if(number != sum) return false;
    return true;
}

bool checkgroups(int high, int wide, int *order, int number, int fillnum) {
    //for(int i = 0; i < (2 * (high + wide - 2)) * 1; i++) printf("%d ", order[i]); printf("\n");
    if(fillnum == 0) return true;
    int groupnum = fillnum / (2 * (high + wide - 2));
    int lastnum = fillnum % (2 * (high + wide - 2));
    if(lastnum == 0) return checkequal(high, wide, order + ((groupnum - 1) * (2 * (high + wide - 2))), number, 4);


    if (lastnum == high * 2 + wide - 2 || lastnum == high * 2 + wide - 1) return checkequal(high, wide, order + (groupnum * (2 * (high + wide - 2))), number, 3);
    else if(lastnum == high + wide) return checkequal(high, wide, order + (groupnum * (2 * (high + wide - 2))), number, 2);
    else if(lastnum == high || lastnum == high + 1) return checkequal(high, wide, order + (groupnum * (2 * (high + wide - 2))), number, 1);
    else return true;
}

bool fill(int dice[28][3], int order[], int high, int wide, int number, int guess, int fillnum) {
    //for(int i = 0; i < 2 * (high + wide - 2); i++) printf("%d ", order[i]);printf("\n");
    if(checkgroups(high, wide, order, number, fillnum)) {
        if(fillnum == (2 * (high + wide - 2)) * guess) return true;
    }
    else return false;
    for(int i = 0; i < 28; i++) {
        if(dice[i][2] == 1) continue;
        bool flag;
        dice[i][2] = 1;
        order[fillnum] = dice[i][0];
        order[fillnum + 1] = dice[i][1];
        flag = fill(dice, order, high, wide, number, guess, fillnum + 2);
        if(flag) return true;
        if(dice[i][0] != dice[i][1]) {
            order[fillnum + 1] = dice[i][0];
            order[fillnum] = dice[i][1];
            flag = fill(dice, order, high, wide, number, guess, fillnum + 2);
            if(flag) return true;    
        }
        dice[i][2] = 0;
    }
    return false;
}

int main() {
    printf("input high, wide, edge distance and guess groups (each number splited by space):");
    int high = 5, wide = 5, number = 20, guess = 2;
    scanf("%d%d%d%d", &high, &wide, &number, &guess);
    int dice[28][3], order[(2 * (high + wide - 2)) * guess];
    int count = 0;
    for(int i=0; i<=6; i++) for(int j=i; j<=6; j++) {
        dice[count][0] = i;
        dice[count][1] = j;
        dice[count][2] = 0; // if 0 then it have not been put, else it put
        count++;
    }
    
    time_t start = time(NULL);
    bool flag = fill(dice, order, high, wide, number, guess, 0);
    printf("time cost: %d s\n", time(NULL) - start);
    if(flag) {
        printf("group found, one of the group:\n");
        for(int i = 0; i < guess; i++) {
            for(int j = 0; j < 2 * (high + wide - 2); j++) printf("%d ", order[(2 * (high + wide - 2)) * i + j]);
            printf("\n");
        }
    } else printf("no groups found.\n");
    printf("press any bottom to terminate.\n");
    scanf("%d", &count);
    return 0;
}
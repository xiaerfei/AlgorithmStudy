//
//  SortHelper.c
//  算法学习
//
//  Created by xiaerfei on 2017/2/13.
//  Copyright © 2017年 二哥. All rights reserved.
//

#include "SortHelper.h"
#include "stdlib.h"
#include "time.h"
#include <string.h>

#define bool int
#define false 0
#define true 1


void swap(int *a,int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArr(int arr[],int n) {
    for (int i = 0; i < n; i ++) {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

bool isSort(int *arr,int n) {
    
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}
/*
    产生 n 个[rangL,rangR]之间的随机数
 */
int *generateRandomArray(int n ,int rangL, int rangR) {
    
    int* arr = (int *)malloc(sizeof(int)*n);
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand()%(rangR - rangL + 1) + rangL;
    }
    return arr;
}

int *generateNoRepeatRandomArray(int n ,int rangL, int rangR) {
    int* arr = (int *)malloc(sizeof(int)*n);
    srand((unsigned)time(NULL));
    
    for (int i = 0; i < n;) {
        int value = rand()%(rangR - rangL + 1) + rangL;
        int canAdd = 1;
        for (int j = 0; j <= i; j ++) {
            if (arr[j] == value) {
                canAdd = 0;
                break;
            }
        }
        if (canAdd) {
            arr[i] = value;
            i++;
        }
    }
    
    return arr;
}

int *copyGenerateRandomArray(int *arr,int n) {
    int* arrC = (int *)malloc(sizeof(int)*n);
    memcpy(arrC, arr, sizeof(int)*n);
    return arrC;
}
/*
    产生倒叙的数组
 */
int *generateReverseArray(int n ) {
    int* arr = (int *)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i ++) {
        arr[i] = n - i;
    }
    return arr;
}
/*
    产生有序的数组
 */
int *generateSequenceArray(int n ) {
    int* arr = (int *)malloc(sizeof(int)*n);
    for (int i = 1; i <= n; i ++) {
        arr[i] = i;
    }
    return arr;
}
/*
    产生近乎有序的数组  random 为 打乱的数量
 */
int *generateRandomSequenceArray(int n,int random ) {
    int* arr = (int *)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i ++) {
        arr[i] = i;
    }
    
    srand((unsigned)time(NULL));
    for (int i = 0; i < random; i ++) {
        int l = rand() % ( n - 1 );
        int r = rand() % ( n - 1 );
        swap(&arr[l],&arr[r]);
    }
    return arr;
}

void testSort(char *s ,void(*sort)(int[],int),int *arr,int n) {
    
    clock_t start = clock();
    sort(arr,n);
    clock_t end   = clock();
    
    
    if (isSort(arr, n) == false) {
        printf("sortname:%s\t sort failed\n",s);
    } else {
        printf("sortname:%s\t sorttime: %fs\n",s,(double)(end - start)/CLOCKS_PER_SEC);
    }
}





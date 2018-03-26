//
//  BubbleSort.c
//  算法学习
//
//  Created by rongyu100 on 2017/2/15.
//  Copyright © 2017年 二哥. All rights reserved.
//

#include "BubbleSort.h"
#include "SortHelper.h"



void bubbleSort(int arr[],int n) {
    for (int i = 0; i < n ; i ++) {
        for (int j = 1; j < n-i; j ++) {
            if (arr[j] < arr[j-1]) {
                swap(&arr[j], &arr[j-1]);
            }
        }
        printArr(arr, n);
    }
}

void bubbleSort2(int arr[],int n) {
    int flag = 1;
    for (int i = 0; i < n && flag ; i ++) {
        flag = 0;
        for (int j = 1; j < n - i; j ++) {
            
            if (arr[j] < arr[j-1]) {
                flag = 1;
                swap(&arr[j], &arr[j-1]);
            }
        }
    }
}

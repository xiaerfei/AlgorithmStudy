//
//  InsertSort.c
//  算法学习
//
//  Created by xiaerfei on 2017/1/26.
//  Copyright © 2017年 二哥. All rights reserved.
//

#include "InsertSort.h"
#include "SortHelper.h"

void insertSort(int arr[],int n) {
    
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && (arr[j] < arr[j - 1]); j--) {
            swap(&arr[j], &arr[j-1]);
            
        }
    }
}

/**
 优化后的插入排序

 @param arr 数组
 @param n 元素的个数
 */
void insertSort2(int arr[],int n) {
    
    for (int i = 1; i < n; i++) {
        
        int e = arr[i];
        int j;
        for (j = i; j > 0 && arr[j - 1] > e; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = e;
    }
}


void insertSort3(int arr[],int n) {
    
    int gap = 1;
    for (int j = gap; j < n; j ++) {
        if (arr[j] < arr[j -gap]) {
            int temp = arr[j];
            int k = j - gap;
            while (k >= 0 && arr[k] > temp) {
                arr[k + gap] = arr[k];
                k -= gap;
            }
            
            arr[k+gap] = temp;
        }
    }
}


void insertSort4(int arr[],int n) {
    
    int gap = 1;
    
    for (int i = gap; i < n; i++) {
        
        int e = arr[i];
        int j = i - gap;
        for (; j >= 0 && arr[j] > e; j-=gap) {
            arr[j + gap] = arr[j];
        }
        arr[j + gap] = e;
    }
}




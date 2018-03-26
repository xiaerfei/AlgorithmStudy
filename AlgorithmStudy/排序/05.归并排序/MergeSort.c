//
//  MergeSort.c
//  算法学习
//
//  Created by rongyu100 on 2017/2/17.
//  Copyright © 2017年 二哥. All rights reserved.
//

#include "MergeSort.h"
#include "stdlib.h"

#define MIN(x,y) (x) > (y) ? (y) : (x)

void _merge(int arr[],int l, int mid,int r) {
    int count = r-l+1;
    int *ta = (int *)malloc(sizeof(int) * count);
//    if (l == 0 && mid == 1249999 && r == 2499999) {
//        printf("ok !");
//    }
    for (int i = l; i <= r; i++) {
        int a = i - l;
        ta[a] = arr[i];
    }
    
    int i = l,j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (i > mid) {
            arr[k] = ta[j - l];
            j ++;
        } else if (j > r) {
            arr[k] = ta[i - l];
            i ++ ;
        } else if (ta[i - l] < ta[j - l]) {
            arr[k] = ta[i-l];
            i ++;
        } else {
            arr[k] = ta[j - l];
            j ++;
        }
    }
    free(ta);
    
    
}

void __mergeSort(int arr[],int l,int r) {
    
    int mid = l + (r - l)/2;
    
    if (l >= r) {
        return;
    }
    
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);
    
    _merge(arr, l, mid, r);
}

void mergeSort(int arr[],int n) {
    __mergeSort(arr, 0, n-1);
}

void mergeSortBackUp(int arr[],int n) {
    
    for (int size = 1; size <= n; size += size ) {
        for (int i = 0; i + size < n; i += (size + size)) {
            _merge(arr, i, i + size - 1, MIN(i + size + size - 1,n-1));
        }
    }
}
















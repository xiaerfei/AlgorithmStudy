//
//  QuickSort.c
//  算法学习
//
//  Created by rongyu100 on 2017/2/23.
//  Copyright © 2017年 二哥. All rights reserved.
//

#include "QuickSort.h"
#include "SortHelper.h"

#include "stdlib.h"
#include "time.h"

// p [l...p-1] [p] [p+1...r]
int __partition(int arr[],int l,int r) {
   
    int v = arr[l];
    
    int j = l;
    //[l+1...j]  [j+1...i) 
    for (int i = l+1; i <= r; i++) {
        if (arr[i] < v) {
            swap(&arr[j +1], &arr[i]);
            j ++;
        }
    }
    swap(&arr[l], &arr[j]);
    return j;
}

void __quickSort(int arr[],int l,int r) {
    if (l >= r) {
        return;
    }
    int p = __partition(arr,l,r);
    __quickSort(arr, l, p-1);
    __quickSort(arr, p+1, r);
}

void quickSort(int arr[],int n) {
    __quickSort(arr,0,n-1);
}

/*  随机化的快速排序
 
    但我们很快就发现，这样的一个快排，在面临有序或者近乎有序的数组时，会退化成为一个O(n^2)的算法。
    于是我们使用了一个很简单的随机选取pivot的方式来处理这个问题。这步随机化让快速排序的时间期望成
    为了O(nlogn)，并且只有极低的概率退化为O(n^2)。关于这一点，背后的数学证明比较复杂，对背后的数
    学不感兴趣的同学，只要相信这个结论就好了。事实上，n不需要太大，在100这个量级，其退化成O(n^2)
    算法的概率就已经低于大家彩票中大奖的概率了：）
 
 
    快速排序优化 __partition_00 中 V的值 随机生成
 
    对于
    近乎有序的数组 速度较快
    无序数组      耗时基本一致
    1百万个    优化前        优化后
    近乎有序    2.720384s   0.158201s
    无序       0.204638s   0.216107s
 */

// p [l...p-1] [p] [p+1...r]
int __partition_00(int arr[],int l,int r) {
    
    swap(&arr[l], &arr[rand()%(r-l+1) + l]);
    
    int v = arr[l];
    
    int j = l;
    //[l+1...j]  [j+1...i)
    for (int i = l+1; i <= r; i++) {
        if (arr[i] < v) {
            swap(&arr[j +1], &arr[i]);
            j ++;
        }
    }
    swap(&arr[l], &arr[j]);
    return j;
}

void __quickSort_00(int arr[],int l,int r) {
    if (l >= r) {
        return;
    }
    
    int p = __partition_00(arr,l,r);
    
    __quickSort_00(arr, l, p-1);
    __quickSort_00(arr, p+1, r);
}

void quickSort_00(int arr[],int n) {
    srand((unsigned)time(NULL));
    __quickSort_00(arr,0,n-1);
}

/*  
 *  双路快速排序
 */

int __partition_twoWays(int arr[],int l,int r) {
    swap(&arr[l], &arr[rand()%(r-l+1) + l]);
    int v = arr[l];
    // arr[l+1...i-1] <= v   和 arr[j...r] >= v
    int i = l + 1;
    int j = r;
    while (1) {
        while (i <= r && arr[i] < v) { i ++; }
        while (j >= l+1 && arr[j] > v) { j --; }
        if (j <= i) { break; }
        swap(&arr[i], &arr[j]);
        i++;
        j--;
    }
    swap(&arr[l], &arr[j]);
    return j;
}


void __quickSort_twoWays(int arr[],int l,int r) {
    if (l >= r) {
        return;
    }
    int p = __partition_twoWays(arr,l,r);
    
    __quickSort_twoWays(arr, l, p-1);
    __quickSort_twoWays(arr, p+1, r);
}


void quickSort_twoWays(int arr[],int n) {
    srand((unsigned)time(NULL));
    __quickSort_twoWays(arr,0,n-1);
}

/*
 *  三路快速排序
 */
void __quickSort_threeWays(int arr[],int l,int r) {
    if (l >= r) {
        return;
    }
    swap(&arr[l], &arr[rand()%(r-l+1) + l]);
    int v = arr[l];
    // arr[l+1...lt] < v 、 arr[lt+1...i-1] == v 和 arr[gt...r] > v
    int lt = l;
    int i  = l + 1;
    int gt = r + 1;
    while (i < gt) {
        if (arr[i] < v) {
            swap(&arr[i], &arr[lt + 1]);
            i++;
            lt++;
        } else if (arr[i] > v) {
            swap(&arr[i], &arr[gt - 1]);
            gt --;
        } else {
            i ++;
        }
    }
    swap(&arr[l], &arr[lt]);
    __quickSort_threeWays(arr, l, lt-1);
    __quickSort_threeWays(arr, gt, r);
}

void quickSort_threeWays(int arr[],int n) {
    srand((unsigned)time(NULL));
    __quickSort_threeWays(arr,0,n-1);
}


void testQuictSort() {
    int arr[] = {5,8,6,2,3,1,7,4};
    
    quickSort(arr, 8);
    
}




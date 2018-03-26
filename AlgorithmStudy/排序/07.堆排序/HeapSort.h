//
//  HeapSort.h
//  算法学习
//
//  Created by xiaerfei on 2017/2/28.
//  Copyright © 2017年 二哥. All rights reserved.
//

#ifndef HeapSort_h
#define HeapSort_h

#include <stdio.h>

typedef struct Heap_sort_max_s Heap_sort_max;

typedef struct Heap_sort_max_s {
    int count;                              //-> 当前堆内数据的大小
    int capacity;                           //-> 当前堆的容量
    void (*insert)(Heap_sort_max *,int);    //-> 插入函数
    int (*extract_max)(Heap_sort_max *);    //-> 输出一个最大值
    int *item;                              //-> 数组指针
    void (*print_to_dot)(Heap_sort_max *);  //-> 生成 dot 语言 函数
} Heap_sort_max;

void heap_sort(int arr[],int n);
void heapify_sort(int arr[],int n);
void heap_autochthonous_sort(int arr[],int n);

void test_heap_sort_max();







/// 最大堆
void heapSortMax(int arr[],int n);
/// 最小堆
void heapSortMin(int arr[],int n);
#endif /* HeapSort_h */

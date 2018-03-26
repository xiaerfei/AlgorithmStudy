//
//  HeapSort.c
//  算法学习
//
//  Created by xiaerfei on 2017/2/28.
//  Copyright © 2017年 二哥. All rights reserved.
// 二叉堆

#include "HeapSort.h"
#include "SortHelper.h"
#include <stdlib.h>
#include <assert.h>

void __shiptUp(int arr[],int n,int k) {
    while (2*k + 1 < n) {
        
        int j = 2*k + 1;
        
        if (j + 1 < n && arr[j] > arr[j + 1]) {
            j += 1;
        }
        
        if (arr[k] <= arr[j]) {
            break;
        }
        
        swap(&arr[j], &arr[k]);
        k = j;
    }
}

void __shiptDown(int arr[],int n,int k) {
    while (2*k + 1 < n) {
        int j = 2*k + 1;
        if (j + 1 < n && arr[j] < arr[j + 1]) {
            j += 1;
        }
        if (arr[k] >= arr[j]) {
            break;
        }
        swap(&arr[j], &arr[k]);
        k = j;
    }
}

void heapSortMin(int arr[],int n) {
    for (int i = (n-1)/2; i >= 0; i --) {
        __shiptUp(arr, n, i);
    }
    
    for (int i = n-1; i > 0; i --) {
        swap(&arr[0], &arr[i]);
        __shiptUp(arr, i, 0);
    }
}

void heapSortMax(int arr[],int n) {
    for (int i = (n-1)/2; i >= 0; i --) {
        __shiptDown(arr, n, i);
    }
    
    for (int i = n-1; i > 0; i --) {
        swap(&arr[0], &arr[i]);
        __shiptDown(arr, i, 0);
    }
}


#pragma mark -


static void heap_sort_max_shift_up(Heap_sort_max *heap_sort_max,int k) {
    while (k > 1 && heap_sort_max->item[k/2] < heap_sort_max->item[k]) {
        swap(&heap_sort_max->item[k/2], &heap_sort_max->item[k]);
        k /= 2;
    }
}

static void heap_sort_max_shift_down(Heap_sort_max *heap_sort_max,int k) {
    while (2*k <= heap_sort_max->count) {
        int index = 2*k;
        if (index + 1 <= heap_sort_max->count && heap_sort_max->item[index + 1] > heap_sort_max->item[index]) {
            index += 1;
        }
        if (heap_sort_max->item[k] > heap_sort_max->item[index]) {
            break;
        }
        
        swap(&heap_sort_max->item[k], &heap_sort_max->item[index]);
        k = index;
    }
}

static void insert(Heap_sort_max* heap_sort_max,int item) {
    if (heap_sort_max->count > heap_sort_max->capacity) {
        return;
    }
    heap_sort_max->count += 1;
    heap_sort_max->item[heap_sort_max->count] = item;
    heap_sort_max_shift_up(heap_sort_max, heap_sort_max->count);
}

static int extract_max(Heap_sort_max* heap_sort_max) {
    assert(heap_sort_max->count > 0);
    int ret = heap_sort_max->item[1];
    
    swap(&heap_sort_max->item[1], &heap_sort_max->item[heap_sort_max->count]);
    heap_sort_max->count -= 1;
    
    heap_sort_max_shift_down(heap_sort_max, 1);
    
    return ret;
}


static void print_to_dot(Heap_sort_max *heap_sort_max) {
    printf("\n<---------- dot start ---------->\n\n");
    printf("digraph heap {\nnode[shape=circle];\nnodesep=0.3;\n");
    int count = heap_sort_max->count;
    for (int i = 1; i <= count; i++) {
        int leftIndex = 2 * i;
        int rightIndex = 2 * i + 1;
        if (leftIndex <= count) {
            printf("\t%d -> %d;\n",heap_sort_max->item[i],heap_sort_max->item[leftIndex]);
        }
        if (rightIndex <= count) {
            printf("\t%d -> %d;\n",heap_sort_max->item[i],heap_sort_max->item[rightIndex]);
        }
    }
    printf("}\n");
    printf("\n\n<---------- dot end ---------->\n");
}

static Heap_sort_max create_heap_sort_max(int capacity) {
    
    int *p = (int *)malloc(sizeof(int) * capacity);
    for (int i = 0; i < capacity; i++) {
        p[i] = 0;
    }
    Heap_sort_max heap_sort_max = {
        .count = 0,
        .capacity = capacity,
        .insert = insert,
        .extract_max = extract_max,
        .item = p,
        .print_to_dot = print_to_dot
    };
    return heap_sort_max;
}

static void free_heap_sort_max(Heap_sort_max *heap_sort_max) {
    free(heap_sort_max->item);
}



void heap_sort(int arr[],int n) {
    Heap_sort_max heap_sort_max = create_heap_sort_max(n + 1);
    
    for (int i = 0; i < n; i++) {
        heap_sort_max.insert(&heap_sort_max,arr[i]);/// O(nlogn)
    }
    
    for (int i = n-1; i >=0; i--) {
        arr[i] = ((int (*)(Heap_sort_max *heap_sort_max))heap_sort_max.extract_max)(&heap_sort_max);
    }
}

void heapify_sort(int arr[],int n) {
    Heap_sort_max heap_sort_max = create_heap_sort_max(n + 1);
    for (int i = 0; i < n; i ++) {
        heap_sort_max.item[i+1] = arr[i];
    }
    heap_sort_max.count = n;
    
    for (int i = n/2; i >= 1; i--) {
        heap_sort_max_shift_down(&heap_sort_max, i);/// O(n)
    }
    
    for (int i = n-1; i >=0; i--) {
        arr[i] = ((int (*)(Heap_sort_max *heap_sort_max))heap_sort_max.extract_max)(&heap_sort_max);
    }
}

#pragma mark -
// 顶结点的索引从 0 开始
static void heap_autochthonous_sort_shift_down(int arr[],int n,int k) {
    while ((2*k + 1) < n) {
        int index = 2*k + 1; // 取左孩子索引
        if (index + 1 < n && arr[index + 1] > arr[index]) { index++; }
        if (arr[k] > arr[index]) { break; }
        swap(&arr[k], &arr[index]);
        k = index;
    }
}

/// 原地堆排序 空间O(1)
void heap_autochthonous_sort(int arr[],int n) {
    /// heapify
    for (int i = (n-1)/2; i >= 0; i--) {
        heap_autochthonous_sort_shift_down(arr, n, i);
    }
    
    for (int i = n-1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heap_autochthonous_sort_shift_down(arr, i, 0);
    }
}

#pragma mark - test
void test_heap_sort_max() {
    
    int *a = generateNoRepeatRandomArray(20,0,100);
    
    Heap_sort_max heap_sort_max = create_heap_sort_max(50);
    
    for (int i = 0; i < 20; i++) {
        heap_sort_max.insert(&heap_sort_max,a[i]);
    }
    
    void (*print_to_dot)(Heap_sort_max *heap_sort_max) = heap_sort_max.print_to_dot;
    print_to_dot(&heap_sort_max);
    
    int (*extract_max)(Heap_sort_max *heap_sort_max) = heap_sort_max.extract_max;
    for (int i = 1; i <= 20; i ++) {
        printf("%d ",extract_max(&heap_sort_max));
    }
    
    free_heap_sort_max(&heap_sort_max);
}






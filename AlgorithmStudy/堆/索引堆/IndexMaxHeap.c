//
//  IndexMaxHeap.c
//  算法学习
//
//  Created by xiaerfei on 2018/3/26.
//  Copyright © 2018年 二哥. All rights reserved.
//

#include "IndexMaxHeap.h"
#include "SortHelper.h"
#include <stdlib.h>
#include <assert.h>


typedef struct Index_max_heap_s Index_max_heap;

typedef struct Index_max_heap_s {
    int count;                                      //-> 当前堆内数据的大小
    int capacity;                                   //-> 当前堆的容量
    void (*insert)(Index_max_heap *,int,int);       //-> 插入函数
    int (*extract_max)(Index_max_heap *);           //-> 输出一个最大值
    int (*extract_max_index)(Index_max_heap *);     //-> 输出一个最大值的索引
    int (*get_item_by_index)(Index_max_heap *,int); //-> 返回一个指定的索引值
    void (*change_item_by_index)(Index_max_heap *,int,int); //-> 更改指定索引的值
    int *item;                                      //-> 数组指针
    int *indexs;                                    //-> 数组指针 索引
    int *reverses;                                  //-> 数组指针 反向查找索引
    void (*print_to_dot)(Index_max_heap *);         //-> 生成 dot 语言 函数
} Index_max_heap;


static void index_max_heap_shift_up(Index_max_heap *index_max_heap,int k) {
    while (k > 1 && index_max_heap->item[index_max_heap->indexs[k/2]] < index_max_heap->item[index_max_heap->indexs[k]]) {
        /// 仅交换 index
        swap(&index_max_heap->indexs[k/2], &index_max_heap->indexs[k]);
        index_max_heap->reverses[index_max_heap->indexs[k/2]] = k/2;
        index_max_heap->reverses[index_max_heap->indexs[k]] = k;
        k /= 2;
    }
}

static void index_max_heap_shift_down(Index_max_heap *index_max_heap,int k) {
    while (2*k <= index_max_heap->count) {
        int index = 2*k;
        if (index + 1 <= index_max_heap->count && index_max_heap->item[index_max_heap->indexs[index + 1]] > index_max_heap->item[index_max_heap->indexs[index]]) {
            index += 1;
        }
        if (index_max_heap->item[index_max_heap->indexs[k]] > index_max_heap->item[index_max_heap->indexs[index]]) {
            break;
        }
        
        swap(&index_max_heap->indexs[k], &index_max_heap->indexs[index]);
        index_max_heap->reverses[index_max_heap->indexs[k]] = k;
        index_max_heap->reverses[index_max_heap->indexs[index]] = index;

        k = index;
    }
}

static void insert(Index_max_heap* index_max_heap,int index,int item) {
    if (index_max_heap->count > index_max_heap->capacity) {
        return;
    }
    index_max_heap->count += 1;
    index_max_heap->item[index_max_heap->count] = item;
    index_max_heap->reverses[index] = index_max_heap->count;
    index_max_heap->indexs[index_max_heap->count] = index;
    index_max_heap_shift_up(index_max_heap, index_max_heap->count);
}

static int extract_max(Index_max_heap* index_max_heap) {
    assert(index_max_heap->count > 0);
    int ret = index_max_heap->item[index_max_heap->indexs[1]];
    
    swap(&index_max_heap->indexs[1], &index_max_heap->indexs[index_max_heap->count]);
    index_max_heap->reverses[index_max_heap->indexs[1]] = 1;
    index_max_heap->reverses[index_max_heap->indexs[index_max_heap->count]] = 0;
    
    index_max_heap->count -= 1;
    
    index_max_heap_shift_down(index_max_heap, 1);
    
    return ret;
}

static int extract_max_index(Index_max_heap* index_max_heap) {
    assert(index_max_heap->count > 0);
    int ret = index_max_heap->indexs[1];
    
    swap(&index_max_heap->indexs[1], &index_max_heap->indexs[index_max_heap->count]);
    index_max_heap->reverses[index_max_heap->indexs[1]] = 1;
    index_max_heap->reverses[index_max_heap->indexs[index_max_heap->count]] = 0;

    index_max_heap->count -= 1;
    
    index_max_heap_shift_down(index_max_heap, 1);
    
    return ret;
}

static int contain(Index_max_heap* index_max_heap,int i) {
    assert(i + 1 >= 1 && i + 1 <= index_max_heap->capacity );
    return index_max_heap->reverses[i + 1] != 0;
}

static int get_item_by_index(Index_max_heap* index_max_heap,int index) {
    assert(contain(index_max_heap,index));
    return index_max_heap->item[index + 1];
}

static void change_item_by_index(Index_max_heap* index_max_heap,int index,int item) {
    assert(contain(index_max_heap,index));
    index += 1;
    index_max_heap->item[index] = item;
    
//    for (int i = 1; i <= index_max_heap->count; i++) {
//        if (index_max_heap->indexs[i] == index) {
//            index_max_heap_shift_up(index_max_heap, i);
//            index_max_heap_shift_down(index_max_heap, i);
//            return;
//        }
//    }
    
    int i = index_max_heap->reverses[index];
    index_max_heap_shift_up(index_max_heap, i);
    index_max_heap_shift_down(index_max_heap, i);
}

static void print_to_dot(Index_max_heap *index_max_heap) {
    printf("\n<---------- dot start ---------->\n\n");
    printf("digraph heap {\nnode[shape=circle];\nnodesep=0.3;\n");
    int count = index_max_heap->count;
    for (int i = 1; i <= count; i++) {
        int leftIndex = 2 * i;
        int rightIndex = 2 * i + 1;
        if (leftIndex <= count) {
            printf("\t%d -> %d;\n",index_max_heap->item[index_max_heap->indexs[i]],index_max_heap->item[index_max_heap->indexs[leftIndex]]);
        }
        if (rightIndex <= count) {
            printf("\t%d -> %d;\n",index_max_heap->item[index_max_heap->indexs[i]],index_max_heap->item[index_max_heap->indexs[rightIndex]]);
        }
    }
    printf("}\n");
    printf("\n\n<---------- dot end ---------->\n");
}


static Index_max_heap create_index_max_heap(int capacity) {
    
    int *item = (int *)malloc(sizeof(int) * (capacity + 1));
    int *indexs = (int *)malloc(sizeof(int) * (capacity + 1));
    int *reverses = (int *)malloc(sizeof(int) * (capacity + 1));
    for (int i = 0; i < capacity; i++) {
        item[i] = 0;
        indexs[i] = 0;
        reverses[i] = 0;
    }
    Index_max_heap index_max_heap = {
        .count = 0,
        .capacity = capacity,
        .insert = insert,
        .extract_max = extract_max,
        .extract_max_index = extract_max_index,
        .get_item_by_index = get_item_by_index,
        .change_item_by_index = change_item_by_index,
        .item = item,
        .indexs = indexs,
        .reverses = reverses,
        .print_to_dot = print_to_dot
    };
    return index_max_heap;
}


#pragma mark - test
void test_index_max_heap() {
    
//    int *a = generateNoRepeatRandomArray(20,0,100);
    
    int arr[] = { 31,2, 1,45,73, 69, 60, 59,91, 49,  43, 32,  29, 18,88, 17, 9,76, 6,  0};
    
    Index_max_heap index_max_heap = create_index_max_heap(50);
    
    for (int i = 0; i < 20; i++) {
        index_max_heap.insert(&index_max_heap,i,arr[i]);
    }
    
    void (*change_item_by_index)(Index_max_heap *index_max_heap,int,int) = index_max_heap.change_item_by_index;
    change_item_by_index(&index_max_heap,8,22);
    
    void (*print_to_dot)(Index_max_heap *index_max_heap) = index_max_heap.print_to_dot;
    print_to_dot(&index_max_heap);
    
    int (*extract_max)(Index_max_heap *index_max_heap) = index_max_heap.extract_max;
    for (int i = 1; i <= 20; i ++) {
        printf("%d, ",extract_max(&index_max_heap));
    }
}




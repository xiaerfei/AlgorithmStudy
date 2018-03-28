//
//  LeftistHeap.h
//  算法学习
//
//  Created by xiaerfei on 2018/2/6.
//  Copyright © 2018年 二哥. All rights reserved.
//

#ifndef LeftistHeap_h
#define LeftistHeap_h

#include <stdio.h>

typedef struct leftist_heap_s *leftist_heap_pt;

typedef struct leftist_heap_s {
    leftist_heap_pt left;
    leftist_heap_pt right;
    int data;
    int npl;
} leftist_heap_t;



leftist_heap_pt leftist_heap_merge(leftist_heap_pt h1,leftist_heap_pt h2);
leftist_heap_pt leftist_heap_push(leftist_heap_pt heap,int data);
leftist_heap_pt leftist_heap_pop(leftist_heap_pt heap);
void leftist_heap_destroy(leftist_heap_pt heap);


void leftist_heap_export_dot(leftist_heap_pt heap, char *filename, char *label);

#endif /* LeftistHeap_h */

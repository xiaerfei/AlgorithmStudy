//
//  SkewHeap.h
//  算法学习
//
//  Created by xiaerfei on 2018/2/6.
//  Copyright © 2018年 二哥. All rights reserved.
//

#ifndef SkewHeap_h
#define SkewHeap_h

#include <stdio.h>


typedef struct skew_heap_s *skew_heap_pt;

typedef struct skew_heap_s {
    skew_heap_pt left;
    skew_heap_pt right;
    int data;
} skew_heap_t;

skew_heap_pt skew_heap_merge(skew_heap_pt h1,skew_heap_pt h2);
skew_heap_pt skew_heap_push(skew_heap_pt heap,int data);
skew_heap_pt skew_heap_pop(skew_heap_pt heap);
void skew_heap_destroy(skew_heap_pt heap);


void skew_heap_export_dot(skew_heap_pt heap, char *filename, char *label);

#endif /* SkewHeap_h */

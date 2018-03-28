//
//  SkewHeap.c
//  算法学习
//
//  Created by xiaerfei on 2018/2/6.
//  Copyright © 2018年 二哥. All rights reserved.
//

/*
    斜堆
 
 
    http://mingnote.com/skew-heap-algorithm-in-c.html
 
 */

#include "SkewHeap.h"
#include <stdlib.h>


static void swap(skew_heap_pt p1,skew_heap_pt p2) {
    skew_heap_t tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}


skew_heap_pt skew_heap_merge(skew_heap_pt h1,skew_heap_pt h2) {
    
    if (h1 == NULL) { return h2; }
    if (h2 == NULL) { return h1; }
    /// 保证h1的优先级大于h2
    if (h1->data > h2->data) { swap(h1,h2); }
    
    h1->right = skew_heap_merge(h1->right, h2);
    
    skew_heap_pt tmp = h1->left;
    h1->left = h1->right;
    h1->right = tmp;
    return h1;
}

skew_heap_pt skew_heap_push(skew_heap_pt heap,int data) {
    skew_heap_pt node_heap = (skew_heap_pt)malloc(sizeof(skew_heap_t));
    if (node_heap == NULL) { return node_heap; }
    node_heap->left  = NULL;
    node_heap->right = NULL;
    node_heap->data  = data;
    return skew_heap_merge(heap, node_heap);
}

skew_heap_pt skew_heap_pop(skew_heap_pt heap) {
    if (heap == NULL) { return heap; }
    skew_heap_pt node_heap_left  = heap->left;
    skew_heap_pt node_heap_right = heap->right;
    free(heap);
    return skew_heap_merge(node_heap_left, node_heap_right);
}

void skew_heap_destroy(skew_heap_pt heap) {
    if (heap == NULL) { return; }
    
    skew_heap_destroy(heap->left);
    skew_heap_destroy(heap->right);
    
    free(heap);
}


void skew_heap_show(skew_heap_pt heap) {
    if (heap == NULL) { return; }
    skew_heap_show(heap->left);
    printf("%d ",heap->data);
    skew_heap_show(heap->right);
}

/* 打印节点计数变量 */
static int node_num = 0;

static void export_dot(skew_heap_pt heap, char *last_label) {
    /* 打印节点 */
    char node_name[10] = {0};
    sprintf(node_name, "n%d", node_num);
    if (heap == NULL) {
        printf("%s[style=invis];\n", node_name);
    }
    else {
        printf("%s[label=%d];\n", node_name, heap->data);
    }
    node_num++;
    
    /* 打印边 */
    if (last_label != NULL) {
        if (heap == NULL) {
            printf("%s->%s[style=invis];\n", last_label, node_name);
        }
        else {
            printf("%s->%s;\n", last_label, node_name);
        }
    }
    
    if (heap == NULL) {
        return;
    }
    
    /* 打印子节点 */
    if (heap->left == NULL && heap->right == NULL) {
        return;
    }
    export_dot(heap->left, node_name);
    export_dot(NULL, node_name);
    export_dot(heap->right, node_name);
}

void skew_heap_export_dot(skew_heap_pt heap, char *filename, char *label) {
    printf("digraph g{\nnode[shape=circle];\nlabel=\"%s\";\nlabeljust=l;\nlabelloc=t;\n", label);
    export_dot(heap, NULL);
    printf("}\n");
}

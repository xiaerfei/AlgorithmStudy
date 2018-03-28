//
//  LeftistHeap.c
//  算法学习
//
//  Created by xiaerfei on 2018/2/6.
//  Copyright © 2018年 二哥. All rights reserved.
//

/*
 左偏树（英语：leftist tree或leftist heap），也可称为左偏堆、左倾堆，是计算机科学中的一种树，是一种优先队列实现方式，属于可并堆，在信息学中十分常见，在统计问题、最值问题、模拟问题和贪心问题等等类型的题目中，左偏树都有着广泛的应用。斜堆是比左偏树更为一般的数据结构。
 
 不同于斜堆合并的平均情况复杂度,左偏堆的合并操作的最坏情况复杂度为O(log n)，而完全二叉堆为O(n)，所以左偏堆适合基于合并操作的情形。
 
 由于左偏堆已经不是完全二叉树，因此不能用数组存储表示，需要用链接结构。
 
 左倾堆的基本性质：
 [性质1] 节点的键值小于或等于它的左右子节点的键值。
 [性质2] 节点的左孩子的NPL >= 右孩子的NPL。
 [性质3] 节点的NPL = 它的右孩子的NPL + 1
 
 http://www.cnblogs.com/skywang12345/p/3638327.html
 
 http://mingnote.com/leftist-heap-algorithm-in-c.html
 */
#include "LeftistHeap.h"
#include <stdlib.h>

static void swap(leftist_heap_pt p1,leftist_heap_pt p2) {
    leftist_heap_t tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}


leftist_heap_pt leftist_heap_merge(leftist_heap_pt h1,leftist_heap_pt h2) {
    
    if (h1 == NULL) { return h2; }
    if (h2 == NULL) { return h1; }
    /// 保证h1的优先级大于h2
    if (h1->data > h2->data) { swap(h1,h2); }
    
    h1->right = leftist_heap_merge(h1->right, h2);
    
    if (h1->left == NULL || h1->right->npl > h1->left->npl) {
        leftist_heap_pt tmp = h1->left;
        h1->left = h1->right;
        h1->right = tmp;
    }
    
    if (h1->right == NULL || h1->left == NULL) {
        h1->npl = 0;
    } else {
        h1->npl = h1->right->npl + 1;
    }
    return h1;;
}

leftist_heap_pt leftist_heap_push(leftist_heap_pt heap,int data) {
    leftist_heap_pt node_heap = (leftist_heap_pt)malloc(sizeof(leftist_heap_t));
    if (node_heap == NULL) {
        return node_heap;
    }
    node_heap->left  = NULL;
    node_heap->right = NULL;
    node_heap->data  = data;
    node_heap->npl   = 0;
    return leftist_heap_merge(heap, node_heap);
}

leftist_heap_pt leftist_heap_pop(leftist_heap_pt heap) {
    if (heap == NULL) { return heap; }
    leftist_heap_pt node_heap_left  = heap->left;
    leftist_heap_pt node_heap_right = heap->right;
    free(heap);
    return leftist_heap_merge(node_heap_left, node_heap_right);
}

void leftist_heap_destroy(leftist_heap_pt heap) {
    if (heap == NULL) {
        return;
    }
    
    leftist_heap_destroy(heap->left);
    leftist_heap_destroy(heap->right);
    
    free(heap);
}


void leftist_heap_show(leftist_heap_pt heap) {
    if (heap == NULL) { return; }
    leftist_heap_show(heap->left);
    printf("%d ",heap->data);
    leftist_heap_show(heap->right);
}

/* 打印节点计数变量 */
static int node_num = 0;

static void
export_dot(leftist_heap_pt heap, char *last_label) {
    /* 打印节点 */
    char node_name[10] = {0};
    sprintf(node_name, "n%d", node_num);
    if (heap == NULL) {
        printf("%s[style=invis];\n", node_name);
    }
    else {
        printf("%s[label=%d, xlabel=%d];\n", node_name, heap->data, heap->npl);
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

void leftist_heap_export_dot(leftist_heap_pt heap, char *filename, char *label) {
    printf("digraph g{\nnode[shape=circle];\nlabel=\"%s\";\nlabeljust=l;\nlabelloc=t;\n", label);
    export_dot(heap, NULL);
    printf("}\n");
}

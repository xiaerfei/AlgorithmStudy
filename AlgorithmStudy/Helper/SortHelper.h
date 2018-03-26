//
//  SortHelper.h
//  算法学习
//
//  Created by xiaerfei on 2017/2/13.
//  Copyright © 2017年 二哥. All rights reserved.
//

#ifndef SortHelper_h
#define SortHelper_h

#include <stdio.h>

void swap(int *a,int *b);

void printArr(int arr[],int n);

int *generateSequenceArray(int n );

int *generateRandomArray(int n ,int rangL, int rangR);

int *generateNoRepeatRandomArray(int n ,int rangL, int rangR);

int *copyGenerateRandomArray(int *arr,int n);

int *generateReverseArray(int n );

int *generateRandomSequenceArray(int n,int random);

void testSort(char *s ,void(*sort)(int[],int),int *arr,int n);



#endif /* SortHelper_h */

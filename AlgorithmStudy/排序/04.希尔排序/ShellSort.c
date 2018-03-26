//
//  ShellSort.c
//  算法学习
//
//  Created by xiaerfei on 2017/2/18.
//  Copyright © 2017年 二哥. All rights reserved.
//

#include "ShellSort.h"
#include "SortHelper.h"


void shellSort(int arr[],int n) {
    /// 步长为 2 ，每个步长分为 gap 组数据
    int gap;
    for (gap = n/2; gap > 0; gap /= 2) {
//        for (j = gap; j < n; j ++) {
//            if (arr[j] < arr[j -gap]) {
//                int temp = arr[j];
//                int k = j - gap;
//                while (k >= 0 && arr[k] > temp) {
//                    arr[k + gap] = arr[k];
//                    k -= gap;
//                }
//                
//                arr[k+gap] = temp;
//            }
//        }
        for (int i = gap; i < n; i++) {
            
            int e = arr[i];
            int j = i - gap;
            for (; j >= 0 && arr[j] > e; j-=gap) {
                arr[j + gap] = arr[j];
            }
            arr[j+gap] = e;
        }
    }
}


void shellsort1(int a[], int n)
{
    int i, j, gap;
    
    for (gap = n / 2; gap > 0; gap /= 2) //步长
        for (i = 0; i < gap; i++)        //直接插入排序
        {
            for (j = i + gap; j < n; j += gap)
                if (a[j] < a[j - gap])
                {
                    int temp = a[j];
                    int k = j - gap;
                    while (k >= 0 && a[k] > temp)
                    {
                        a[k + gap] = a[k];
                        k -= gap;
                    }
                    a[k + gap] = temp;
                }
        }
}

void shellsort2(int a[], int n)
{
    int j, gap;
    
    for (gap = n / 2; gap > 0; gap /= 2)
        for (j = gap; j < n; j++)//从数组第gap个元素开始
            if (a[j] < a[j - gap])//每个元素与自己组内的数据进行直接插入排序
            {
                int temp = a[j];
                int k = j - gap;
                while (k >= 0 && a[k] > temp)
                {
                    a[k + gap] = a[k];
                    k -= gap;
                }
                a[k + gap] = temp;
            }
}


void shellsort3(int a[], int n)
{
    int i, j, gap;
    
    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
                swap(&a[j], &a[j + gap]);
}

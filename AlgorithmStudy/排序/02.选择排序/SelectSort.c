//
//  SelectSort.c
//  算法学习
//
//  Created by xiaerfei on 2017/1/26.
//  Copyright © 2017年 二哥. All rights reserved.
//

#include "SelectSort.h"
#include "SortHelper.h"

void selectSort(int arr[],int n) {
    
    for (int i = 0; i < n; i++) {
        
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(&arr[i], &arr[minIndex]);
    }
}

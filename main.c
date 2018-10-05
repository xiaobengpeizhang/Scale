//
//  main.c
//  进制转化器C语言版
//
//  Created by apple on 2018/10/4.
//  Copyright © 2018年 ONEPIECE. All rights reserved.
// 2,8,10,16进制转换器

#include <stdio.h>

#define MAX_LINE 1000

unsigned int mForN(unsigned int m, unsigned int n);
unsigned int rTor(unsigned int sourceNumber, unsigned int source, unsigned int goal);
unsigned int rToTen(unsigned int sourceNumber, unsigned int r);
unsigned int tenToR(unsigned int sourceNumber, unsigned int r);
unsigned char sixTeenfromTen(unsigned int ten);
unsigned int fromSixTeen(unsigned char sixTeen);
unsigned int sixTeenToTen(unsigned char *sixTeen);
unsigned char *tenToSixTeen(unsigned int sourceNumber);
unsigned int sixTeenToR(unsigned char *sourceNumber, unsigned int r);
unsigned char *rToSixTeen(unsigned int sourceNumber, unsigned int r);

int main()
{
    unsigned int source;    // 源进制
    unsigned int goal;      // 目标进制
    unsigned int sourceNumber;  // 源数字
    unsigned int goalNumber;    // 目标数字
    unsigned char sourceArray[MAX_LINE];        // 源数字为16进制
    unsigned char *sourceArrayPointer = sourceArray;
    unsigned char *goalNumberPointer;
    
    while (1)
    {
        printf("源进制为: ");
        scanf("%d", &source);
        printf("目标进制: ");
        scanf("%d", &goal);
        if (source == goal)
        {
            printf("进制相同无需转换\n");
            return 0;
        }
        printf("源数字为: ");
        
        if (source == 16 || goal == 16)
        {
            if (source == 16)
            {
                char ch;
                int isFirstEnter = 1;
                while ((ch = getchar()) != '\n' || isFirstEnter)
                {
                    if (ch == '\n')
                    {
                        isFirstEnter = 0;
                        continue;
                    }
                    *sourceArrayPointer++ = ch;
                }
                *sourceArrayPointer = '\0';
                sourceArrayPointer = sourceArray;
                goalNumber = sixTeenToR(sourceArrayPointer, goal);
                printf("目标数字为: %d\n", goalNumber);
            }
            else
            {
                scanf("%d", &sourceNumber);
                goalNumberPointer = rToSixTeen(sourceNumber, source);
                printf("目标数字为: %s\n", goalNumberPointer);
            }
        }
        else
        {
            scanf("%d", &sourceNumber);
            goalNumber = rTor(sourceNumber, source, goal);
            printf("目标数字为: %d\n", goalNumber);
        }
    }
    

    return 0;
}

// 16进制与R进制的转换
unsigned int sixTeenToR(unsigned char *sourceNumber, unsigned int r)
{
    unsigned int result;
    if (r == 10)
    {
        result = sixTeenToTen(sourceNumber);
    }
    else
    {
        unsigned int temp = sixTeenToTen(sourceNumber);
        result = tenToR(temp, r);
    }
    return result;
}

// R进制与16进制的转换
unsigned char *rToSixTeen(unsigned int sourceNumber, unsigned int r)
{
    unsigned char *result;
    if (r == 10)
    {
        result = tenToSixTeen(sourceNumber);
    }
    else
    {
        unsigned int temp = rToTen(sourceNumber, r);
        result = tenToSixTeen(temp);
    }
    return result;
}

// 16进制转换为10进制
unsigned int sixTeenToTen(unsigned char *sixTeen)
{
    unsigned char *sourceNumber = sixTeen;
    unsigned int i = 0;
    while (*sourceNumber++ != '\0')
    {
        i++;
    }
    printf("i: %d\n", i);
    
    unsigned int result = 0;
    sourceNumber = sixTeen;
    for (int j = i - 1; j >= 0; j--, sourceNumber++)
    {
        unsigned int fromSixTeenNumber = fromSixTeen(*sourceNumber);
        result = result + fromSixTeenNumber * mForN(16, j);
    }
    printf("目标数字: %d\n", result);
    return result;
}

// 10进制转换为16进制
unsigned char *tenToSixTeen(unsigned int sourceNumber)
{
    unsigned char charArray[MAX_LINE];
    unsigned char *sourceArrayPointer = charArray;
    
    while (sourceNumber != 0)
    {
        unsigned int eachBit = sourceNumber % 16;
        char eachSixTeenBit = sixTeenfromTen(eachBit);
        *sourceArrayPointer++ = eachSixTeenBit;
        sourceNumber /= 16;
    }
    *sourceArrayPointer = '\0';
    
    sourceArrayPointer = charArray;       // 计算长度
    unsigned int i = 0;
    while (*sourceArrayPointer++ != '\0')
    {
        i++;
    }
    printf("i: %d\n", i);
    
    sourceArrayPointer = charArray + i - 1;
    unsigned char goalArray[MAX_LINE];
    unsigned char *goalArrayPointer = goalArray;
    while (sourceArrayPointer > charArray)
    {
        *goalArrayPointer++ = *sourceArrayPointer--;
    }
    *goalArrayPointer++ = *sourceArrayPointer;
    *goalArrayPointer = '\0';
    
    goalArrayPointer = goalArray;
    printf("%s\n", goalArrayPointer);
    return goalArrayPointer;
}


// R进制转换为R进制 R为2,8,10
unsigned int rTor(unsigned int sourceNumber, unsigned int source, unsigned int goal)
{
    unsigned int result = 0;
    if (source == 10)
    {
        result = tenToR(sourceNumber, goal);
    }
    else if (goal == 10)
    {
        result = rToTen(sourceNumber, source);
    }
    else
    {
        unsigned int tempResult = rToTen(sourceNumber, source);
        result = tenToR(tempResult, goal);
    }
    return result;
}

// R进制转换为10进制
unsigned int rToTen(unsigned int sourceNumber, unsigned int r)
{
    unsigned int i = 0;
    unsigned int result = 0;
    while (sourceNumber != 0)
    {
        unsigned int eachBit = sourceNumber % 10;
        result += eachBit * mForN(r, i);
        sourceNumber /= 10;
        i++;
    }
    return result;
    return 0;
}

// 10进制转换为R进制
unsigned int tenToR(unsigned int sourceNumber, unsigned int r)
{
    unsigned int result = 0;
    unsigned int i = 0;
    while (sourceNumber != 0)
    {
        unsigned int eachBit = sourceNumber % r;
        result += eachBit * mForN(10, i);
        sourceNumber = sourceNumber / r;
        i++;
    }
    return result;
}

// 数字M的N次方
unsigned int mForN(unsigned int m, unsigned int n)
{
    unsigned int result = 1;
    if (n == 0)
    {
        return result;
    }
    
    for (int i = 0; i < n; i++)
    {
        result *= m;
    }
    return result;
}


// 10进制到16进制的映射
unsigned char sixTeenfromTen(unsigned int ten)
{
    unsigned char ch;
    if (ten >= 0 && ten <= 9)
    {
        ch = '0' + ten;
    }
    else
    {
        ch = 'a' + ten - 10;
    }
    return ch;
}

// 16进制到10进制的映射
unsigned int fromSixTeen(unsigned char sixTeen)
{
    unsigned int result = 0;
    if (sixTeen >= '0' && sixTeen <= '9')
    {
        result = sixTeen - '0';
    }
    else
    {
        result = sixTeen - 'a' + 10;
    }
    return result;
}

//
//  combs.c
//  Combinatorics
//
//  Created by ivan on 13.04.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "combs.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

ErrorCode P_(UNI n, UNI *result)
{
    UNI i = 0, previous = 0;
    
    *result = 1;
    
    for (i = 2; i <= n; i++)
    {
        previous = *result;
        (*result) *= i;
        if (*result / i != previous)
        {
            return ERRORCODE_OVERFLOW;
        }
    }
    
    return ERRORCODE_NO_ERROR;
}

ErrorCode A_(UNI m, UNI n, UNI *result)
{
    UNI i = 0, previous = 0;
    
    if (n > m)
    {
        *result = 0;
        return ERRORCODE_NO_ERROR;
    }
    
    if (n == 0)
    {
        *result = m ? 1 : 0;
        return ERRORCODE_NO_ERROR;
    }
    
    *result = 1;
    
    for (i = m - n + 1; i <= m; i++)
    {
        previous = *result;
        (*result) *= i;
        if (*result / i != previous)
        {
            return ERRORCODE_OVERFLOW;
        }
    }
    
    return ERRORCODE_NO_ERROR;
}

ErrorCode U_(UNI m, UNI n, UNI *result)
{
    UNI i = 0, previous = 0;
    
    if (n > m)
    {
        *result = 0;
        return ERRORCODE_NO_ERROR;
    }
    
    if (n == 0)
    {
        *result = m ? 1 : 0;
        return ERRORCODE_NO_ERROR;
    }
    
    *result = 1;
    
    for (i = 0; i < n; i++)
    {
        previous = *result;
        (*result) *= m;
        if (*result / m != previous)
        {
            return ERRORCODE_OVERFLOW;
        }
    }
    
    return ERRORCODE_NO_ERROR;
}

ErrorCode C_(UNI m, UNI n, UNI *result)
{
    ErrorCode errorCode = ERRORCODE_NO_ERROR;
    
    UNI *a = NULL, *b = NULL, i = 0, j = 0;
    size_t sUNI = 0;
    
    sUNI = sizeof(UNI);
    
    if (n == m)
    {
        *result = 1;
        return ERRORCODE_NO_ERROR;
    }
    
    if (n > m)
    {
        *result = 0;
        return ERRORCODE_NO_ERROR;
    }
    
    if (n > m / 2)
    {
        n = m - n;
    }
    
    if (n == 0)
    {
        *result = m ? 1 : 0;
        return ERRORCODE_NO_ERROR;
    }
    
    if (n == 1)
    {
        *result = m;
        return ERRORCODE_NO_ERROR;
    }
    
    a = (UNI *)malloc(sUNI * (n + 1));
    MEM(a, errHandler);
    b = (UNI *)malloc(sUNI * (n + 1));
    MEM(b, errHandler);
    
    a[0] = 1;
    a[1] = 1;
    
    for (i = 2; i <= m; i++)
    {
        memcpy(b, a, i * sUNI);
        a[0] = 1;
        for (j = 1; j < min(i, n + 1); j++)
        {
            a[j] = b[j] + b[j - 1];
            if (a[j] < b[j] || a[j] < b[j - 1])
            {
                return ERRORCODE_OVERFLOW;
            }
        }
    }
    
    *result = a[n];
    
    free(a);
    free(b);
    
    return ERRORCODE_NO_ERROR;
    
errHandler:
    if (a)
    {
        free(a);
    }
    return ERRORCODE_MEMORY_ALLOCATION_ERROR;
}

ErrorCode S_(UNI m, UNI n, UNI *result)
{
    ErrorCode errorCode = ERRORCODE_NO_ERROR;
    
    UNI *a = NULL, *b = NULL, i = 0, j = 0, stage = 0;
    size_t sUNI = 0;
    
    sUNI = sizeof(UNI);
    
    if (n == m)
    {
        *result = 1;
        return ERRORCODE_NO_ERROR;
    }
    
    if (n > m)
    {
        *result = 0;
        return ERRORCODE_NO_ERROR;
    }
    
    if (n == 0)
    {
        *result = m ? 0 : 1;
        return ERRORCODE_NO_ERROR;
    }
    
    if (n == 1)
    {
        *result = m ? 1 : 0;
        return ERRORCODE_NO_ERROR;
    }
    
    a = (UNI *)malloc(sUNI * (n + 1));
    MEM(a, errHandler);
    b = (UNI *)malloc(sUNI * (n + 1));
    MEM(b, errHandler);
    
    a[0] = 0;
    a[1] = 1;
    
    stage = 1;
    
    for (i = 2; i <= m; i++)
    {
        if (i > m - n + 1)
        {
            stage++;
        }
        
        memcpy(b, a, i * sUNI);
        a[0] = 0;
        for (j = stage; j < min(i, n + 1); j++)
        {
            UNI tmp = 0;
            
            tmp = j * b[j];
            if (tmp / j != b[j])
            {
                return ERRORCODE_OVERFLOW;
            }
            a[j] = tmp + b[j - 1];
            if (a[j] < tmp || a[j] < b[j - 1])
            {
                return ERRORCODE_OVERFLOW;
            }
        }
        if (i < n + 1)
        {
            a[i] = 1;
        }
    }
    
    *result = a[n];
    
    free(a);
    free(b);
    
    return ERRORCODE_NO_ERROR;
    
errHandler:
    if (a)
    {
        free(a);
    }
    return ERRORCODE_MEMORY_ALLOCATION_ERROR;
}


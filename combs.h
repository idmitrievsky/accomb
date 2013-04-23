//
//  combs.h
//  Combinatorics
//
//  Created by ivan on 13.04.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#ifndef Combinatorics_combs_c
#define Combinatorics_combs_c

typedef unsigned int UNI;

#include "errors.h"

ErrorCode P_(UNI n, UNI *result);
ErrorCode A_(UNI m, UNI n, UNI *result);
ErrorCode U_(UNI m, UNI n, UNI *result);
ErrorCode C_(UNI m, UNI n, UNI *result);
ErrorCode S_(UNI m, UNI n, UNI *result);
ErrorCode B_(UNI n, UNI *result);
void PrintNum(UNI num);

#endif

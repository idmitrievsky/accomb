//
//  methods.c
//  Sets
//
//  Created by ivan on 06.04.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "lists.h"
#include "combs.h"
#include "methods.h"

typedef ErrorCode (*Method) (List *list);

#define X(a, b, c, d) a,
typedef enum TagCommands
{
#include "methods.txt"
} Commands;
#undef X

#define X(a, b, c, d) b,
char *commands_names[] =
{
#include "methods.txt"
};
#undef X

#define X(a, b, c, d) d,
char *helpNotes[] =
{
    #include "methods.txt"
};
#undef X

ErrorCode MU(List *args)
{
    ErrorCode errorCode = ERRORCODE_NO_ERROR;
    
    return ERRORCODE_NO_ERROR;
    
errHandler:
    return errorCode;
}

ErrorCode MA(List *args)
{
    ErrorCode errorCode = ERRORCODE_NO_ERROR;
    
    return ERRORCODE_NO_ERROR;
    
errHandler:
    return errorCode;
}

ErrorCode MP(List *args)
{
    ErrorCode errorCode = ERRORCODE_NO_ERROR;
    
    return ERRORCODE_NO_ERROR;
    
errHandler:
    return errorCode;
}

ErrorCode MC(List *args)
{
    ErrorCode errorCode = ERRORCODE_NO_ERROR;
    
    return ERRORCODE_NO_ERROR;
    
errHandler:
    return errorCode;
}

ErrorCode MS(List *args)
{
    ErrorCode errorCode = ERRORCODE_NO_ERROR;
    
    return ERRORCODE_NO_ERROR;
    
errHandler:
    return errorCode;
}

ErrorCode MB(List *args)
{
    ErrorCode errorCode = ERRORCODE_NO_ERROR;
    
    return ERRORCODE_NO_ERROR;
    
errHandler:
    return errorCode;
}

ErrorCode MQ(List *args)
{
    return ERRORCODE_NO_ERROR;
}

ErrorCode MH(List *args)
{
    Commands command = 0;
    
    if (Length(args) == 0)
    {
            while (strcmp(commands_names[EMPTY], commands_names[command]))
            {
                    PrintMethodsHelp(helpNotes[command]);
                command++;
            }
        return ERRORCODE_NO_ERROR;
    }
    return ERRORCODE_WRONG_NUMBER_OF_ARGS;
}

ErrorCode MEmpty(List *list)
{
    return ERRORCODE_EMPTY_COMMAND;
}

ErrorCode MEnd(List *list)
{
    return ERRORCODE_NO_ERROR;
}


#define X(a, b, c, d) c,
Method methods[] =
{
#include "methods.txt"
};
#undef X

ErrorCode Route(List *list, int *quit)
{
    ErrorCode errorCode = ERRORCODE_NO_ERROR;
    Commands command = 0;
    char *methodName = NULL;
    List *args = NULL;
    
    methodName = list->head->next->content;
    
    while (strcmp(commands_names[END], commands_names[command]) && strcmp(methodName, commands_names[command]))
    {
        command++;
    }
    
    if (!strcmp(commands_names[END], commands_names[command]))
    {
        return ERRORCODE_DONT_KNOW_COMMAND;
    }
    else if (!strcmp(commands_names[Q], commands_names[command]))
    {
        *quit = 1;
    }
    else
    {
        CATCH_ERROR(AppendToFromForced(&args, list->head->next->next, list), errHandler);
        CATCH_ERROR(methods[command](args), errHandler);
        ReleaseList(&args);
    }
    
    return ERRORCODE_NO_ERROR;
    
errHandler:
    if (args)
    {
        ReleaseList(&args);
    }
    return errorCode;
}

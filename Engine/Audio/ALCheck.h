// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

void ALCheckError();
void ALClearError();

#if 1
#    define ALCall(func)    \
        do                  \
        {                   \
            ALClearError(); \
            func;           \
            ALCheckError(); \
        } while(false)
#else
#    define GLCall(func) func
#endif

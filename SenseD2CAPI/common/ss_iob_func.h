
#pragma once

/*
* Issue Solving tips�� If the IDE VS2015 and above report the error as the external symbol can't be parsed ,  __iob_func() which is because the compiler
*            
*/
#if _MSC_VER>=1900

#include "stdio.h" 
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);

#ifdef __cplusplus 
extern "C"
#endif
    FILE* __cdecl __iob_func(unsigned i) {
        return __acrt_iob_func(i);

}
#endif /* _MSC_VER>=1900 */


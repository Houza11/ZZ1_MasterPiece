#ifndef TO_STRING_H
#define TO_STRING_H

#define TO_STRING(a) TO_STRING_TMP(a)
#define TO_STRING_TMP(a) #a

#define STRING_GLUE(a, b) a ## b

#endif
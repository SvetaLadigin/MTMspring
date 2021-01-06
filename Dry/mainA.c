#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

//// Original function
// should be duplicateString(char *s, int times) (convention)
// char *s should be const char *str (convention)
//char *stringDuplicator(char *s, int times) {
// assert(!s);    // should be assert(s); (coding)
// assert(times > 0);
// int LEN = strlen(s);   // Should be len (convention)
// char *out = malloc(LEN * times); // Should be +1 for NULL terminator (coding)
// assert(out);
// // indent the for body (convention)
// // Should use a pointer to out instead of using out since (coding)
// for (int i = 0; i < times; i++) {
// out = out + LEN;   // Skips the first LEN bytes (should switch between this and the strcpy (coding)
// strcpy(out, s);
// }
// return out;
//}


char *duplicateString(char *str, int times) {
 assert(str);
 assert(times > 0);
 int len = strlen(str);
 char *out = malloc(len * times + 1);
 assert(out);
 char *out_ptr = out;

 for (int i = 0; i < times; i++) {
     strcpy(out_ptr, str);
     out_ptr = out_ptr + len;
 }

 return out;
}

int main()
{
    char *str = "abc";
    int times = 3;
    char *dupped = duplicateString(str, times);
    printf("original: %s, duplicated %d times: %s\n", str, times, dupped);
    free(dupped);
    return 0;
}
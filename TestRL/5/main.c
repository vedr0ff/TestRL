#include <stdio.h>
#include <string.h>

void* linear_search(const void* arr, const void* key, size_t count, size_t size, 
                   int (*compare)(const void*, const void*)) {
    const char* byte_arr = (const char*)arr;
    for (size_t i = 0; i < count; i++) {
        if (compare(byte_arr + i * size, key) == 0) {
            return (void*)(byte_arr + i * size);
        }
    }
    return NULL;
}

int compare_int(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int compare_double(const void* a, const void* b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int compare_string(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    int int_array[] = {10, 20, 30, 40, 50};
    int int_key = 30;
    
    int* found_int = linear_search(int_array, &int_key, 
                                  sizeof(int_array)/sizeof(int), 
                                  sizeof(int), compare_int);
    
    if (found_int != NULL) {
        printf("Found integer: %d\n", *found_int);
    } else {
        printf("Integer not found\n");
    }
    
    const char* str_array[] = {"apple", "banana", "cherry", "date"};
    const char* str_key = "cherry";
    
    const char** found_str = linear_search(str_array, &str_key,
                                         sizeof(str_array)/sizeof(char*),
                                         sizeof(char*), compare_string);
    
    if (found_str != NULL) {
        printf("Found string: %s\n", *found_str);
    } else {
        printf("String not found\n");
    }
    
     double double_array[] = {1.1, 2.2, 3.3};
     double double_key = 3.3;

     double *found_double =
         linear_search(double_array,
                      &double_key,
                      sizeof(double_array)/sizeof(double),
                      sizeof(double),
                      compare_double);

     if(found_double != NULL)
         printf("Found float: %f\n", *found_double);
     else
         printf("Float not found\n");

     return 0;
}
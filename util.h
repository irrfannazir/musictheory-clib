#ifndef DESC_SIZET
#ifdef _WIN64
    typedef unsigned __int64 size_t;
#else
    typedef unsigned int     size_t;
#endif
#endif

static inline int linearSearch(const int *arr, int value){
    for(size_t i = 0; arr[i] != -1; i++) if(arr[i] == value) return 1;
    return 0;
}
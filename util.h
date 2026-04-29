#ifndef DESC_SIZET
#ifdef _WIN64
    typedef unsigned __int64 size_t;
#else
    typedef unsigned int     size_t;
#endif
#endif

#define get__index_of_sharpnote(NOTE) (NOTE < 'C')?((size_t)NOTE - 60):((size_t)NOTE - 67)
#define get__startindex_of_flatnote(NOTE) (7 + (size_t)NOTE - 67)
#define __if_char_is_null_(CHAR) if(CHAR == '\0')
#define __if_its_not_a_note(NOTE) if(!(NOTE[0] >= 'A' && NOTE[0] <= 'G'))


static inline int linearSearch(const int *arr, int value){
    for(size_t i = 0; arr[i] != -1; i++) if(arr[i] == value) return 1;
    return 0;
}

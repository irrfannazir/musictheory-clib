#ifndef MUSCONSTS_H
#define MUSCONSTS_H
#include "util.h"

/*--------------------------
         basic types
 ---------------------------*/
typedef int                 hashkey_t; // to understand its for index/key value which directs to string representation of musical notes
typedef unsigned char       bool_t;
typedef enum{
    MAJOR,
    MINOR
}                           scale_n; // for denoting type of chords and scale

/*from stddef.h*/
#ifndef DESC_SIZET
  #ifdef _WIN64
    typedef unsigned __int64 size_t;
  #else
    typedef unsigned int     size_t;
  #endif
  #define DESC_SIZET
#endif


#define __if_its_minor_scale if(scale[1] == 'm' || scale[2] == 'm')


const char *notes[] = {
    "C", "C#",
    "D", "D#",
    "E",
    "F", "F#",
    "G", "G#",
    "A", "A#",
    "B"
};

const struct{
    hashkey_t key;
    char *note;
} hashed_value_notes[] = {
    {0, "C"},
    {2, "D"},
    {4, "E"},
    {5, "F"},
    {7, "G"},
    {9, "A"},
    {11, "B"},
    {1, "C#"}, {1, "Db"},
    {3, "D#"}, {3, "Eb"},
    {6, "F#"}, {6, "Gb"},
    {8, "G#"}, {8, "Ab"},
    {10, "A#"}, {10, "Bb"}
};

const char *chord_notation[] = {
    "",
    "m"
};

const hashkey_t chord_patterns[][5] = {
    {0, 4, 7, -1},
    {0, 3, 7, -1}
};

const hashkey_t scale_patterns[][12] = {
    {0, 2, 4, 5, 7, 9, 11, -1},
    {0, 2, 3, 5, 7, 8, 10, -1}
};

static inline scale_n getScaleNotation(char *scale){
    __if_its_minor_scale return MINOR;
    return MAJOR;
}

static inline int getSharpNotation(char *res, char *note){
    __if_char_is_null_(note[0]) return 0;
    __if_char_is_null_(note[1]) return 0;
    if (note[1] == 'b' &&
        (
            note[0] == 'D' || 
            note[0] == 'E' || 
            note[0] == 'G' || 
            note[0] == 'A' || 
            note[0] == 'B' 
        )
    ){
        res[0] = note[0] - 1;
        res[1] = '#';
        res[2] = '\0';
        return 1;
    }
    return 0;
}

static inline hashkey_t getKeyValueOfNote(char *note, size_t len){
    __if_char_is_null_(note[0]) return -1;
    __if_its_not_a_note(note) return -1;
    size_t i;
    switch(len){
        case 1:
            i = get__index_of_sharpnote(note[0]);
            return hashed_value_notes[i].key;
        case 2:
            i = get__startindex_of_flatnote(note[0]);
            for(size_t j = i; i < sizeof(hashed_value_notes)/ sizeof(hashed_value_notes[0]); i++){
                const char *temp = hashed_value_notes[i].note;
                if(note[0] == temp[0] && note[1] == temp[1]) return hashed_value_notes[i].key;
            }
        default:
            return -1;
    }
}

#undef __if_its_minor_scale

#endif
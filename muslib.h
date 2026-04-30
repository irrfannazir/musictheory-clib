#ifndef MUSLIB_H // gaurds for third party
#define MUSLIB_H
#include "musconsts.h"
#include <stdio.h>


/* maximum size of string of musical notations */ 
#define NOTE_MAX 3
#define CHORD_MAX 5


static inline void getChordName(char chord_name[CHORD_MAX], const char base_note[NOTE_MAX], scale_n notation){
    __if_char_is_null_(base_note[0]) return;
    __if_its_not_a_note(base_note) return;
    const bool_t isflat = base_note[1] != '\0';
    chord_name[0] = base_note[0];
    if (isflat) chord_name[1] = base_note[1];
    register size_t i;
    for (i = 0; chord_notation[notation][i] != '\0'; i++) chord_name[1 + (isflat) + i] = chord_notation[notation][i];
    chord_name[1 + isflat + i] = '\0';
}

static inline hashkey_t getBaseNoteIndex(char *scale){
    __if_char_is_null_(scale[0]) return -1;
    char base_note[CHORD_MAX];
    size_t len;
    base_note[0] = scale[0];
    base_note[1] = '\0';
    len = 1;
    if (scale[1] == '#' || scale[1] == 'b') {
        base_note[1] = scale[1];
        base_note[2] = '\0';
        len = 2;
    }
    return getKeyValueOfNote(base_note, len);
}

static inline bool_t findChordInScale(char *scale, int cni, int ni){
    register const scale_n cp_key = getScaleNotation(scale);
    const hashkey_t *scale_pattern = scale_patterns[cp_key];
    const hashkey_t spni = cni - getBaseNoteIndex(scale) + 12;


    for(size_t k = 0; chord_patterns[ni][k] != -1; k++){
        register hashkey_t current_note = (spni + chord_patterns[ni][k]) % 12;
        if(!linearSearch(scale_pattern, current_note)) return 0;
    }
    return 1;
}

static inline void printChordFromScale(char scale[CHORD_MAX]){
    __if_char_is_null_(scale[0]) return;
    if(getBaseNoteIndex(scale) == -1) return;
    scale_n cp_key = getScaleNotation(scale);
    const hashkey_t *scale_pattern = scale_patterns[cp_key];

    for(size_t i = 0; scale_pattern[i] != -1; i++){
        const hashkey_t current_note_index = (getBaseNoteIndex(scale) + scale_pattern[i]) % 12;

        for(scale_n j = 0; j < sizeof(chord_patterns)/sizeof(chord_patterns[0]); j++){
            char chord[CHORD_MAX];
            getChordName(chord, notes[current_note_index], j);
            if(findChordInScale(scale, current_note_index, j)) printf("%s\t", chord);
        }
    }
    printf("\n");
}

static inline void printNotesFromScale(char *scale){
    __if_char_is_null_(scale[0]) return;
    scale_n cp_key = getScaleNotation(scale);
    const int *scale_pattern = scale_patterns[cp_key];
    
    for(int i = 0; scale_pattern[i] != -1; i++){
        register int current_note_index = (getBaseNoteIndex(scale) + scale_pattern[i]) % 12;
        printf("%s\t", notes[current_note_index]);
    }
    printf("\n");
}


#endif
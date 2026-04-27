#ifndef MUSLIB_H // gaurds for third party
#define MUSLIB_H


/* maximum size of string of musical notations */ 
#define NOTE_MAX 3
#define CHORD_MAX 5

/*--------------------------
         basic types
 ---------------------------*/
typedef int                 hashkey_t; // to understand its for index/key value which directs to string representation of musical notes
typedef enum{
    MAJOR,
    MINOR
}                           scale_n; // for denoting type of chords and scale

/*from stddef.h*/
#ifdef _WIN64
    typedef unsigned __int64 size_t;
#else
    typedef unsigned int     size_t;
#endif


#define get__index_of_sharpnote(NOTE) (NOTE < 'C')?((size_t)NOTE - 60):((size_t)NOTE - 67)
#define get__startindex_of_flatnote(NOTE) (7 + (size_t)NOTE - 67)

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


/* helper functions*/
static inline scale_n getScaleNotation(char scale[CHORD_MAX]){
    if(scale[1] == 'm' || scale[2] == 'm') return MINOR;
    return MAJOR;
}

static inline int linearSearch(const int *arr, int value){
    for(size_t i = 0; arr[i] != -1; i++) if(arr[i] == value) return 1;
    return 0;
}

static inline int getSharpNotation(char *res, char *note){
    if (note[0] == '\0') return 0;
    if (note[1] == '\0') return 0;
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

static inline void getChordName(char chord_name[CHORD_MAX], const char base_note[NOTE_MAX], scale_n notation){
    size_t i;
    const unsigned char isflat = base_note[1] != '\0';
    chord_name[0] = base_note[0];
    if (isflat) chord_name[1] = base_note[1];
    for (i = 0; chord_notation[notation][i] != '\0'; i++) chord_name[1 + (isflat) + i] = chord_notation[notation][i];
    chord_name[1 + isflat + i] = '\0';
}



static inline hashkey_t getKeyValueOfNote(char note[NOTE_MAX], size_t len){
    if(!(note[0] >= 'A' && note[0] <= 'G')) return -1;
    if(len == 1){
        size_t i = get__index_of_sharpnote(note[0]);
        return hashed_value_notes[i].key;
    }else if(len == 2){
        size_t start = get__startindex_of_flatnote(note[0]);
        for(size_t i = start; i < sizeof(hashed_value_notes)/ sizeof(hashed_value_notes[0]); i++){
            char *temp = hashed_value_notes[i].note;
            if(note[0] == temp[0] && note[1] == temp[1]) return hashed_value_notes[i].key;
        }
        return -1;
    }else{
        return -1;
    }
}

static inline hashkey_t getBaseNoteIndex(char *scale){
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

static inline void printChordFromScale(char scale[CHORD_MAX]){
    scale_n cp_key = getScaleNotation(scale);
    const hashkey_t *scale_pattern = scale_patterns[cp_key];
    if(getBaseNoteIndex(scale) == -1) return;

    for(size_t i = 0; scale_pattern[i] != -1; i++){
        const hashkey_t current_note_index = (getBaseNoteIndex(scale) + scale_pattern[i]) % 12;

        for(scale_n j = 0; j < sizeof(chord_patterns)/sizeof(chord_patterns[0]); j++){
            int flag = 1;

            for(size_t k = 0; chord_patterns[j][k] != -1; k++){
                hashkey_t current_note = (current_note_index + chord_patterns[j][k]) % 12;
                
                if(!linearSearch(scale_pattern, current_note)){
                    flag = 0;
                    break;
                }
            }
            char chord[CHORD_MAX];
            getChordName(chord, notes[current_note_index], j);
            if(flag) printf("%s\t", chord);
        }
    }
    printf("\n");
}

static inline void printNotesFromScale(char *scale){
    scale_n cp_key = getScaleNotation(scale);
    const int *scale_pattern = scale_patterns[cp_key];
    
    for(int i = 0; scale_pattern[i] != -1; i++){
        register int current_note_index = (getBaseNoteIndex(scale) + scale_pattern[i]) % 12;
        printf("%s\t", notes[current_note_index]);
    }
    printf("\n");
}



#undef get__index_of_sharpnote
#undef get__startindex_of_flatnote

#endif
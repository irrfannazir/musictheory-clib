Try to use the functions in library

----------------------------
Types:

    hashkey_t: Just an alias for int, for the semitone value (0 through 11) used for mathematical operations on musical intervals
    scale_n (Enum):
        MAJOR: Represents a major quality.
        MINOR: Represents a minor quality.
    size_t: A custom definition from stddef

----------------------------
Functions:

    getKeyValueOfNote
        Purpose: Translates a note string (e.g., "Eb") into its integer hashkey_t (3).
        Logic:
            For single-character notes, it uses an ASCII offset calculation.
            For two-character notes, it performs a search through hashed_value_notes.

    getBaseNoteIndex
        Purpose: Extracts the root note from a scale/chord string and returns its hashkey_t.
        Note: There is a logic bug in the provided code where len = 1 is hardcoded at the end of the function, potentially overwriting the length of accidental notes (sharps/flats).

    printNotesFromScale
        Purpose: Prints all individual notes contained within a specific scale (e.g., "C Major").
        Logic: Calculates the semitone index for each step in the scale_pattern and fetches the string from the notes array.

    printChordFromScale
        Purpose: Identifies and prints the valid diatonic chords within a given scale.
        Logic:
            Iterates through every note in the scale.
            For each note, it tests both Major and Minor chord patterns.
            If all notes of a chord pattern exist within the current scale (verified via linearSearch), the chord name is printed.



Run the command with desirable main c program file
```sh
gcc main.c -o m
```

Then execute m.


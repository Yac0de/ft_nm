#!/bin/bash

FT_NM=../ft_nm
NM=nm
SRC_DIR=src
MALFORMED_DIR=malformed
OBJ_DIR=obj
EXP_DIR=expected
ACT_DIR=actual

VERBOSE=false  # ← set to true to see all messages during tests

mkdir -p "$OBJ_DIR" "$EXP_DIR" "$ACT_DIR"
rm -f "$ACT_DIR"/*.txt
git push --force

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

# Test .c and .txt sources
for src in "$SRC_DIR"/*; do
    name=$(basename "$src")
    base="${name%.*}"
    ext="${name##*.}"
    obj="$OBJ_DIR/$base.o"

    if [ "$ext" = "c" ]; then
        gcc -c "$src" -o "$obj" || { echo "Failed to compile $src"; continue; }

        "$NM" "$obj" > "$EXP_DIR/$base.txt"
        "$FT_NM" "$obj" > "$ACT_DIR/$base.txt" 2>/dev/null

        if diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt" > /dev/null; then
            echo -e "$GREEN✔ $base$NC"
        else
            echo -e "$RED✘ $base$NC"
            diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt"
        fi

    elif [ "$ext" = "txt" ]; then
        "$NM" "$src" 2>&1 | tee "$EXP_DIR/$base.txt" > /dev/null
        "$FT_NM" "$src" 2>&1 | tee "$ACT_DIR/$base.txt" > /dev/null

        if diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt" > /dev/null; then
            echo -e "$GREEN✔ $base (non-ELF)$NC"
        else
            echo -e "$RED✘ $base (non-ELF)$NC"
            diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt"
        fi
    fi
done

echo -e "\n====== Testing malformed ELF files ======\n"

# Test malformed ELF binaries
for bin in "$MALFORMED_DIR"/*; do
    name=$(basename "$bin")

    # Remove 'bfd plugin:' from nm output
    "$NM" "$bin" 2>&1 | grep -v '^bfd plugin:' > "$EXP_DIR/$name.txt"
    "$FT_NM" "$bin" > "$ACT_DIR/$name.txt" 2>&1

    if diff -u "$EXP_DIR/$name.txt" "$ACT_DIR/$name.txt" > /dev/null; then
        echo -e "$GREEN✔ $name (malformed)$NC"
    else
        echo -e "$RED✘ $name (malformed)$NC"
        diff -u "$EXP_DIR/$name.txt" "$ACT_DIR/$name.txt"
        if [ "$VERBOSE" = true ]; then
            echo "--- ft_nm output ---"
            cat "$ACT_DIR/$name.txt"
        fi
    fi
done

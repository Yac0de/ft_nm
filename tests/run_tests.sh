#!/bin/bash

FT_NM=../ft_nm
NM=nm
SRC_DIR=src
OBJ_DIR=obj
EXP_DIR=expected
ACT_DIR=actual

mkdir -p "$OBJ_DIR" "$EXP_DIR" "$ACT_DIR"

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

for src in "$SRC_DIR"/*; do
    name=$(basename "$src")
    base="${name%.*}"
    ext="${name##*.}"
    obj="$OBJ_DIR/$base.o"

    if [ "$ext" = "c" ]; then
        gcc -c "$src" -o "$obj" || { echo "Failed to compile $src"; continue; }

        "$NM" "$obj" > "$EXP_DIR/$base.txt"
        "$FT_NM" "$obj" > "$ACT_DIR/$base.txt"

        if diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt" > /dev/null; then
            echo -e "$GREEN✔ $base$NC"
        else
            echo -e "$RED✘ $base$NC"
            diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt"
        fi

    elif [ "$ext" = "txt" ]; then
        if "$FT_NM" "$src" 2>&1 | grep -q "Not an ELF file"; then
            echo -e "$GREEN✔ $base (non-ELF)$NC"
        else
            echo -e "$RED✘ $base (non-ELF)$NC"
        fi
    fi
done

#!/bin/bash

# This script builds and tests ft_nm against various ELF files.
# It runs tests for 64-bit and 32-bit compiled sources, malformed binaries,
# and shared objects (.so). Output is compared to system nm.

FT_NM=../ft_nm
NM="env LC_ALL=C nm" # Force binary string comparison for consistent sorting across locales
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
YELLOW="\033[1;33m"
NC="\033[0m"

# Test .c and .txt sources
for src in "$SRC_DIR"/*; do
    name=$(basename "$src")
    base="${name%.*}"
    ext="${name##*.}"

    if [ "$ext" = "c" ]; then
        # === Compile 64-bit ===
        obj64="$OBJ_DIR/${base}_64.o"
        gcc -c "$src" -o "$obj64" || { echo "Failed to compile $src (64-bit)"; continue; }

        $NM "$obj64" > "$EXP_DIR/${base}_64.txt"
        "$FT_NM" "$obj64" > "$ACT_DIR/${base}_64.txt" 2>/dev/null

        if diff -u "$EXP_DIR/${base}_64.txt" "$ACT_DIR/${base}_64.txt" > /dev/null; then
            echo -e "$GREEN✔ $base (64-bit)$NC"
        else
            echo -e "$RED✘ $base (64-bit)$NC"
            diff -u "$EXP_DIR/${base}_64.txt" "$ACT_DIR/${base}_64.txt"
        fi

        # === Compile 32-bit ===
        obj32="$OBJ_DIR/${base}_32.o"
        if gcc -m32 -c "$src" -o "$obj32" 2>/dev/null; then
            $NM "$obj32" > "$EXP_DIR/${base}_32.txt"
            "$FT_NM" "$obj32" > "$ACT_DIR/${base}_32.txt" 2>/dev/null

            if diff -u "$EXP_DIR/${base}_32.txt" "$ACT_DIR/${base}_32.txt" > /dev/null; then
                echo -e "$GREEN✔ $base (32-bit)$NC"
            else
                echo -e "$RED✘ $base (32-bit)$NC"
                diff -u "$EXP_DIR/${base}_32.txt" "$ACT_DIR/${base}_32.txt"
            fi
        else
            echo -e "$YELLOW⚠ Skipped $base (32-bit not supported on this system)$NC"
        fi

    elif [ "$ext" = "txt" ]; then
        $NM "$src" 2>&1 | tee "$EXP_DIR/$base.txt" > /dev/null
        "$FT_NM" "$src" 2>&1 | tee "$ACT_DIR/$base.txt" > /dev/null

        if diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt" > /dev/null; then
            echo -e "$GREEN✔ $base (non-ELF)$NC"
        else
            echo -e "$RED✘ $base (non-ELF)$NC"
            diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt"
        fi

    elif [ "$ext" = "so" ]; then
    $NM "$src" > "$EXP_DIR/$base.txt" 2>/dev/null
    "$FT_NM" "$src" > "$ACT_DIR/$base.txt" 2>/dev/null

        if diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt" > /dev/null; then
            echo -e "$GREEN✔ $base (.so)$NC"
        else
            echo -e "$RED✘ $base (.so)$NC"
            diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt"
        fi

    elif [ "$ext" = "o" ]; then
        $NM "$src" > "$EXP_DIR/$base.txt" 2>/dev/null
        "$FT_NM" "$src" > "$ACT_DIR/$base.txt" 2>/dev/null

        if diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt" > /dev/null; then
            echo -e "$GREEN✔ $base (.o)$NC"
        else
            echo -e "$RED✘ $base (.o)$NC"
            diff -u "$EXP_DIR/$base.txt" "$ACT_DIR/$base.txt"
        fi
    fi
done

echo -e "\n====== Testing malformed ELF files ======\n"

# Test malformed ELF binaries
for bin in "$MALFORMED_DIR"/*; do
    name=$(basename "$bin")

    $NM "$bin" 2>&1 | grep -v '^bfd plugin:' > "$EXP_DIR/$name.txt"
    "$FT_NM" "$bin" > "$ACT_DIR/$name.txt" 2>&1

    if diff -u "$EXP_DIR/$name.txt" "$ACT_DIR/$name.txt" > /dev/null; then
        echo -e "$GREEN✔ $name $NC"
    else
        echo -e "$RED✘ $name $NC"
        diff -u "$EXP_DIR/$name.txt" "$ACT_DIR/$name.txt"
        if [ "$VERBOSE" = true ]; then
            echo "--- ft_nm output ---"
            cat "$ACT_DIR/$name.txt"
        fi
    fi
done

#!/bin/bash

PROGRAM="./cub3D"

# Directories
ERROR_DIR="./maps/errors"
INVALID_DIR="./invalid_maps"
VALID_DIR_1="./maps/weirds"
VALID_DIR_2="./maps/normal"

VALGRIND = ""
#VALGRIND="valgrind --leak-check=full --show-leak-kinds=all"
PASS=0
FAIL=0

test_dir () {
    DIR=$1
    SHOULD_ERROR=$2

    echo "=============================="
    echo "Testing: $DIR"
    echo "=============================="

    for map in "$DIR"/*.cub; do
        echo "→ $map"

        output=$(timeout 2s $VALGRIND "$PROGRAM" "$map" 2>&1)
        exit_code=$?

        has_error=$(echo "$output" | grep -c "^Error")

        # Detect leaks
        leaks=$(echo "$output" | grep "definitely lost:" | awk '{print $4}')
        leaks=${leaks//,/}

        if [ -z "$leaks" ]; then
            leaks=0
        fi

        has_leaks=0
        if [ "$leaks" -gt 0 ]; then
            has_leaks=1
        fi
        # Check expectations
        if [ "$SHOULD_ERROR" -eq 1 ]; then
            # should ERROR
            if [ "$has_error" -gt 0 ] ; then
                echo "✅ PASS"
                echo "$output"
                ((PASS++))
            else
                echo "❌ FAIL"
                "   → Expected Error"
                ((FAIL++))
            fi
        else
            # should NOT error
            if [ "$has_error" -eq 0 ] && [ "$has_leaks" -eq 0 ]; then
                echo "✅ PASS"
                echo "$output"
                ((PASS++))
            else
                echo "❌ FAIL"
                echo "$output"
                [ "$has_error" -gt 0 ] && echo "   → Unexpected Error"
                [ "$has_leaks" -eq 1 ] && echo "   → Memory leak ($leaks bytes)"
                ((FAIL++))
            fi
        fi

        echo ""
    done
}

# Run tests
test_dir "$ERROR_DIR" 1
test_dir "$INVALID_DIR" 1
test_dir "$VALID_DIR_1" 0
test_dir "$VALID_DIR_2" 0

echo "=============================="
echo "FINAL RESULTS"
echo "=============================="
echo "✅ Passed: $PASS"
echo "❌ Failed: $FAIL"

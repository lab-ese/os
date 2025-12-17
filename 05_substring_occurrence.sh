#!/bin/bash

# Find occurrences of substring in a string

echo "Enter the main string:"
read mainstr

echo "Enter the substring to search:"
read substr

# Get lengths
mainlen=${#mainstr}
sublen=${#substr}

count=0
positions=""

echo "Searching for '$substr' in '$mainstr'..."
echo ""

# Search for substring
for ((i=0; i<=mainlen-sublen; i++))
do
    # Extract substring of length sublen starting at position i
    temp="${mainstr:$i:$sublen}"
    
    if [ "$temp" = "$substr" ]; then
        count=$((count + 1))
        positions="$positions $i"
        echo "Occurrence $count found at position: $i"
    fi
done

echo ""
echo "Total occurrences: $count"

if [ $count -gt 0 ]; then
    echo "Positions:$positions"
fi

# Example: banana, substring: ana
# Output: Position 1 and Position 3

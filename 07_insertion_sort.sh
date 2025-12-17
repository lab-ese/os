#!/bin/bash

# Insertion Sort in Shell Script

echo "Enter the number of elements:"
read n

echo "Enter $n numbers:"
for ((i=0; i<n; i++))
do
    read arr[$i]
done

echo "Original array:"
echo "${arr[@]}"

# Insertion Sort Algorithm
for ((i=1; i<n; i++))
do
    key=${arr[$i]}
    j=$((i-1))
    
    # Move elements greater than key one position ahead
    while [ $j -ge 0 ] && [ ${arr[$j]} -gt $key ]
    do
        arr[$((j+1))]=${arr[$j]}
        j=$((j-1))
    done
    
    arr[$((j+1))]=$key
done

echo "Sorted array:"
echo "${arr[@]}"

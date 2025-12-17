#!/bin/bash

# Bubble Sort in Shell Script

echo "Enter the number of elements:"
read n

echo "Enter $n numbers:"
for ((i=0; i<n; i++))
do
    read arr[$i]
done

echo "Original array:"
echo "${arr[@]}"

# Bubble Sort Algorithm
for ((i=0; i<n-1; i++))
do
    for ((j=0; j<n-i-1; j++))
    do
        if [ ${arr[$j]} -gt ${arr[$((j+1))]} ]; then
            # Swap elements
            temp=${arr[$j]}
            arr[$j]=${arr[$((j+1))]}
            arr[$((j+1))]=$temp
        fi
    done
done

echo "Sorted array:"
echo "${arr[@]}"

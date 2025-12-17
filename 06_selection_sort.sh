#!/bin/bash

# Selection Sort in Shell Script

echo "Enter the number of elements:"
read n

echo "Enter $n numbers:"
for ((i=0; i<n; i++))
do
    read arr[$i]
done

echo "Original array:"
echo "${arr[@]}"

# Selection Sort Algorithm
for ((i=0; i<n-1; i++))
do
    min_idx=$i
    
    # Find minimum element in unsorted array
    for ((j=i+1; j<n; j++))
    do
        if [ ${arr[$j]} -lt ${arr[$min_idx]} ]; then
            min_idx=$j
        fi
    done
    
    # Swap minimum element with first element
    if [ $min_idx -ne $i ]; then
        temp=${arr[$i]}
        arr[$i]=${arr[$min_idx]}
        arr[$min_idx]=$temp
    fi
done

echo "Sorted array:"
echo "${arr[@]}"

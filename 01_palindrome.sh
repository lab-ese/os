#!/bin/bash

# Program to check if a string is palindrome

echo "Enter a string:"
read str

# Remove spaces and convert to lowercase
str=$(echo "$str" | tr -d ' ' | tr '[:upper:]' '[:lower:]')

# Reverse the string manually
rev=""
len=${#str}
for ((i=len-1; i>=0; i--))
do
    rev="${rev}${str:$i:1}"
done

# Compare original and reversed strings
if [ "$str" = "$rev" ]; then
    echo "The string is a palindrome"
else
    echo "The string is not a palindrome"
fi

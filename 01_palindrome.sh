#!/bin/bash

# Program to check if a string is palindrome

echo "Enter a string:"
read str

# Remove spaces and convert to lowercase
str=$(echo "$str" | tr -d ' ' | tr '[:upper:]' '[:lower:]')

# Reverse the string
rev=$(echo "$str" | rev)

# Compare original and reversed strings
if [ "$str" = "$rev" ]; then
    echo "The string is a palindrome"
else
    echo "The string is not a palindrome"
fi

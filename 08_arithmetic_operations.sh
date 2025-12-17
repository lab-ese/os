#!/bin/bash

# Arithmetic operations using case statement

echo "Enter first number:"
read num1

echo "Enter second number:"
read num2

echo ""
echo "Select operation:"
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiplication"
echo "4. Division"
echo "5. Modulus"
echo ""
echo "Enter your choice (1-5):"
read choice

case $choice in
    1)
        result=$((num1 + num2))
        echo "$num1 + $num2 = $result"
        ;;
    2)
        result=$((num1 - num2))
        echo "$num1 - $num2 = $result"
        ;;
    3)
        result=$((num1 * num2))
        echo "$num1 * $num2 = $result"
        ;;
    4)
        if [ $num2 -eq 0 ]; then
            echo "Error: Division by zero is not allowed!"
        else
            result=$(echo "scale=2; $num1 / $num2" | bc)
            echo "$num1 / $num2 = $result"
        fi
        ;;
    5)
        if [ $num2 -eq 0 ]; then
            echo "Error: Modulus by zero is not allowed!"
        else
            result=$((num1 % num2))
            echo "$num1 % $num2 = $result"
        fi
        ;;
    *)
        echo "Invalid choice! Please select 1-5."
        ;;
esac

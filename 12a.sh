#!/bin/sh

# Prompt the user for three numbers
read -p "Enter the first number: " n1
read -p "Enter the second number: " n2
read -p "Enter the third number: " n3

# Find the largest number
if [ "$n1" -ge "$n2" ] && [ "$n1" -ge "$n3" ]; then
    largest=$n1
elif [ "$n2" -ge "$n1" ] && [ "$n2" -ge "$n3" ]; then
    largest=$n2
else
    largest=$n3
fi

# Print the largest number
echo "The largest number is: $largest"

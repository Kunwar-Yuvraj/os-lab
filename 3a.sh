#!/bin/bash

# Read the number of elements
read -p "Enter the number of elements: " n

# Read the elements into an array
echo "Enter the elements:"
for ((i = 0; i < n; i++)); do
  read -p "Element $((i+1)): " a[i]
done

# Initialize the largest variable
largest=${a[0]}

# Loop through the array to find the largest number
for ((i = 1; i < n; i++)); do
  if [ ${a[i]} -gt $largest ]; then
    largest=${a[i]}
  fi
done

# Print the largest number
echo "The largest number is: $largest"

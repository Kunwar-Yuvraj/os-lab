#!/bin/bash

# Read the range from user input
read -p "Enter the lower bound of the range: " lower
read -p "Enter the upper bound of the range: " upper

# Generate and print prime numbers in the given range
echo "Prime numbers between $lower and $upper are:"
for ((num = lower; num <= upper; num++)); do
  is_prime=1
  for ((i = 2; i * i <= num; i++)); do
    if [ $((num % i)) -eq 0 ]; then
      is_prime=0
      break
    fi
  done
  if [ $is_prime -eq 1 ]; then
    echo $num
  fi
done

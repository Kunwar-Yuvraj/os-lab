#!/bin/bash

# Read number from user input
read -p "Enter a number: " num

# Initialize variables
orig_num=$num
rev_num=0

# Reverse the number
while [ $num -gt 0 ]
do
  rem=$((num % 10))
  rev_num=$((rev_num * 10 + rem))
  num=$((num / 10))
done

# Check if the original number is equal to the reversed number
if [ $orig_num -eq $rev_num ]; then
  echo "The number $orig_num is a palindrome."
else
  echo "The number $orig_num is not a palindrome."
fi

#!/bin/bash

# Read matrix dimensions
read -p "Enter rows: " r
read -p "Enter columns: " c

# Initialize arrays to store matrix elements
m1=()
m2=()
res=()

# Read the first matrix
echo "Enter elements of first matrix:"
for ((i = 0; i < r * c; i++)); do
  read -p "Element $((i + 1)): " m1[i]
done

# Read the second matrix
echo "Enter elements of second matrix:"
for ((i = 0; i < r * c; i++)); do
  read -p "Element $((i + 1)): " m2[i]
done

# Calculate the addition of the two matrices
for ((i = 0; i < r * c; i++)); do
  res[i]=$((m1[i] + m2[i]))
done

# Print the first matrix
echo "First Matrix:"
for ((i = 0; i < r; i++)); do
  for ((j = 0; j < c; j++)); do
    echo -n "${m1[i * c + j]} "
  done
  echo
done

# Print the second matrix
echo "Second Matrix:"
for ((i = 0; i < r; i++)); do
  for ((j = 0; j < c; j++)); do
    echo -n "${m2[i * c + j]} "
  done
  echo
done

# Print the resultant matrix
echo "Resultant Matrix (Sum):"
for ((i = 0; i < r; i++)); do
  for ((j = 0; j < c; j++)); do
    echo -n "${res[i * c + j]} "
  done
  echo
done

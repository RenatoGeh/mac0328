#!/bin/bash

echo "Cleaning..."
make clean
echo "Compiling with DIGRAPHlists..."
make GRAPH=lists
echo "Running with DIGRAPHlists..."
./ep

echo "Cleaning..."
make clean
echo "Compiling with DIGRAPHmatrix..."
make GRAPH=matrix
echo "Running with DIGRAPHmatrix..."
./ep

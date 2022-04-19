#!/bin/bash
# DATASETS = /input/*.fasta

mkdir -p time
for file in input/datasets_input/*.fasta;
do
    filename="$(basename -- ${file%.*})"
    echo "Processing $filename"

    { /usr/bin/time -v ./bin/algorithm $file "output/$filename.txt"; } 2> "time/time_$filename.txt" 

    # ./bin/algorithm $file "output/$filename.txt" >> "time_$filename.txt"
done
#!/bin/zsh

gcc -o delaunay delaunay.c

echo "Starting 60 point triangulation..."
./delaunay input/data60.txt 60 > 'output/test60.txt'
cat output/test60.txt | python3 tri.py input/data60.txt output/delaunay60.png
echo "...60 point triangulation finished"

echo "Starting 800 point triangulation..."
./delaunay input/data800.txt 800 > 'output/test800.txt'
cat output/test800.txt | python3 tri.py input/data800.txt output/delaunay800.png
echo "...800 point triangulation finished"


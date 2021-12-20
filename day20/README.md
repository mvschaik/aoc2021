# Day 20

https://adventofcode.com/2021/day/20

If the first element of the algorithm is a '#', each other iteration
will cause the infinite world to be filled with '#'s. Having the last
element being '.' will clear that out again.

```
c++ -std=c++17 -O2 main.cpp -o main

# Usage:
# ./main <input filename>

./main input.txt
```

```
➜ …src/aoc2021/day20 ./main test.txt
Number of active pixels after 1 enhancements: 10
Number of active pixels after 2 enhancements: 13
Number of active pixels after 3 enhancements: 34
# ...
Number of active pixels after 49 enhancements: 3067
Number of active pixels after 50 enhancements: 3046

➜ …src/aoc2021/day20 time ./main input.txt
Number of active pixels after 2 enhancements: 203
Number of active pixels after 4 enhancements: 406
Number of active pixels after 6 enhancements: 601
Number of active pixels after 8 enhancements: 782
Number of active pixels after 10 enhancements: 1004
Number of active pixels after 12 enhancements: 1220
Number of active pixels after 14 enhancements: 1483
Number of active pixels after 16 enhancements: 1654
Number of active pixels after 18 enhancements: 1919
Number of active pixels after 20 enhancements: 2189
Number of active pixels after 22 enhancements: 2454
Number of active pixels after 24 enhancements: 2804
Number of active pixels after 26 enhancements: 3059
Number of active pixels after 28 enhancements: 3379
Number of active pixels after 30 enhancements: 3750
Number of active pixels after 32 enhancements: 4009
Number of active pixels after 34 enhancements: 4382
Number of active pixels after 36 enhancements: 4632
Number of active pixels after 38 enhancements: 5091
Number of active pixels after 40 enhancements: 5369
Number of active pixels after 42 enhancements: 5726
Number of active pixels after 44 enhancements: 6142
Number of active pixels after 46 enhancements: 6546
Number of active pixels after 48 enhancements: 7075
Number of active pixels after 50 enhancements: 7422
./main input.txt  1.47s user 0.01s system 99% cpu 1.492 total
```

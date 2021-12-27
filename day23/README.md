# Day 23

https://adventofcode.com/2021/day/23

```
c++ -std=c++17 -O2 main.cpp -o main

# Usage:
# ./main <part> <input filename>

# Part 1
./main 1 input.txt

# Part 2
./main 2 input.txt
```

It will display minima while searching the solution space.

I didn't wait until part 2 completed, when it stopped progressing I just
tried to enter the current minimum and it turned out to be correct! :-)

```
➜ …src/aoc2021/day23 ./main 1 test.txt
Completed with cost 22581
Completed with cost 22541
Completed with cost 22521
...
Completed with cost 12521
Min cost: 12521

➜ …src/aoc2021/day23 time ./main 1 input.txt
Completed with cost 18982
Completed with cost 18786
Completed with cost 17586
Completed with cost 17386
Completed with cost 16986
Completed with cost 16786
Completed with cost 15586
Completed with cost 15386
Completed with cost 14986
Completed with cost 14786
Completed with cost 14766
Completed with cost 14746
Completed with cost 14698
Completed with cost 14694
Completed with cost 14692
Completed with cost 14690
Completed with cost 14688
Completed with cost 14686
Completed with cost 14682
Completed with cost 14680
Completed with cost 14662
Completed with cost 14654
Completed with cost 14652
Completed with cost 14644
Completed with cost 14642
Completed with cost 14628
Completed with cost 14622
Completed with cost 14620
Completed with cost 14566
Completed with cost 14546
Min cost: 14546
./main 1 input.txt  690.37s user 1.00s system 99% cpu 11:32.74 total

➜ …src/aoc2021/day23 time ./main 2 test.txt
Completed with cost 44429
Completed with cost 44389
Completed with cost 44369
Completed with cost 44229
Completed with cost 44189
Completed with cost 44169
^C
./main 2 test.txt  785.45s user 0.98s system 99% cpu 13:07.73 total


➜ …src/aoc2021/day23 time ./main 2 input.txt
Completed with cost 42510
Completed with cost 42310
Completed with cost 42308
^C
./main 2 input.txt  35.34s user 0.09s system 99% cpu 35.561 total
```

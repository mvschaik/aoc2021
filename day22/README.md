# Day 22

https://adventofcode.com/2021/day/22

Ooofff. In the end the solution ran for 4 hours and 40 minutes and took almost 15 GB RAM.

```
c++ -std=c++17 -O2 main.cpp -o main

# Usage:
# ./main <input filename>

./main input.txt
```

```
➜  day22 ./main test.txt
on x=-5..47,y=-31..22,z=-19..33
...
off x=-44271..17935,y=-9516..60759,z=49131..112598
There are 474140 cubes on in part 1
Using 117 * 117 * 119 = 1628991 cube buckets
[1/60] off x=-93533..-4276,y=-16170..68771,z=-104985..-24507
[2/60] on x=-53470..21291,y=-120233..-33476,z=-44150..38147
...
[60/60] on x=-5..47,y=-31..22,z=-19..33
There are 2758514936282235 cubes on in part 2


➜  day22 /usr/bin/time -v ./main input.txt
on x=-40..8,y=-12..40,z=-44..6
on x=-34..16,y=-49..5,z=-25..23
...
off x=-2390..20751,y=-9828..15681,z=71197..87706
There are 648681 cubes on in part 1
Using 830 * 835 * 835 = 578696750 cube buckets
[1/420] on x=36489..59834,y=41164..59395,z=5821..27183
[2/420] on x=47725..57873,y=-72930..-54630,z=10555..26451
[3/420] off x=-77226..-62474,y=-32321..-6557,z=-14470..3713
...
[420/420] on x=-40..8,y=-12..40,z=-44..6
There are 1302784472088899 cubes on in part 2
        Command being timed: "./main input.txt"
        User time (seconds): 16796.78
        System time (seconds): 37.23
        Percent of CPU this job got: 99%
        Elapsed (wall clock) time (h:mm:ss or m:ss): 4:40:47
        Average shared text size (kbytes): 0
        Average unshared data size (kbytes): 0
        Average stack size (kbytes): 0
        Average total size (kbytes): 0
        Maximum resident set size (kbytes): 14593432
        Average resident set size (kbytes): 0
        Major (requiring I/O) page faults: 0
        Minor (reclaiming a frame) page faults: 2978846
        Voluntary context switches: 74
        Involuntary context switches: 1697365
        Swaps: 0
        File system inputs: 0
        File system outputs: 0
        Socket messages sent: 0
        Socket messages received: 0
        Signals delivered: 0
        Page size (bytes): 4096
        Exit status: 0
```

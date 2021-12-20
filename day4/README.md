# Day 4

https://adventofcode.com/2021/day/4

```
c++ -std=c++17 -O2 main.cpp -o main

# Usage:
# ./main <input filename>

./main input.txt
```

```
➜ …src/aoc2021/day4 ./main test.txt
Got 27 draws and 3 cards
Draw: 7
Draw: 4
Draw: 9
Draw: 5
Draw: 11
Draw: 17
Draw: 23
Draw: 2
Draw: 0
Draw: 14
Draw: 21
Draw: 24
Bingo! Card value is 188 for a score of 4512
Draw: 10
Draw: 16
Bingo! Card value is 137 for a score of 2192
Draw: 13
Bingo! Card value is 148 for a score of 1924

➜ …src/aoc2021/day4 time ./main input.txt
Got 100 draws and 100 cards
Draw: 67
Draw: 31
Draw: 58
Draw: 8
Draw: 79
Draw: 18
Draw: 19
Draw: 45
Draw: 38
Draw: 13
Draw: 40
Draw: 62
Draw: 85
Draw: 10
Bingo! Card value is 1068 for a score of 10680
Draw: 21
Draw: 96
Draw: 56
Draw: 55
Draw: 4
Draw: 36
Draw: 76
Draw: 42
Draw: 32
Draw: 34
Bingo! Card value is 786 for a score of 26724
Draw: 39
Draw: 89
Draw: 6
Draw: 12
Draw: 24
Draw: 57
Draw: 93
Draw: 47
Draw: 41
Draw: 52
Draw: 83
Bingo! Card value is 563 for a score of 46729
Draw: 61
Bingo! Card value is 754 for a score of 45994
Bingo! Card value is 739 for a score of 45079
Bingo! Card value is 698 for a score of 42578
Draw: 5
Bingo! Card value is 819 for a score of 4095
Bingo! Card value is 832 for a score of 4160
Bingo! Card value is 765 for a score of 3825
Draw: 37
Bingo! Card value is 631 for a score of 23347
Draw: 28
Bingo! Card value is 532 for a score of 14896
Bingo! Card value is 804 for a score of 22512
Draw: 15
Draw: 86
Draw: 23
Draw: 69
Draw: 92
Bingo! Card value is 728 for a score of 66976
Bingo! Card value is 634 for a score of 58328
Bingo! Card value is 509 for a score of 46828
Draw: 70
Bingo! Card value is 730 for a score of 51100
Bingo! Card value is 680 for a score of 47600
Bingo! Card value is 673 for a score of 47110
Draw: 27
Bingo! Card value is 814 for a score of 21978
Draw: 25
Draw: 53
Bingo! Card value is 655 for a score of 34715
Bingo! Card value is 557 for a score of 29521
Draw: 44
Bingo! Card value is 592 for a score of 26048
Bingo! Card value is 667 for a score of 29348
Bingo! Card value is 515 for a score of 22660
Draw: 80
Bingo! Card value is 485 for a score of 38800
Draw: 65
Bingo! Card value is 719 for a score of 46735
Draw: 22
Bingo! Card value is 720 for a score of 15840
Bingo! Card value is 610 for a score of 13420
Draw: 99
Bingo! Card value is 539 for a score of 53361
Bingo! Card value is 373 for a score of 36927
Bingo! Card value is 574 for a score of 56826
Draw: 43
Draw: 66
Bingo! Card value is 820 for a score of 54120
Draw: 26
Bingo! Card value is 710 for a score of 18460
Bingo! Card value is 599 for a score of 15574
Bingo! Card value is 438 for a score of 11388
Draw: 11
Bingo! Card value is 549 for a score of 6039
Bingo! Card value is 546 for a score of 6006
Bingo! Card value is 762 for a score of 8382
Bingo! Card value is 441 for a score of 4851
Bingo! Card value is 656 for a score of 7216
Bingo! Card value is 322 for a score of 3542
Draw: 72
Bingo! Card value is 286 for a score of 20592
Bingo! Card value is 655 for a score of 47160
Bingo! Card value is 435 for a score of 31320
Bingo! Card value is 597 for a score of 42984
Bingo! Card value is 447 for a score of 32184
Draw: 2
Bingo! Card value is 418 for a score of 836
Bingo! Card value is 461 for a score of 922
Bingo! Card value is 578 for a score of 1156
Draw: 98
Bingo! Card value is 435 for a score of 42630
Draw: 14
Bingo! Card value is 452 for a score of 6328
Bingo! Card value is 698 for a score of 9772
Draw: 82
Bingo! Card value is 464 for a score of 38048
Draw: 87
Bingo! Card value is 445 for a score of 38715
Bingo! Card value is 545 for a score of 47415
Bingo! Card value is 599 for a score of 52113
Bingo! Card value is 355 for a score of 30885
Bingo! Card value is 369 for a score of 32103
Bingo! Card value is 295 for a score of 25665
Bingo! Card value is 678 for a score of 58986
Draw: 20
Bingo! Card value is 292 for a score of 5840
Bingo! Card value is 578 for a score of 11560
Draw: 73
Bingo! Card value is 417 for a score of 30441
Bingo! Card value is 567 for a score of 41391
Bingo! Card value is 438 for a score of 31974
Bingo! Card value is 494 for a score of 36062
Draw: 46
Bingo! Card value is 529 for a score of 24334
Bingo! Card value is 371 for a score of 17066
Draw: 35
Bingo! Card value is 543 for a score of 19005
Bingo! Card value is 361 for a score of 12635
Bingo! Card value is 685 for a score of 23975
Bingo! Card value is 284 for a score of 9940
Bingo! Card value is 595 for a score of 20825
Bingo! Card value is 442 for a score of 15470
Draw: 7
Bingo! Card value is 578 for a score of 4046
Draw: 1
Bingo! Card value is 427 for a score of 427
Bingo! Card value is 424 for a score of 424
Bingo! Card value is 427 for a score of 427
Bingo! Card value is 438 for a score of 438
Draw: 84
Bingo! Card value is 299 for a score of 25116
Bingo! Card value is 337 for a score of 28308
Draw: 95
Bingo! Card value is 436 for a score of 41420
Draw: 74
Bingo! Card value is 431 for a score of 31894
Bingo! Card value is 336 for a score of 24864
Draw: 81
Bingo! Card value is 301 for a score of 24381
Bingo! Card value is 600 for a score of 48600
Draw: 63
Bingo! Card value is 473 for a score of 29799
Draw: 78
Bingo! Card value is 368 for a score of 28704
Bingo! Card value is 463 for a score of 36114
Draw: 94
Bingo! Card value is 218 for a score of 20492
Bingo! Card value is 470 for a score of 44180
Draw: 16
Draw: 60
Bingo! Card value is 394 for a score of 23640
Bingo! Card value is 329 for a score of 19740
Bingo! Card value is 449 for a score of 26940
Bingo! Card value is 333 for a score of 19980
Draw: 29
Bingo! Card value is 313 for a score of 9077
Draw: 97
Bingo! Card value is 295 for a score of 28615
Bingo! Card value is 266 for a score of 25802
Draw: 91
Draw: 30
Bingo! Card value is 269 for a score of 8070
Draw: 17
Draw: 54
Draw: 68
Bingo! Card value is 469 for a score of 31892
./main input.txt  0.01s user 0.00s system 34% cpu 0.045 total
```

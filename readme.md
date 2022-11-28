## cdoku

this is a relativley simple and efficent sudoku puzzle brute force algorithm!

check out ./example.sudoku and ./main.c for more documentation:)

### building and running

`just b` or `gcc -o cdoku main.c` to build the binary

check out `just --list` for more options

`cdoku {file path}`

### examples and some bench marks

1.80 GHz arm  -  ~1.3s  </br>
1.60 GHz x86  -  ~0.169s</br>
3.18 GHz x86  -  ~0.02s </br>

### todo

- read json formated
- read sudoku as argument

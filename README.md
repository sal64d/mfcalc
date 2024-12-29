# mfcalc
Simple multifunction calculator using bison and c

## How to run
- Compile parser using the following command:
```
bison parser.y
```

- Build the program using gcc:
```
gcc lexer.c calc.c parser.c main.c -o mfcalc.out
```

- Run the program
```
./mfcalc.out
```


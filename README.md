## Compilation instructions

While I've tried my level best to avoid any Unix-specific libraries, I have not been able to compile test this on Windows, since
the only machine I had was a Macbook. Even so, the Makefile is fairly straightforward, so should be easy to translate to the equivalent on Windows.

To build and run the tests:
```
make test
```

To build the main binary:
```
make
```

To clean all built objects:
```
make clean
```

## Running instructions

To run the program:
```
./gol <pattern>
```

The following `pattern` values are supported:
- `RANDOM`
- `TOAD`
- `BLINKER`
- `BEACON`

If no argument is provided, `RANDOM` is executed as the default.

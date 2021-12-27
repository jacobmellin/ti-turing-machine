# TI Deterministic Turing Machine Implementation

## How to build

- Make sure gcc and graphviz are installed
- Run `make`

## Usage

### Simulate a universal turing machine code on an input:

```bash
./ti_turing c#w
```
Where `c` is the machine coding and `w` is an input word. Use `c#` if you want to simulate the machine on a λ input word.

The program returns 1 if the word is accepted and 0 if the word is discarded.

**Example:**

```
./ti_turing 0001000101000101001001001001001010101001001000100010001001#101
```

### Limit the number of steps

Use the parameter `-t` to provide a maximum number of steps (before providing the coding).

**Example:**

```
./ti_turing -t 30 01000110100010100010001#
```

### Export a graph representation of the machine

Use the parameter `-g filename.pdf` (before the machine code) to export a graph representation of the machine in PDF format.

**Example:**

```
./ti_turing -g graph.pdf 0001000101000101001001001001001010101001001000100010001001#101
```

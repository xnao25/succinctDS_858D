## Usage of Bit-Vector Select
The implementation of bit-vector select operation is written into a class called **select_support**. It is built upon **rank_support object**.A **bit-vector** is required. All source files are in folder **succinctDS_Select**. Implementation can be used as classed or a command line program.

### Usage as an object

Three methods are implemented in this structure:
- `uint64_t select1(uint64_t i)` Returns the index(0-based) of the underlying bit-vector of the ith 1.
- `uint64_t select0(uint64_t i)` Returns the index(0-based) of the underlying bit-vector of the ith 0.
- `uint64_t overhead()` Returns the size of the data structure (in bits) used in this implementation.

Example code:
```
bit_vector b("1001011101001010");
rank_support r(&b);
select_support s(&r);
uint64_t y=s.select1(3);//y=5
```

### Usage as a program
**Compilation**

Prerequisite: C++11

Steps:
1. Clone this repository to you local directory.
2. `$cd succinctDS_858D/succinctDS_Select/`
3. `$./make` An executable program called `SuccinctSelect` will appear in the directory.

**Commands and Options**
- `$./SuccinctSelect select1 <input_bit_string> <occurrence>`   return the result from method select1
- `$./SuccinctSelect select0 <input_bit_string> <occurrence>`   return the result from method select0
- `$./SuccinctSelect --h`   show help messages

Example input and output:
```
$./SuccinctSelect select1 010101 3
Result:	select1 at 3 is 5
```

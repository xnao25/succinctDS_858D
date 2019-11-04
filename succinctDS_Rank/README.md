## Usage of Bit-Vector Rank
The implementation of bit-vector rank operation is written into a class called **rank_support**. A **bit-vector** is required. All source files are in folder **succinctDS_Rank**. Implementation can be used as classed or a command line program.
[GitHub Repository: https://github.com/xnao25/succinctDS_858D](https://github.com/xnao25/succinctDS_858D)

### Usage as an object
Three methods are implemented in this structure:
- `uint64_t rank1(uint64_t i)` Returns the number of 1s in the underlying bit-vector up to index(0-based) i (inclusive).
- `uint64_t rank0(uint64_t i)` Returns the number of 0s in the underlying bit-vector up to index(0-based) i (inclusive).
- `uint64_t overhead()` Returns the size of the data structure (in bits) used in this implementation.

Example code:
```
bit_vector b("1001011101001010");
rank_support r(&b);
uint64_t x=r.rank1(4);//x=3
```

### Usage as a program
**Compilation**

Prerequisite: C++11

Steps:
1. Clone this repository to you local directory.
2. `$cd succinctDS_858D/succinctDS_Rank/`
3. `$./make` An executable program called `SuccinctRank` will appear in the directory.

**Commands and Options**
- `$./SuccinctRank rank1 <input_bit_string> <index 0-based>`   return the result from method rank1
- `$./SuccinctRank rank0 <input_bit_string> <index 0-based>`   return the result from method rank0
- `$./SuccinctRank --h`   show help messages

Example input and output:
```
$./SuccinctRank rank1 010101 3
Result:	rank1 at 3 is 2
```

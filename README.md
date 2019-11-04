# succinctDS_858D
Succinct Data Structure and Wavelet Tree implementations. (Assignment#1 for CMSC858D-Fall2019)
[GitHub Repository: https://github.com/xnao25/succinctDS_858D](https://github.com/xnao25/succinctDS_858D)
----------------------------
# Overview
This program contains 3 major succinct primitives: bit-vector rank, bit-vector select, and wavelet-tree. More information about installation and usage can be found below.

----------------------------
# Usage
## 1. Bit-Vector Rank
The implementation of bit-vector rank operation is written into a class called **rank_support**. A **bit-vector** is required. All source files are in folder **succinctDS_Rank**. Implementation can be used as classed or a command line program.

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

## 2. Bit-Vector Select
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

## 3. Wavelet-Tree
The implementation of wavelet-tree is written into a class called **wavelet_tree**. It is built upon **rank_support** and **select_support**.

Methods in this implementation can be used either as a class object or as a program after compilation.

### Usage as an object

Four major methods:
- `tree_build()` Builds a wavelet tree structure. The tree will be built based on a string which is given at the initiation of the object. (The basis of other methods)
- `char tree_access(unsigned int access_idx)` Returns the character at the given index(0-based) provided.
- `uint64_t tree_rank(char the_character, uint64_t the_idx)` Returns the number of the given character in the underlying string up to index(0-based) i (inclusive). If character is not in the string or the index provided is larger than the length of the string-1, the result will be -1.
- `uint64_t tree_select(char the_character, uint64_t i)` Returns the index(0-based) of the underlying string of the ith the_character. If character is not in the string or the occurrence provided is larger than the rank of such character at the end of the string, the result will be -1.

Example code:
```
wavelet_tree wlt("0167154263abc");
wlt.tree_build();
char z_access=wlt.access(3);//z_access='7'
uint64_t z_rank=wlt.rank('1',5);//z_rank=2
uint64_t z_select=wlt.select('c',1);//z_select=12
```

### Usage as a program
**Compilation**

Prerequisite: C++11

Steps:
1. Clone this repository to you local directory.
2. `$cd succinctDS_858D/WaveletTree/`
3. `$./make` An executable program called `WVLTREE` will appear in the directory.

**Commands and Options**
1. build
  - `$./WVLTREE build <input_string> <output_tree_file>` 
  - A wavelet tree structure will be built based on the string provided. The wavelet tree structure will be stored into output_tree_file and this file can be furthur used for other calculations. The total number of characters and unique characters will be returned on the terminal.
  - Input: `<input_string>` A string. The wavelet tree will be built based on the string.
  - Output: `<output_tree_file>` A text file containing the structure of the wavelet tree built.
2. access
  - `$./WVLTREE access <input_tree_file> <access indices>` 
  - The character(s) at the given index(es) will be returned on the terminal.
  - Input: `<input_tree_file>` A text file containing the structure of the wavelet tree. It is usually the output of the command `build`.
  - Input: `<access indices>` A text file containing a "\n"-separated list of indices (0-based) to access.
3. rank
  - `$./WVLTREE rank <input_tree_files> <access indices>`
  - The rank(s) of the character(s) at the given index(es) will be returned on the terminal. The defination of rank is that the number of the given character in the underlying string up to index(0-based) i (inclusive).
  - Input: `<input_tree_file>` A text file containing the structure of the wavelet tree. It is usually the output of the command `build`.
  - Input: `<access indices>` A text file containing a "\n"-separated list of indices to access. The format of each line should be `<c>\t<i>`, where `<c>` is the character and `<i>` is the 0-based index.
4. select
  - `$./WVLTREE select <input_tree_files> <access indices>`
  - The select(s) of the character(s) at the given index(es) will be returned on the terminal. The defination of select is that the index(0-based) of the underlying string of the ith the_character.
  - Input: `<input_tree_file>` A text file containing the structure of the wavelet tree. It is usually the output of the command `build`.
  - Input: `<access indices>` A text file containing a "\n"-separated list of indices to access. The format of each line should be `<c>\t<i>`, where `<c>` is the character and `<i>` is the 0-based index.

Example input and output:

- build command
```
$./WVLTREE build 0167154263abc test_output_2.txt
Messages:
Your wavelet tree is built, please see more information in your output file.
There are 11 unique characters in your string.
The total number of characters in your string is 13.
```
- build output
```
$cat test_output_2.txt
#Elements & Corresponding integers:
0:0	1:1	2:2	3:3	4:4	5:5	6:6	7:7	a:8	b:9	c:10

#Wavelet Tree Structure:
0	0	0	0	0	0	0	0	0	0	1	1	1
0	0	1	1	0	1	1	0	1	0	0	0	0
0	0	0	1	1	1	1	0	0	1	0	0	1
0	1	1	0	1	1	0	0	1	0	0	1	0

#Wavelet Tree Position:
0:0	1:10
00:0	01:5	10:10	11:13
000:0	001:3	010:5	011:7	100:10	101:12	110:13	111:13
```
- access command input
```
cat test_access_input.txt
0
3
5
7
```
- access command
```
$./WVLTREE access test_output_2.txt test_access_input.txt
0
7
5
2
```
- rank command input
```
$cat test_rank_input.txt
0	10
1	20
8	20
a	10
p	3
```
- rank command
```
./WVLTREE rank test_output_2.txt test_rank_input.txt
1
-1
-1
1
-1
```
- select command input
```
$cat test_select_input.txt
1	2
0	2
a	1
b	1
c	1
```
- select command
```
$./WVLTREE select test_output_2.txt test_select_input.txt
4
-1
10
11
12
```

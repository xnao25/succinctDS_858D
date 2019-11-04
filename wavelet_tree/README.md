## Usage of Wavelet-Tree
The implementation of wavelet-tree is written into a class called **wavelet_tree**. It is built upon **rank_support** and **select_support**.

Methods in this implementation can be used either as a class object or as a program after compilation.

### Usage as an object

Four major methods:
- `tree_build()` Builds a wavelet tree structure. The tree will be built based on a string which is given at the initiation of the object. (The basis of other methods)
- `char tree_access(unsigned int access_idx)` Returns the character at the given index(0-based) provided.
- `uint64_t tree_rank(char the_character, uint64_t the_idx)` Returns the number of the given character in the underlying string up to index(0-based) i (inclusive).
- `uint64_t tree_select(char the_character, uint64_t i)` Returns the index(0-based) of the underlying string of the ith the_character.

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

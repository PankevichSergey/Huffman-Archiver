#  Archiver

 This archiver uses [Haffman Algorithm](https://en.wikipedia.org/wiki/Huffman_coding).

It has a simple console interface, call `archiver -h` to find out more.


## Format of file
9-bit values are written in little-endian format. 

File produced by archiver has the following format:
1. 9 bits -- the size of an alphabet `SYMBOLS_COUNT`
1. Block of data for restoring canonical codes 
1. `SYMBOLS_COUNT` 9-bit values - alphabet symbols in order of their canonical codes
1. The list of `MAX_SYMBOL_CODE_SIZE` 9-bit values, i-й (0-based indexing) element - is a number of symbols which codes have lengths equal to  `i+1`. `MAX_SYMBOL_CODE_SIZE` - the biggest lengths of a code among all symbols. Canonical codes go in the same order as in the previous parahraph. `MAX_SYMBOL_CODE_SIZE` is not clearly written in the file  as it can be restored from the previous data.
1. Encoded file name
1. Encoded special symbol`FILENAME_END`
1. Encoded file
1. Encoded special symbol `ONE_MORE_FILE` if the archive contains another file and encoding continues from the first paragraph
1. Encoded special symbol `ARCHIVE_END`.


## Other information

Encoding and decoding algorithms don't focus on files and work with steams.

Archiver correctly works with files that exceed RAM.

Project contains:
1. Classes that alow to read and write via streams and read and write 1-bits and 9-bits values

1. Trie with an interface 

1. Heap 



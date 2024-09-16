# DNA File Encoder/Decoder

This C program encodes binary files into DNA sequences using the letters `A`, `C`, `G`, and `T`, and decodes them back to their original binary format. The program uses 2-bit encoding, where each byte of the file is broken down into 2-bit pairs that are then mapped to DNA bases.

## Features

- **Encoding**: Convert any binary file into a DNA sequence.
- **Decoding**: Reconstruct the original binary file from the DNA sequence.
- **File extension preservation**: The file extension is saved during encoding and restored during decoding.

## Requirements

- GCC or any C compiler
- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`

## How to Use

### Compilation

First, compile the program using a C compiler:

```bash
gcc -o dna_encoder_decoder dna_encoder_decoder.c
```

### Encoding a File

To encode a file, use the `-e` option followed by the file name:

```bash
./dna_encoder_decoder -e input_file
```

This will generate a text file containing the DNA sequence, with the file extension saved at the beginning.

### Decoding a File

To decode a previously encoded file, use the `-d` option followed by the encoded file's name:

```bash
./dna_encoder_decoder -d encoded_file.txt
```

The program will output the original file with its correct extension restored.

## Example

### Encoding a File

```bash
./dna_encoder_decoder -e example.bin
```

This command will create an output file `example.bin.txt` containing the encoded DNA sequence.

### Decoding a File

```bash
./dna_encoder_decoder -d example.bin.txt
```

This command will reconstruct the original file, `example.bin`.

## Error Handling

- If files cannot be opened for reading or writing, the program will display an error message and exit.
- The program checks for valid input formats and prints usage instructions if arguments are incorrect.

## Notes

- The encoding uses 2 bits per DNA base:
  - `00 -> A`
  - `01 -> C`
  - `10 -> G`
  - `11 -> T`

- The file extension is stored in the first line of the encoded output and is required for proper decoding.

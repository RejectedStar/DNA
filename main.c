#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_ENCODING_SIZE 4
#define DNA_ENCODING_SIZE 2

void encode_file(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "rb");
    FILE *output_file = fopen(output_filename, "w");
    if (!input_file || !output_file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    const char *dot = strrchr(input_filename, '.');
    if (dot) {
        fprintf(output_file, "%s\n", dot + 1);
    } else {
        fprintf(output_file, "noext\n");
    }

    int byte;
    while ((byte = fgetc(input_file)) != EOF) {
        for (int i = 0; i < 8; i += 2) {
            unsigned char pair = (byte >> (6 - i)) & 0x03;
            switch (pair) {
                case 0: fputc('A', output_file); break;
                case 1: fputc('C', output_file); break;
                case 2: fputc('G', output_file); break;
                case 3: fputc('T', output_file); break;
            }
        }
    }

    fclose(input_file);
    fclose(output_file);
}

void decode_file(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    FILE *output_file = fopen(output_filename, "wb");
    if (!input_file || !output_file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char ext[256];
    if (!fgets(ext, sizeof(ext), input_file)) {
        perror("Error reading file extension");
        exit(EXIT_FAILURE);
    }

    ext[strcspn(ext, "\n")] = '\0';

    int byte = 0, bit_count = 0;
    int c;
    while ((c = fgetc(input_file)) != EOF) {
        unsigned char pair;
        switch (c) {
            case 'A': pair = 0; break;
            case 'C': pair = 1; break;
            case 'G': pair = 2; break;
            case 'T': pair = 3; break;
            default: continue; 
        }

        byte = (byte << 2) | pair;
        bit_count += 2;

        if (bit_count == 8) {
            fputc(byte, output_file);
            bit_count = 0;
            byte = 0;
        }
    }

    if (bit_count != 0) {
        byte <<= (8 - bit_count);
        fputc(byte, output_file);
    }

    fclose(input_file);
    fclose(output_file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s -e|-d filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-e") == 0) {
        char output_filename[256];
        snprintf(output_filename, sizeof(output_filename), "%s.txt", argv[2]);
        encode_file(argv[2], output_filename);
    } else if (strcmp(argv[1], "-d") == 0) {
        FILE *input_file = fopen(argv[2], "r");
        if (!input_file) {
            perror("Error opening input file");
            return EXIT_FAILURE;
        }

        char ext[256];
        if (!fgets(ext, sizeof(ext), input_file)) {
            perror("Error reading file extension");
            return EXIT_FAILURE;
        }

        fclose(input_file);

        ext[strcspn(ext, "\n")] = '\0';

        char output_filename[256];
        snprintf(output_filename, sizeof(output_filename), "decoded_file.%s", ext);
        decode_file(argv[2], output_filename);
    } else {
        fprintf(stderr, "Invalid argument. Use -e for encoding or -d for decoding.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

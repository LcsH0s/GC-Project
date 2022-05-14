#ifndef COMPRESSION
#define COMPRESSION

void compress_map(char *filename);
void compression_effectiveness(char *filename);
void decompress_map();
void print_compressed_map();
void print_decompressed_map();
void rle_compress(const char *src, const char *dst);
void rle_decompress(const char *src, const char *dst);

#endif

#ifndef COMPRESSION
#define COMPRESSION

void compress_map(char *filename);
void compression_effectiveness(char *filename);
void decompress_map();
void print_compressed_map();
void print_decompressed_map();
void rle_compress_solution(const char *src, const char *dst);
void rle_decompress_solution(const char *src, const char *dst);

#endif

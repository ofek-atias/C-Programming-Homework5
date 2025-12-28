#include <stdio.h>

#define SIZE_BYTES 1 
#define MAX_FILE_SIZE 1048576  //1 MB (2^20 byte)
#define MAX_NUM_BYTES 256

typedef struct {
  unsigned long int cnt_1;
  unsigned long int cnt_0;
  unsigned long int cnt_bytes;
  unsigned char byte_freq;
  unsigned char byte_mdl;
} stats_t;

static void print_stats(stats_t stats) {
  printf("Total bits set to 1: %lu\n", stats.cnt_1);
  printf("Total bits set to 0: %lu\n", stats.cnt_0);
  printf("Total number of bytes: %lu\n", stats.cnt_bytes);
  printf("Most frequent byte value: 0x%X\n", stats.byte_freq);
  printf("Middle byte value: 0x%X\n", stats.byte_mdl);
}

static stats_t compute_stats(FILE *file) {

  stats_t stats = {0, 0, 0, 0, 0};
  unsigned char buffer[MAX_FILE_SIZE];
  unsigned long freq[MAX_NUM_BYTES] = {0};
  size_t bytes_read = 0;

  bytes_read = fread(buffer, 1, MAX_FILE_SIZE, file);
  stats.cnt_bytes = (unsigned long)bytes_read;

  if (stats.cnt_bytes == 0) 
    return stats;

  for (size_t i = 0; i < bytes_read; i++) {
      unsigned char current_byte = buffer[i];
      
      // Update frequency
      freq[current_byte]++;

      // Count bits
      for (int b = 0; b < 8; b++) {
          if ((current_byte >> b) & 1) {
              stats.cnt_1++;
          }

          else {
              stats.cnt_0++;
          }
      }
      // Determine most frequent byte 
    unsigned long max_freq = 0;
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            stats.byte_freq = (unsigned char)i;
        }
        // Smallest value is kept on tie because we only update if strictly greater 
    }

    // Determine middle byte
    
  }

  stats.byte_mdl = buffer[bytes_read / 2];

  return stats;
}

int main(int argc, char *argv[]) {
  stats_t stats;

  // check input argument
  if (argc != 2) {
    printf("Usage: %s <binary_file>\n", argv[0]);
    return 0;
  }

  FILE *file = fopen(argv[1], "rb");
  if (file == NULL) {
    printf("Error opening file: %s\n", argv[1]);
    return 0;
  }

  stats = compute_stats(file);
  fclose(file);

  // print the results
  print_stats(stats);

  return 0;
}

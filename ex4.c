// TODO: add includes here
#include "parser.h"

#define SHIFT_V 29
#define SHIFT_L 25
#define SHIFT_T 20
#define SHIFT_SN 13
#define SHIFT_DN 6
#define SHIFT_P 4
#define SHIFT_E 3

// encoding the packet fields according to the layout
static unsigned int encode_packet_header(header_t* hdr) {
  unsigned int packet = 0;
  packet |= hdr->version << SHIFT_V;
  packet |= hdr->length << SHIFT_L;
  packet |= hdr->type << SHIFT_T;
  packet |= hdr->src_node << SHIFT_SN;
  packet |= hdr->dst_node << SHIFT_DN;
  packet |= hdr->priority << SHIFT_P;
  packet |= hdr->encrypted << SHIFT_E;
  
  unsigned int count = 0;
  unsigned int checksum = 0;

  unsigned int temp = packet;

  // We can skip the first 3 bits that represent the checksum value
  temp = temp >> 3;

  while (temp != 0) {
    if (temp & 1 == 1) {
      count++;
    }
    temp = temp >> 1;
  }

  checksum = count & 7;
  packet |= checksum;
  return packet;
}

// print header
static void print_header(unsigned int hdr_buf) {
  printf("The Encoded Packet Header is: 0x%08X\n", hdr_buf);
}

// TODO: fill the code
int main(int argc, const char *argv[]) {
  
  // TODO: check if need to print help (no args or only help)
  if ((argc == 2 && strcmp(argv[1], HELP_FLAG) == 0) || (argc == 1)) {
      print_help();
      return OK;
  }

  header_t* hdr = (header_t*)malloc(sizeof(header_t));

  // TODO: parse arguments
  err_t status = parse_args(argc, argv, hdr);

  if (status == OK) {
    // TODO: encode the packet header
    unsigned int packet = encode_packet_header(hdr);

    // TODO: print the encoded header
    print_header(packet);
  }

  free(hdr);
  return OK;
}

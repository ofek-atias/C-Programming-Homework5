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
static unsigned int encode_packet_header(header_t hdr) {
  unsigned int packet = 0;
  packet |= hdr.version << SHIFT_V;
  packet |= hdr.length << SHIFT_L;
  packet |= hdr.type << SHIFT_T;
  packet |= hdr.src_node << SHIFT_SN;
  packet |= hdr.dst_node << SHIFT_DN;
  packet |= hdr.priority << SHIFT_P;
  packet |= hdr.encrypted << SHIFT_E;
  
  unsigned int count = 0;
  unsigned int checksum = 0;

  for (int i = 3; i < 32; i++)
  {
    if((packet >> i)&1 == 1)
      count++;
  }
  checksum = count&7;
  packet|=checksum;
  return packet;
}

// print header
static void print_header(unsigned int hdr_buf) {
  printf("The Encoded Packet Header is: 0x%08X\n", hdr_buf);
}

// TODO: fill the code
int main(int argc, const char *argv[]) {
  header_t hdr = {};
  unsigned int hdr_buf;
  err_t ret;

  // TODO: check if need to print help (no args or only help)

  // TODO: parse arguments

  // TODO: encode the packet header

  // TODO: print the encoded header

  return OK;
}

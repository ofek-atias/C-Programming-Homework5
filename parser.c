#include "parser.h"

#define FIELDS_LEN(flags) (sizeof(flags) / sizeof(flags_t))

#define FIELDS_MIN 0
#define VERSION_MAX 7
#define LENGTH_MAX 15
#define PACKET_TYPE_MAX 31
#define NODE_MAX 127
#define PRIORITY_MAX 2
#define ENCRYPTED 1

typedef struct {
  const char *short_name;
  const char *long_name;
  const char *description;
  unsigned int min;
  unsigned int max;
} flags_t;

static const flags_t flags[] = {
    {HELP_FLAG, "Help", "Print this description", FIELDS_MIN, FIELDS_MIN},
    {"-v", "Version", "Protocol version", FIELDS_MIN, VERSION_MAX},
    {"-l", "Packet Length", "Packet length in 4 bytes units", FIELDS_MIN,
     LENGTH_MAX},
    {"-t", "Packet Type", "Packet type", FIELDS_MIN, PACKET_TYPE_MAX},
    {"-s", "Source Node", "Sender address", FIELDS_MIN, NODE_MAX},
    {"-d", "Destination Node", "Receiver address", FIELDS_MIN, NODE_MAX},
    {"-p", "Priority", "Priority class (0 = low … 2 = high)", FIELDS_MIN,
     PRIORITY_MAX},
    {"-e", "Encrypted", "1 if the packet is encrypted", FIELDS_MIN, ENCRYPTED}};

void print_help() {
  printf("Usage:\n");
  for (int i = 0; i < FIELDS_LEN(flags); i++) {
    printf("%*s%*s [%u-%u]:\t%s,\n", 4, flags[i].short_name, 17,
           flags[i].long_name, flags[i].min, flags[i].max,
           flags[i].description);
  }
  printf("Please try again.\n");
}

static const flags_t* get_flag_info(const char* arg) {
    for (int i = 0; i < FIELDS_LEN(flags); i++) {
        if (strcmp(arg, flags[i].short_name) == 0) {
            return &flags[i];
        }
    }
    return NULL;
}

int string_to_uint(const char* s, unsigned int* out)
{
    char* end;
    unsigned long val;

    errno = 0;
    val = strtoul(s, &end, 10);

    /* No digits found */
    if (end == s)
        return -1;

    /* Extra characters after number */
    if (*end != '\0')
        return -1;

    /* Overflow or underflow */
    if (errno == ERANGE || val > UINT_MAX)
        return -1;

    *out = (unsigned int)val;
    return 1;
}

// parse the arguments, and fill p_hdr
err_t parse_args(int argc, const char *argv[], header_t *p_hdr) {

  // TODO: check parameters
  if (p_hdr == NULL || argv == NULL) {
    return ERR_PARAMS;
  }

  // TODO: check number of arguments
  if (argc != 15) {
    printf("Error: number of given arguements %d is different than expected\n", argc);
    return ERR_NUM_ARGS;
  }

  // TODO: parse the arguments
  for (int i = 1; i < argc; i += 2) {
      const flags_t* info = get_flag_info(argv[i]);

      if (info == NULL) {
        printf("Error: Unknown flag: \"%s\"\n", argv[i]);
        return ERR_UNKNOWN_FLAG;
      }

      /*
        Take a look at the example of such arguments:
        argv = {"ex4.exe", "-v", "1", "-t"}
        argc = 4
        In the first iteration, i = 1, and it works fine.
        In the second iteration, i = 3, which means our current value is "-t".
        This is the last value in the argv array, and we are about to check the next one (with i + 1).
        Before we do that, we need to check that i + 1 is within the argv size (argc), because if not,
        in this example, we are gonna get an out_of_range error (since i + 1 = 4, and there is no index 4 in argv).
      */
      if (i + 1 >= argc) {
        printf("Error: Missing argument for flag \"%s\"\n", argv[i]);
        return ERR_MISSING_ARG;
      }

      unsigned int val;
      if (string_to_uint(argv[i+1], &val) == -1) {
        printf("Error: Missing argument for flag \"%s\"\n", argv[i]);
        return ERR_MISSING_ARG;
      }

      if (val < info->min || val > info->max) {
          printf("Error: value %d for flag \"%s\" (%s) is out of range [%u-%u]\n", val, info->short_name, info->long_name, info->min, info->max);
          return ERR_INVALID_VALUE;
      }

      if (strcmp(argv[i], "-v") == 0) p_hdr->version = (unsigned char)val;
      else if (strcmp(argv[i], "-l") == 0) p_hdr->length = (unsigned char)val;
      else if (strcmp(argv[i], "-t") == 0) p_hdr->type = (unsigned char)val;
      else if (strcmp(argv[i], "-s") == 0) p_hdr->src_node = (unsigned char)val;
      else if (strcmp(argv[i], "-d") == 0) p_hdr->dst_node = (unsigned char)val;
      else if (strcmp(argv[i], "-p") == 0) p_hdr->priority = (unsigned char)val;
      else if (strcmp(argv[i], "-e") == 0) p_hdr->encrypted = (val != 0);
  }
  
  return OK;
}

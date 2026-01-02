#include <stdio.h>

int main() {
    unsigned char data[] = {
        0x00, 0x0F, 0x33, 0x80, 0xAA, 0xC0, 0xEE, 0xFF, 0x05, 0x07,
        0x09, 0xFF, 0xEE, 0xC0, 0xAA, 0x80, 0x33, 0x0F, 0x00, 0x01
    };
    FILE *f = fopen("test_data.bin", "wb");

    for (int i = 0; i < 1000; i++) {
        unsigned char b = (unsigned char)(i % 100);
        fwrite(&b, 1, 1, f);
    }

    //fwrite(data, sizeof(unsigned char), 15, f);
    fclose(f);
    printf("test_data.bin created successfully.\n");
    return 0;
}
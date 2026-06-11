#include <cassert>
#include <cstdint>
#include <cstdio>

void process3(FILE* file)
{
    uint16_t num_elem;
    size_t ret = fread(&num_elem, sizeof(uint16_t), 1, file);
    assert(ret == 1);
    fprintf(stdout, "num-elem: %04x\n", num_elem);
    for (uint16_t i = 0; i < num_elem; i++)
    {
        uint16_t len;
        ret = fread(&len, sizeof(uint16_t), 1, file);
        assert(ret == 1);
        char buffer[512];
        assert(len < 512);
        ret = fread(buffer, sizeof(char), len, file);
        assert(ret == len);
        buffer[len] = '\0';
        fprintf(stdout, "%u : %s\n", len, buffer);
    }
    uint32_t tag;
    uint32_t zero;
    ret = fread(&tag, sizeof(uint32_t), 1, file);
        assert(ret == 1);
    ret = fread(&zero, sizeof(uint32_t), 1, file);
        assert(ret == 1);
    //assert(zero == 0);
    fprintf(stdout, "tag %08x : %008x\n", tag, zero);
}

int main(int argc, char* argv[])
{
    const char* filename = argv[1];
    FILE* f = fopen(filename, "rb");
    int offset = 0x0D30;
    offset -= 2;
    fseek(f, offset, SEEK_SET);
    for (int i = 0; i < 17; i++)
        process3(f);
    fclose(f);
}

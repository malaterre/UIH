#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>

struct entry
{
    char name[512];
    char type[512];
};

static const char* types[] = {
    "int64",
    "double",
    "string"
};

enum EType
{
    Invalid = -1,
    Int64 = 0,
    Double = 1,
    String = 2,
};

EType get_type(const char* type)
{
    static const size_t n = sizeof(types) / sizeof(types[0]);
    for (size_t i = 0; i < n; i++)
    {
        if (strcmp(type, types[i]) == 0) return static_cast<EType>(i);
    }
    return static_cast<EType>(-1);
}

void p1(FILE* file, char buffer[512])
{
    uint32_t zero;
    uint32_t len;
    size_t ret;
    ret = fread(&len, sizeof(uint32_t), 1, file);
    assert(ret == 1);
    fprintf(stdout, "len %08x: ", len);
    ret = fread(&zero, sizeof(uint32_t), 1, file);
    assert(ret == 1);
    assert(zero==0);
    ret = fread(buffer, sizeof(char), len, file);
    assert(ret == len);
    buffer[len] = '\0';
    fprintf(stdout, "[%s]", buffer);
    fprintf(stdout, "\n");
}

void read_type(const entry* entry, FILE* file)
{
    int type = get_type(entry->type);

    size_t ret;
    if (type == Int64)
    {
        for (int i = 0; i < 4; i++)
        {
            uint32_t junk;
            ret = fread(&junk, sizeof(uint32_t), 1, file);
            assert(ret == 1);
            fprintf(stdout, "junk %08x: ", junk);
            fprintf(stdout, "\n");
        }
        int64_t value;
        ret = fread(&value, sizeof(int64_t), 1, file);
        assert(ret == 1);
        fprintf(stdout, "value %lld", value);
        fprintf(stdout, "\n");
    }
    else if (type == Double)
    {
        for (int i = 0; i < 4; i++)
        {
            uint32_t junk;
            ret = fread(&junk, sizeof(uint32_t), 1, file);
            assert(ret == 1);
            fprintf(stdout, "junk %08x: ", junk);
            fprintf(stdout, "\n");
        }
        double value;
        ret = fread(&value, sizeof(double), 1, file);
        assert(ret == 1);
        fprintf(stdout, "value %g", value);
        fprintf(stdout, "\n");
    }
    else if (type == String)
    {
        uint32_t len;
        for (int i = 0; i < 4; i++)
        {
            uint32_t junk;
            ret = fread(&junk, sizeof(uint32_t), 1, file);
            assert(ret == 1);
            fprintf(stdout, "junk %08x: ", junk);
            fprintf(stdout, "\n");
            if (i == 0)
                len = junk;
        }
        char buffer[512];
        ret = fread(buffer, sizeof(char), len, file);
        assert(ret == len);
        buffer[len] = '\0';
        fprintf(stdout, "value %s", buffer);
        fprintf(stdout, "\n");
    }
}

void process1(FILE* file)
{
    size_t ret;
    uint32_t tag;
    ret = fread(&tag, sizeof(uint32_t), 1, file);
    assert(ret == 1);
    uint32_t len;
    ret = fread(&len, sizeof(uint32_t), 1, file);
    assert(ret == 1);
    fprintf(stdout, "tag %08x: ", tag);
    fprintf(stdout, "len %08x: ", len);
    char buffer[512];
    ret = fread(buffer, sizeof(char), len, file);
    assert(ret == len);
    buffer[len] = '\0';
    fprintf(stdout, " %s: ", buffer);
    for (int i = 0; i < 2; i++)
    {
        uint32_t junk;
        ret = fread(&junk, sizeof(uint32_t), 1, file);
        assert(ret == 1);
        fprintf(stdout, "junk %08x: ", junk);
    }
    fprintf(stdout, "\n");
    entry entry;
    p1(file, entry.name);
    p1(file, entry.type);
    read_type(&entry, file);

    p1(file, entry.name);
    p1(file, entry.type);
    read_type(&entry, file);

    p1(file, entry.name);
    p1(file, entry.type);
    read_type(&entry, file);

    p1(file, entry.name);
    p1(file, entry.type);
    read_type(&entry, file);
}

void process3(FILE* file)
{
    size_t ret;
    uint32_t tag;
    uint32_t zero;
    ret = fread(&tag, sizeof(uint32_t), 1, file);
    assert(ret == 1);
    ret = fread(&zero, sizeof(uint32_t), 1, file);
    assert(ret == 1);
    //assert(zero == 0);
    fprintf(stdout, "tag %08x: ", tag);
    uint16_t num_elem;
    ret = fread(&num_elem, sizeof(uint16_t), 1, file);
    assert(ret == 1);
    fprintf(stdout, "(%u) ", num_elem);
    fprintf(stdout, "[");
    for (uint16_t i = 0; i < num_elem; i++)
    {
        if (i) fprintf(stdout, " ");
        uint16_t len;
        ret = fread(&len, sizeof(uint16_t), 1, file);
        assert(ret == 1);
        char buffer[512];
        assert(len < 512);
        ret = fread(buffer, sizeof(char), len, file);
        assert(ret == len);
        buffer[len] = '\0';
        fprintf(stdout, "%s", buffer);
    }
    fprintf(stdout, "]\n");
}

int main(int argc, char* argv[])
{
    const char* filename = argv[1];
    FILE* f = fopen(filename, "rb");
    int offset = 0x0D30;
    offset = 0xd0;
    fseek(f, offset, SEEK_SET);
    process1(f);
    //offset = 0xcc0;
    offset = 0xce3;
    fprintf(stdout, "\n");
    fprintf(stdout, "offset %08x\n", offset);
    fseek(f, offset, SEEK_SET);
    for (int i = 0; i < 20; i++)
        process3(f);
    fclose(f);
}

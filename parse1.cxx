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
    "float",
    "string",
    "bool"
};

enum EType
{
    Invalid = -1,
    Int64 = 0,
    Double = 1,
    Float = 2,
    String = 3,
    Bool = 4,
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
    const EType type = get_type(entry->type);
    assert(type != Invalid);

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
    else if (type == Float)
    {
        for (int i = 0; i < 4; i++)
        {
            uint32_t junk;
            ret = fread(&junk, sizeof(uint32_t), 1, file);
            assert(ret == 1);
            fprintf(stdout, "junk %08x: ", junk);
            fprintf(stdout, "\n");
        }
        float value;
        ret = fread(&value, sizeof(float), 1, file);
        assert(ret == 1);
        fprintf(stdout, "value %g", value);
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
    else if (type == Bool)
    {
        for (int i = 0; i < 4; i++)
        {
            uint32_t junk;
            ret = fread(&junk, sizeof(uint32_t), 1, file);
            assert(ret == 1);
            fprintf(stdout, "junk %08x: ", junk);
            fprintf(stdout, "\n");
        }
        int8_t value;
        ret = fread(&value, sizeof(char), 1, file);
        assert(ret == 1);
        fprintf(stdout, "value %d", value);
        fprintf(stdout, "\n");
    }
}

void process1(FILE* file)
{
    size_t ret;
    uint32_t tag;
    int64_t i64;
    float f[2];
    ret = fread(&i64, sizeof(int64_t), 1, file);
    assert(ret == 1);
    ret = fread(f, sizeof(float), 2, file);
    assert(ret == 2);
    fprintf(stdout, "j %lld %g %g\n", i64, f[0], f[1]);
    assert(i64 == 24);
    ret = fread(&tag, sizeof(uint32_t), 1, file);
    assert(ret == 1);
    assert(tag == 0);
    uint32_t len;
    ret = fread(&len, sizeof(uint32_t), 1, file);
    assert(ret == 1);
    assert(len == 8);
    fprintf(stdout, "tag %08x: ", tag);
    fprintf(stdout, "len %08x: ", len);
    char buffer[512];
    ret = fread(buffer, sizeof(char), len, file);
    assert(ret == len);
    buffer[len] = '\0';
    fprintf(stdout, " %s: ", buffer);
    fprintf(stdout, "\n");
    uint64_t slen;
    {
        ret = fread(&slen, sizeof(uint64_t), 1, file);
        assert(ret == 1);
        fprintf(stdout, "num bytes %08x: ", slen);
    }
    fprintf(stdout, "\n");
    entry entry;

    long start = ftell(file);
    while (true)
    {
        p1(file, entry.name);
        p1(file, entry.type);
        read_type(&entry, file);
        long num = ftell(file);
        if ((uint64_t)(num - start) == slen) break;
    }
}

void process2(FILE* file)
{
    uint16_t num;
    size_t ret = fread(&num, sizeof(uint16_t), 1, file);
    assert(ret == 1);
    fprintf(stdout, "num: %04d\n", num);
    for (uint16_t i = 0; i < num; i++)
    {
        uint16_t len;
        ret = fread(&len, sizeof(uint16_t), 1, file);
        assert(ret == 1);
        fprintf(stdout, "%08d ", len);
        char buffer[512];
        ret = fread(buffer, sizeof(char), len, file);
        assert(ret == len);
        buffer[len] = '\0';
        fprintf(stdout, "%s\n", buffer);
    }
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
    fflush(stdout);
}

int main(int argc, char* argv[])
{
    if (argc < 2) return 1;
    const char* filename = argv[1];
    FILE* f = fopen(filename, "rb");
    int offset = 0x0D30;
    offset = 0xd0;
    offset -= 8;
    offset -= 8;
    fseek(f, offset, SEEK_SET);
    process1(f);
    fprintf(stdout, "cur offset %08x\n", ftell(f));
    {
        process2(f);
        process3(f);
        process2(f);
    }
    fprintf(stdout, "cur offset %08x\n", ftell(f));
    //offset = 0xcc0;
    //offset = 0xce3;
    //fprintf(stdout, "\n");
    //fprintf(stdout, "offset %08x\n", offset);
    //fseek(f, offset, SEEK_SET);
    for (int i = 0; i < 21; i++)
        process3(f);
    fprintf(stdout, "cur offset %08x\n", ftell(f));
    //(void) fseek(f, 1L, SEEK_CUR);
    //process2(f);
    //fprintf(stdout, "cur offset %08x\n", ftell(f));
    fclose(f);
}

#include <fstream>
#include <string>
#include <iostream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>


namespace
{
    struct object
    {
        struct element
        {
            std::string key;
            int64_t val_int64;
            std::string val_str;
            int64_t zero64;
        };

        std::vector<element> array;
    };
}

BOOST_CLASS_VERSION(object, 0)

namespace
{
    template <class Archive>
    void serialize(Archive& ar, object::element& el, const unsigned int version)
    {
        ar & el.key
            & el.val_int64
            & el.val_str
            & el.zero64;
    }

    template <class Archive>
    void serialize(Archive& ar, object& data, const unsigned int version)
    {
        ar & data.array;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) return 1;

    const char* filename = argv[1];
    object ps{};

    std::ifstream ifile(filename, std::ios::binary);
    boost::archive::binary_iarchive iBinaryArchive(ifile);
    iBinaryArchive >> ps;

    boost::archive::text_oarchive oTextArchive(std::cout);
    oTextArchive << ps;

    std::ofstream ofile("output.raw", std::ios::binary);
    boost::archive::binary_oarchive oBinaryArchive(ofile);
    oBinaryArchive << ps;

    return 0;
}

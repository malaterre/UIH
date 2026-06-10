#include <fstream>
#include <string>
#include <iostream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include <boost/json/src.hpp>

namespace bj = boost::json;

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

    object read_dump(const char* filename)
    {
        object ps{};
        std::ifstream ifile(filename, std::ios::binary);
        boost::archive::binary_iarchive iBinaryArchive(ifile);
        iBinaryArchive >> ps;
        // originals are 14
        auto v = iBinaryArchive.get_library_version();
        std::cout << "lib version: " << v << std::endl;

        boost::archive::text_oarchive oTextArchive(std::cout);
        oTextArchive << ps;
        return ps;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) return 1;

    const char* filename = argv[1];
    const char temp[] = "temp.raw";
    try
    {
        object ps = read_dump(filename);

        std::cout << "obj1:" << bj::serialize(ps) << std::endl;
        {
            std::ofstream ofile(temp, std::ios::binary);
            boost::archive::binary_oarchive oBinaryArchive(ofile);
            oBinaryArchive << ps;
        } // flush

        read_dump(temp);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

#include <fstream>
#include <string>
#include <iostream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

struct element
{
    std::string key;
    int64_t val_int64;
    std::string val_str;
    int64_t zero64;
};

struct Array
{
    std::vector<element> map;
};

BOOST_CLASS_VERSION(Array, 0)
template <class Archive>
void serialize(Archive& ar, element& el, const unsigned int version)
{
    ar & el.key
       & el.val_int64
       & el.val_str
       & el.zero64;
}
 
template <class Archive>
void serialize(Archive& ar, Array& data, const unsigned int version)
{
    ar & data.map
    ;
}

int main()
{

    const char* filename = "test.raw";
    {
        Array ps;
        element el{};
        {
            // f1ffcc6a68862980351a2a4b974ca38a
            el.key = "Standard";
            el.val_int64 = 0;
            el.val_str = "";
            ps.map.push_back(el);
            el.key = "CoilCombine";
            el.val_int64 = -1;
            el.val_str = "";
            ps.map.push_back(el);
            el.key = "mDWIs";
            el.val_int64 = 1;
            el.val_str = "mDWIs";
            ps.map.push_back(el);
        }
        std::ofstream ofile(filename, std::ios::binary);
        boost::archive::binary_oarchive oBinaryArchive(ofile);
        oBinaryArchive << ps;
    }
    {
        std::ifstream ifile(filename, std::ios::binary);
        boost::archive::binary_iarchive iBinaryArchive(ifile);
        Array ps{};
        iBinaryArchive >> ps;
        
        boost::archive::text_oarchive oTextArchive(std::cout);
        oTextArchive << ps;
    }
    return 0;
}

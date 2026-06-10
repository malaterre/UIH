#include <fstream>
#include <map>
#include <string>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
//#include <boost/serialization/any.hpp>

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
    Array ps;
    element el{};
    {
        // 68322c6b97c1467fc0f14f85b71900b7
        el.key = "CoilCombine";
        el.val_int64 = -1;
        el.val_str = "";
        el.zero64 = 0;
        ps.map.push_back(el);
        el.key = "mpr";
        el.val_int64 = 1;
        el.val_str = "MPR";
        ps.map.push_back(el);
    }
    std::vector<std::string> v;
    v.emplace_back("Standard");
    v.emplace_back("CoilCombine");
    std::map<std::string, int> m;
    m.emplace("Standard", 4);
    m.emplace("CoilCombine", 1);
    const char* filename = "test.raw";
    std::ofstream ofile(filename, std::ios::binary);
    boost::archive::binary_oarchive oBinaryArchive(ofile);
    oBinaryArchive << ps;
    return 0;
}

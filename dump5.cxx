#include <fstream>
#include <map>
#include <variant>
#include <string>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/std_variant.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
//#include <boost/serialization/any.hpp>
#include <boost/any.hpp>

struct element
{
    std::string key;
    int64_t val_int64;
    std::string val_str;
    int64_t zero64;
};

struct Array
{
    //std::vector<el> map;
    std::vector<std::variant<std::string, int64_t>> map;
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
//    {
//        el.key = "Standard";
//        el.val = 0;
//        el.val2 = "";
//        ps.map.push_back(el);
//        el.key = "CoilCombine";
//        el.val = -1;
//        el.val2 = "";
//        ps.map.push_back(el);
//        el.key = "mDWIs";
//        el.val = 1;
//        el.val2 = "mDWIs";
//        ps.map.push_back(el);
//    }
    std::vector<std::variant<std::string, int64_t>> &v = ps.map;
    v.emplace_back("Standard");
    v.emplace_back("CoilCombine");
    const char* filename = "test.raw";
    std::ofstream ofile(filename, std::ios::binary);
    boost::archive::binary_oarchive oBinaryArchive(ofile);
    oBinaryArchive << ps;
    //oBinaryArchive << v;
    return 0;
}

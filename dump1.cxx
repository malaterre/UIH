#include <fstream>
#include <map>
#include <string>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

struct element
{
    std::string key;
    int64_t val_int64;
    int64_t val2;
    int64_t zero64;
};

struct Array
{
    std::vector<element> map;
//    int junk0;
//    int junk1;
//    int junk2;
//    int junk3;
//    int junk4;
//    int16_t junk5;
////    std::map<std::string, int> map;
//    std::string category; // "Standard" (optional)
//    int64_t param2; // 0
//    std::string operation; // "CoilCombine"

//
//    std::string inputSeries; // "ADC", "mDWIs"
//    bool enabled; // 1
//
//    std::string outputSeries; // "ADC", "mDWIs"
//
//    int64_t flags; // 0
};

BOOST_CLASS_VERSION(Array, 0)
template <class Archive>
void serialize(Archive& ar, element& el, const unsigned int version)
{
    ar & el.key
       & el.val_int64
       & el.val2
       & el.zero64;
}
 
template <class Archive>
void serialize(Archive& ar, Array& data, const unsigned int version)
{
    ar & data.map
//    & data.junk1
//    & data.junk2
//    & data.junk3
//    & data.junk4
//    & data.junk5
////    & data.junk
////    & data.map
//    & data.category
////        & data.operation
//        & data.param2
////        & data.inputSeries
////        & data.enabled
////        & data.outputSeries
////        & data.flags
    ;
}


//template<class Archive>
//void serialize(Archive& ar, std::vector<std::string>& v, const unsigned int /*version*/) {
//    ar & v;
//}
//template<class Archive>
//void serialize(Archive& ar, std::map<std::string, int>& v, const unsigned int /*version*/) {
//    ar & v;
//}



int main()
{
    Array ps;
    element el{};
    {
        // 75456bd7def8b0ba300dcdd42aba0933
        el.key = "CoilCombine";
        el.val_int64 = -1;
        el.val2 = 0;
        el.zero64 = 0;
        ps.map.push_back(el);
//        el.key = "ADC";
//        el.val = 0;
//        ps.map.push_back(el);
//        ps.junk0=  0;
//        ps.junk1=  0x200;
//        ps.junk2=  0x0;
//        ps.junk3=  0x0;
//        ps.junk4=  0x0;
//        ps.junk5=  0x0;
////        ps.junk.push_back(  4);
////        ps.junk.push_back(  5);
////        ps.map.emplace(  "CoilCombine", 4);
////        ps.map.emplace(  "ADC", 1);
//        ps.category=  "CoilCombine";
////        ps.operation=  "ADC";
//        ps.param2 = -1; // 0
//
//        ps.inputSeries = "ADC";
//        ps.enabled = true;
//
//        ps.outputSeries = "ADC";
//        ps.flags = 0;
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
    oBinaryArchive << ps; // sérialisation de d
    //oBinaryArchive << v; // sérialisation de d
    //oBinaryArchive << m; // sérialisation de d
    return 0;
}

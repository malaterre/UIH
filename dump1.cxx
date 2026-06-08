#include <fstream>
#include <string>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

struct ProcessingStep
{
    std::string category; // "Standard" (optional)
    std::string operation; // "CoilCombine"

    int64_t sourceIndex; // -1
    int64_t param1; // 0
    int64_t param2; // 0

    std::string inputSeries; // "ADC", "mDWIs"
    bool enabled; // 1

    std::string outputSeries; // "ADC", "mDWIs"

    int64_t flags; // 0
};


template <class Archive>
void serialize(Archive& ar, ProcessingStep& data, const unsigned int version)
{
    ar & data.category
        & data.operation
        & data.sourceIndex
        & data.param1
        & data.param2
        & data.inputSeries
        & data.enabled
        & data.outputSeries
        & data.flags;
}

BOOST_CLASS_VERSION(ProcessingStep, 2)

int main()
{
    ProcessingStep ps;
    {
        ps.category = "Standard";
        ps.operation = "CoilCombine";
        ps.sourceIndex = -1;
        ps.param1 = 0;
        ps.param2 = 0; // 0

        ps.inputSeries = "ADC";
        ps.enabled = true;

        ps.outputSeries = "ADC";
        ps.flags = 0;
    }
    const char* filename = "test.raw";
    std::ofstream ofile(filename, std::ios::binary);
    boost::archive::binary_oarchive oBinaryArchive(ofile);
    oBinaryArchive << ps; // sérialisation de d
    return 0;
}

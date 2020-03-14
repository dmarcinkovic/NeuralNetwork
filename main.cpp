
#include "imageLoader/Data.h"


int main()
{
    constexpr const int INPUT = 28 * 28;
    constexpr const int HIDDEN = 64;
    constexpr const int OUTPUT = 10;
    
    std::vector<Data> labeledData = Data::loadLabeledData("trainingData");
    Data::shuffleData(labeledData);

    for (auto const & data : labeledData)
    {
        std::cout << "Label: " << data.getLabel() << " Data: " << data.getData();
    }

    return 0;
}

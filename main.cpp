
#include "imageLoader/Data.h"


int main()
{
    std::vector<Data> labeledData = Data::loadLabeledData("trainingData");
    Data::shuffleData(labeledData);

    for (auto const & data : labeledData)
    {
        std::cout << "Label: " << data.getLabel() << " Data: " << data.getData();
    }

    return 0;
}


#include "imageLoader/Data.h"


int main()
{
    constexpr const int INPUT = 28 * 28;
    constexpr const int HIDDEN = 64;
    constexpr const int OUTPUT = 10;

    std::vector<Data> labeledData = Data::loadLabeledData("trainingData");
    Data::shuffleData(labeledData);

    Vector<OUTPUT> answer = Data::getAnswerData("7");
    std::cout << answer << "\n";


    return 0;
}

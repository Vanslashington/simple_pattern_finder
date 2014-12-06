#include <iostream>
#include <numeric>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

double stdDev(const vector<double>& numbers);
double getMean(const vector<double>& numbers);

int main()
{
    // User input string
    string userInput;
    
    // Collect sample data
    map<double, double> sampleIO;
    vector<double> sampleInput;
    cout << "Sample inputs and outputs ('d' when done):" << endl;
    getline(cin, userInput);
    while(userInput != "d")
    {
        stringstream userInputLine(userInput);
        double input, output;
        userInputLine >> input >> output;
        sampleIO[input] = output;
        sampleInput.push_back(input);
        getline(cin, userInput);
    }
    sort(sampleInput.begin(), sampleInput.end());

    // Calculate differences per unit
    vector<double> diffPerUnit(sampleInput.size()-1);
    for(int i = 1; i < sampleInput.size(); ++i)
        diffPerUnit[i-1] = (sampleIO[sampleInput[i]] - 
                            sampleIO[sampleInput[i-1]]) /
                           (sampleInput[i] - sampleInput[i-1]);

    // Calculate factor differences per unit
    vector<double> factorPerUnit(sampleInput.size()-1);
    for(int i = 1; i < sampleInput.size(); ++i)
        factorPerUnit[i-1] = pow((sampleIO[sampleInput[i]] / 
                              sampleIO[sampleInput[i-1]]),
                             (1.0 / (sampleInput[i] - sampleInput[i-1])));

    // Calculate means
    double diffMean = getMean(diffPerUnit);
    double factMean = getMean(factorPerUnit);

    cout << endl;
    cout << "diffmean: " << diffMean << endl;
    cout << "factmean: " << factMean << endl;

    // Calculate standard deviations
    double stdDevDiff = stdDev(diffPerUnit);
    double stdDevFact = stdDev(factorPerUnit);

    cout << "sddiff: " << stdDevDiff << endl;
    cout << "sdfact: " << stdDevFact << endl;
    cout << endl;

    // Get answer input
    cout << "Input for answer:" << endl;
    double ansInput;
    cin >> ansInput;

    // Find index with closest input value
    vector<double>::iterator i;
    double minDiff = sampleInput[0] - ansInput;
    int minIndex = sampleInput[0];
    for(i = sampleInput.begin(); i != sampleInput.end(); ++i)
    {
        double thisDiff = *i - ansInput;
        if(abs(thisDiff) < abs(minDiff))
        {
            minDiff = thisDiff;
            minIndex = *i;
        }
    }
    
    cout << endl;
    cout << "mindiff: " << minDiff << endl;
    cout << "minindex: " << minIndex << endl;
    cout << endl;

    // Use the one with the smaller deviation
    double answerOutput;
    if(stdDevDiff < stdDevFact)
        answerOutput = sampleIO[minIndex] - (diffMean * minDiff); 
    else
        answerOutput = sampleIO[minIndex] * (pow(factMean, -1 * minDiff));

    // Report prediction
    cout << "Prediction: ";
    cout << answerOutput << endl;

    return 0;
}

// Mean
double getMean(const vector<double>& numbers)
{
    // Sum and divide by size
    double sum = accumulate(numbers.begin(), numbers.end(), double(0.0));
    return sum / numbers.size();
}

// Standard deviation
double stdDev(const vector<double>& numbers)
{
    // Find mean
    double mean = getMean(numbers);
    
    // Find variance
    double diffSquareSum = 0;
    vector<double>::const_iterator i;
    for(i = numbers.begin(); i != numbers.end(); ++i)
        diffSquareSum += pow((*i - mean), 2.0);
    double variance = diffSquareSum / numbers.size();

    // Return standard deviation
    return sqrt(variance);
}

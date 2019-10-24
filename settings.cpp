#include "settings.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>

void Settings::loadFromFile(std::string filename)
{
    // open file
    std::ifstream file(filename.c_str(), std::ios::in);

    // check if file is open
    if (!file.is_open())
    {
        std::cout << "Could not open parameter file \"" << filename << "\"." << std::endl;
        return;
    }

    // loop over lines of file
    for (int lineNo = 0; ; lineNo++)
    {
        // read line
        std::string line;
        getline(file, line);

        // at the end of the file break for loop
        if (file.eof())
        {
            break;
        }

        // remove whitespace at beginning of line (if there is any)
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

        // if first character is a '#', skip line
        if (line.front() == '#')
        {
            continue;
        }

        // truncate string at '#'
        int commentSignIndex = line.find('#');
        line = std::string(line.begin(), commentSignIndex);

        // if line does not contain a single '=' sign, skip line
        if (std::count(line.begin(), line.end(), '=') != 1)
        {
            continue;
        }

        // split line into parameterName and parameterValue
        std::string parameterName;
        std::string parameterValue;

        int equalSignIndex = line.find('=');
        parameterName = line.substr(line.begin(), equalSignIndex);
        parameterValue = line.substr(equalSignIndex, line.end());

        // parse all the parameters
        if (parameterName == "nCells")
        {
            nCells = parseTuple<int>(parameterValue);
        }
        else if (parameterName == "physicalSize")
        {
            physicalSize = parseTuple<double>(parameterValue);
        }
        else if (parameterName == "re")
        {
            re = atof(parameterValue);
        }
        else if (parameterName == "endTime")
        {
            endTime = atof(parameterValue);
        }
        else if (parameterName == "tau")
        {
            tau = atof(parameterValue);
        }
        else if (parameterName == "maximumDt")
        {
            maximumDt = atof(parameterValue);
        }
        else if (parameterName == "g")
        {
            g = parseTuple<double>(parameterValue);
        }
        else if (parameterName == "discretizationType")
        {
            discretizationType = parameterValue;
        }
        else if (parameterName == "alphaDC")
        {
            alphaDC = atof(parameterValue);
        }
        else if (parameterName == "dirichletBcBottom")
        {
            dirichletBcBottom = parseTuple<double>(parameterValue);
        }
        else if (parameterName == "dirichletBcTop")
        {
            dirichletBcTop = parseTuple<double>(parameterValue);
        }
        else if (parameterName == "dirichletBcLeft")
        {
            dirichletBcLeft = parseTuple<double>(parameterValue);
        }
        else if (parameterName == "dirichletBcRight")
        {
            dirichletBcRight = parseTuple<double>(parameterValue);
        }
        else if (parameterName == "pressureSolver")
        {
            pressureSolver = parameterValue;
        }
        else if (parameterName == "omegaSOR")
        {
            omegaSOR = atof(parameterValue);
        }
        else if (parameterName == "epsilonTol")
        {
            epsilonTol = atof(parameterValue);
        }
        else if (parameterName == "maxPressureIterations")
        {
            maxPressureIterations = atoi(parameterValue);
        }
    }
}

template<typename T>
std::array<T,2> Settings::parseTuple(std::string parameterValue)
{
    int kommaSignIndex = parameterValue.find(',');
    firstValue = parameterValue.substr(parameterValue.begin(), kommaSignIndex);
    secondValue = parameterValue.substr(kommaSignIndex, parameterValue.end());
    std::array<T,2> tuple{(T) atof(firstValue), (T) atof(secondValue)};
    return tuple;
}

void Settings::printSettings()
{
  std::cout << "Settings: " << std::endl
    << "  physicalSize: " << physicalSize[0] << " x " << physicalSize[1] << ", nCells: " << nCells[0] << " x " << nCells[1] << std::endl
    << "  endTime: " << endTime << " s, re: " << re << ", g: (" << g[0] << "," << g[1] << "), tau: " << tau << ", maximum dt: " << maximumDt << std::endl
    << "  dirichletBC: bottom: (" << dirichletBcBottom[0] << "," << dirichletBcBottom[1]  << ")"
    << ", top: ("  << dirichletBcTop[0] << "," << dirichletBcTop[1]  << ")"
    << ", left: ("  << dirichletBcLeft[0] << "," << dirichletBcLeft[1] << ")"
    << ", right: ("  << dirichletBcRight[0] << "," << dirichletBcRight[1] << ")" << std::endl
    << "  discretizationType: " << discretizationType << ", alphaDC: " << alphaDC << std::endl
    << "  pressureSolver: " << pressureSolver << ", omegaSOR: " << omegaSOR << ", epsilonTol: " << epsilonTol << ", maximumPressureIterations: " << maximumPressureIterations << std::endl;
}

void main(int argc, char *argv[]) 
{
    Settings settings;
    settings.loadFromFile("parameters.txt");
}
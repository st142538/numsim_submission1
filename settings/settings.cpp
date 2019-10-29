#include "settings.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>

// parses the parameterValue into a tuple from format a,b to the specified type T
// this type has to be numerical, e.g. double!
template<typename T>
std::array<T,2> parseTuple(std::string parameterValue)
{
    int kommaSignIndex = parameterValue.find(',');
    std::string firstValue = parameterValue.substr(0, kommaSignIndex);
    std::string secondValue = parameterValue.substr(kommaSignIndex + 1, parameterValue.size());
    std::array<T,2> tuple{(T) atof(firstValue.c_str()), (T) atof(secondValue.c_str())};
    return tuple;
}

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
        line = line.substr(0, commentSignIndex);

        // if line does not contain a single '=' sign, skip line
        if (std::count(line.begin(), line.end(), '=') != 1)
        {
            continue;
        }

        // split line into parameterName and parameterValue
        std::string parameterName;
        std::string parameterValue;

        int equalSignIndex = line.find('=');
        parameterName = line.substr(0, equalSignIndex);
        parameterValue = line.substr(equalSignIndex + 1, line.size());

        //std::cout << parameterName << " " << parameterValue << std::endl;
        //continue;

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
            re = atof(parameterValue.c_str());
        }
        else if (parameterName == "endTime")
        {
            endTime = atof(parameterValue.c_str());
        }
        else if (parameterName == "tau")
        {
            tau = atof(parameterValue.c_str());
        }
        else if (parameterName == "maximumDt")
        {
            maximumDt = atof(parameterValue.c_str());
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
            alphaDC = atof(parameterValue.c_str());
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
            omegaSOR = atof(parameterValue.c_str());
        }
        else if (parameterName == "epsilonTol")
        {
            epsilonTol = atof(parameterValue.c_str());
        }
        else if (parameterName == "maxPressureIterations")
        {
            maxPressureIterations = atoi(parameterValue.c_str());
        }
    }
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
    << "  pressureSolver: " << pressureSolver << ", omegaSOR: " << omegaSOR << ", epsilonTol: " << epsilonTol << ", maxPressureIterations: " << maxPressureIterations << std::endl;
}

#include "settings.h"

std::string trim(const std::string &str, const std::string &whitespace = " \t")
{
    // get begin of string
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
    {
        return ""; // no content
    }

    // get end of string
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

void split(const std::string &str, std::vector<std::string> &cont, char delim)
{
    std::size_t current, previous = 0;
    current = str.find(delim);

    while (current != std::string::npos)
    {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find(delim, previous);
    }

    cont.push_back(str.substr(previous, current - previous));
}

void Settings::loadFromFile(std::string filename)
{
    std::ifstream file(filename.c_str(), std::ios::in);

    // check if file is open now
    if (!file.is_open())
    {
        std::cout << "Can not open file" << filename << std::endl;
        return;
    }

    // iterate until file is entierly read
    // TODO check if last line is read
    while (!file.eof())
    {
        std::string line;
        getline(file, line);

        // removes whitespaces at the beginning and at the end
        line = trim(line);

        // check if line is only comment
        if (line[0] == '#')
        {
            continue;
        }

        // check if line contains a equal sign
        if (line.find_first_of('=') == std::string::npos)
        {
            continue;
        }

        // split line into left and right side
        std::vector<std::string> values;
        split(line, values, '=');

        // remove whitespaces from right side
        std::string parameterName = trim(values[0]);
        split(line, values, '=');

        // remove whitespaces from right side
        std::string parameterValueString = trim(values[1]);

        if (line.find('#'))
        {
            std::vector<std::string> value_clean;

            // remove comment from right side
            split(values[1], value_clean, '#');

            // remove whitespaces from right side
            parameterValueString = trim(value_clean[0]);
        }

        // parse right hand side
        const char *parameterValue = parameterValueString.c_str();
        if (parameterName == "physicalSizeX")
        {
            this->physicalSize[0] = atof(parameterValue);
        }
        else if ( parameterName == "physicalSizeY")
        {
            this->physicalSize[1] = atof(parameterValue);
        }
        else if ( parameterName == "endTime")
        {
            this->endTime = atof(parameterValue);
        }
        else if ( parameterName == "re")
        {
            this->re = atof(parameterValue);
        }
        else if ( parameterName == "gX")
        {
            this->g[0] = atof(parameterValue);
        }
        else if ( parameterName == "gY")
        {
            this->g[1] = atof(parameterValue);
        }
        else if ( parameterName == "dirichletBottomX")
        {
            this->dirichletBcBottom[0] = atof(parameterValue);
        }
        else if ( parameterName == "dirichletBottomY")
        {
            this->dirichletBcBottom[1] = atof(parameterValue);
        }
        else if ( parameterName == "dirichletTopX")
        {
            this->dirichletBcTop[0] = atof(parameterValue);
        }
        else if ( parameterName == "dirichletTopY")
        {
            this->dirichletBcTop[1] = atof(parameterValue);
        }
        else if ( parameterName == "dirichletLeftX")
        {
            this->dirichletBcLeft[0] = atof(parameterValue);
        }
        else if ( parameterName == "dirichletLeftY")
        {
            this->dirichletBcLeft[1] = atof(parameterValue);
        }
        else if ( parameterName == "dirichletRightX")
        {
            this->dirichletBcRight[0] = atof(parameterValue);
        }
        else if ( parameterName == "dirichletRightY")
        {
            this->dirichletBcRight[1] = atof(parameterValue);
        }
        else if ( parameterName == "nCellsX")
        {
            this->nCells[0] = (int) atof(parameterValue);
        }
        else if ( parameterName == "nCellsY")
        {
            this->nCells[1] = (int) atof(parameterValue);
        }
        else if ( parameterName == "useDonorCell")
        {
            this->useDonorCell = std::strcmp(parameterValue, "true") == 0;
        }
        else if ( parameterName == "alpha")
        {
            this->alpha = atof(parameterValue);
        }
        else if ( parameterName == "tau")
        {
            this->tau = atof(parameterValue);
        }
        else if ( parameterName == "maximumDt")
        {
            this->maximumDt = atof(parameterValue);
        }
        else if ( parameterName == "pressureSolver")
        {
            this->pressureSolver = parameterValue;
        }
        else if ( parameterName == "omega")
        {
            this->omega = atof(parameterValue);
        }
        else if ( parameterName == "epsilon")
        {
            this->epsilon = atof(parameterValue);
        }
        else if ( parameterName == "maximumNumberOfIterations")
        {
            this->maximumNumberOfIterations = (int) atof(parameterValue);
        }
    }
};

void Settings::printSettings() {
    std::cout << "Settings: " << std::endl
        << "  physicalSize: " << physicalSize[0] << " x " << physicalSize[1] << ", nCells: " << nCells[0] << " x "
        << nCells[1] << std::endl
        << "  endTime: " << endTime << " s, re: " << re << ", g: (" << g[0] << "," << g[1] << "), tau: " << tau
        << ", maximum dt: " << maximumDt << std::endl
        << "  dirichletBC: bottom: (" << dirichletBcBottom[0] << "," << dirichletBcBottom[1] << ")"
        << ", top: (" << dirichletBcTop[0] << "," << dirichletBcTop[1] << ")"
        << ", left: (" << dirichletBcLeft[0] << "," << dirichletBcLeft[1] << ")"
        << ", right: (" << dirichletBcRight[0] << "," << dirichletBcRight[1] << ")" << std::endl
        << "  useDonorCell: " << std::boolalpha << useDonorCell << ", alpha: " << alpha << std::endl
        << "  pressureSolver: " << pressureSolver << ", omega: " << omega << ", epsilon: " << epsilon
        << ", maximumNumberOfIterations: " << maximumNumberOfIterations << std::endl;
}

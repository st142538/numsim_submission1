#include "outputWriterText.h"

void OutputWriterText::writeFile(double currentTime)
{
	// Assemble the filename
	std::stringstream fileName;
	fileName << "out/output_" << std::setw(4) << std::setfill('0') << fileNo_ << ".txt";

	// increment file no.
	fileNo_++;

	// open file
	std::ofstream file(fileName.str().c_str());

	if (!file.is_open())
	{
		std::cout << "Could not write to file \"" << fileName.str() << "\".";
		return;
	}

	// write time
	file << "t: " << currentTime << std::endl;
	// get needed parametres
	// nCells without boundaries
	std::array<int,2> nCells = {discretization_->p.sizeX() - 2, discretization_->p.sizeY() - 2};
	const double dx = discretization_->dx();
	const double dy = discretization_->dy();
	// write mesh width withput boundaries
	file << "nCells: " << nCells[0] << "x" << nCells[1] 
	<< ", dx: " << dx << ", dy: " << dy << std::endl << std::endl;

	const int fieldWidth = 9;   // number of characters to use for a single value

	// write u
	// ---------
	// write header lines
	file << "u (" << discretization_->u.sizeX() << "x" << discretization_->u.sizeY() << "): " << std::endl 
	<< std::string(fieldWidth, ' ') << "|";
	for (int i = discretization_->uIBegin(); i < discretization_->uIEnd(); i++)
	{
		file << std::setw(fieldWidth) << i;
	}
	file << std::endl << std::string(fieldWidth*(discretization_->u.sizeX+2)+1, '-') << std::endl;

	// write u values
	for (int j = discretization_->uJEnd()-1; j >= discretization_->uJBegin(); j--)
	{
		file << std::setw(fieldWidth) << j << "|";
		for (int i = discretization_->uIBegin(); i < discretization_->uIEnd(); i++)
		{
			file << std::setw(fieldWidth) << std::setprecision(fieldWidth-6) << discretization_->u(i,j);
		}
		file << std::endl;
	}
	file << std::endl;

  // write v
  // ---------
  // write header lines
	file << "v (" << discretization_->v.sizeX() << "x" << discretization_->v.sizeY() << "): " << std::endl 
		<< std::string(fieldWidth, ' ') << "|";
	for (int i = discretization_->vIBegin(); i < discretization_->vIEnd(); i++)
	{
		file << std::setw(fieldWidth) << i;
	}
	file << std::endl << std::string(fieldWidth*(discretization_->v.sizeX()+2)+1, '-') << std::endl;

	// write v values
	for (int j = discretization_->vJEnd()-1; j >= discretization_->vJBegin(); j--)
	{
		file << std::setw(fieldWidth) << j << "|";
		for (int i = discretization_->vIBegin(); i < discretization_->vIEnd(); i++)
		{
			file << std::setw(fieldWidth) << std::setprecision(fieldWidth-6) << discretization_->v(i,j);
		}
		file << std::endl;
	}
	file << std::endl;

	// write p
	// ---------
	// write header lines
	file << "p (" << discretization_->p.sizeX() << "x" << discretization_->p.sizeY() << "): " << std::endl 
		<< std::string(fieldWidth, ' ') << "|";
	for (int i = discretization_->pIBegin(); i < discretization_->pIEnd(); i++)
	{
		file << std::setw(fieldWidth) << i;
	}
	file << std::endl << std::string(fieldWidth*(discretization_->p.sizeX()+2)+1, '-') << std::endl;

	// write p values
	for (int j = discretization_->pJEnd()-1; j >= discretization_->pJBegin(); j--)
	{
		file << std::setw(fieldWidth) << j << "|";
		for (int i = discretization_->pIBegin(); i < discretization_->pIEnd(); i++)
		{
			file << std::setw(fieldWidth) << std::setprecision(fieldWidth-6) << discretization_->p(i,j);
		}
		file << std::endl;
	}
	file << std::endl;

	// write f
	// ---------
	// write header lines
	file << "F (" << discretization_->u.sizeX() << "x" << discretization_->u.sizeY() << "): " << std::endl 
		<< std::string(fieldWidth, ' ') << "|";
	for (int i = discretization_->uIBegin(); i < discretization_->uIEnd(); i++)
	{
		file << std::setw(fieldWidth) << i;
	}
	file << std::endl << std::string(fieldWidth*(discretization_->u.sizeX()+2)+1, '-') << std::endl;

	// write f values
	for (int j = discretization_->uJEnd()-1; j >= discretization_->uJBegin(); j--)
	{
		file << std::setw(fieldWidth) << j << "|";
		for (int i = discretization_->uIBegin(); i < discretization_->uIEnd(); i++)
		{
			file << std::setw(fieldWidth) << std::setprecision(fieldWidth-6) << discretization_->f(i,j);
		}
		file << std::endl;
	}
	file << std::endl;

  // write g
  // ---------
  // write header lines
	file << "G (" << discretization_->v.sizeX() << "x" << discretization_->v.sizeY() << "): " << std::endl 
		<< std::string(fieldWidth, ' ') << "|";
	for (int i = discretization_->vIBegin(); i < discretization_->vIEnd(); i++)
	{
		file << std::setw(fieldWidth) << i;
	}
	file << std::endl << std::string(fieldWidth*(discretization_->v.sizeX()+2)+1, '-') << std::endl;

	// write g values
	for (int j = discretization_->vJEnd()-1; j >= discretization_->vJBegin(); j--)
	{
		file << std::setw(fieldWidth) << j << "|";
		for (int i = discretization_->vIBegin(); i < discretization_->vIEnd(); i++)
		{
			file << std::setw(fieldWidth) << std::setprecision(fieldWidth-6) << discretization_->g(i,j);
		}
		file << std::endl;
	}
	file << std::endl;

	// write rhs
	// ---------
	// write header lines
	file << "rhs (" << discretization_->p.sizeX() << "x" << discretization_->p.sizeY() << "): " << std::endl 
		<< std::string(fieldWidth, ' ') << "|";
	for (int i = discretization_->pIBegin(); i < discretization_->pIEnd(); i++)
	{
		file << std::setw(fieldWidth) << i;
	}
	file << std::endl << std::string(fieldWidth*(discretization_->p.sizeX()+2)+1, '-') << std::endl;

	// write rhs values
	for (int j = discretization_->pJEnd()-1; j >= discretization_->pJBegin(); j--)
	{
		file << std::setw(fieldWidth) << j << "|";
		for (int i = discretization_->pIBegin(); i < discretization_->pIEnd(); i++)
		{
			file << std::setw(fieldWidth) << std::setprecision(fieldWidth-6) << discretization_->rhs(i,j);
		}
		file << std::endl;
	}
	file << std::endl;

}

void OutputWriterText::writePressureFile()
{
	// counter for files, counter value is part of the file name
	static int pressurefileNo = 0;

	// Assemble the filename
	std::stringstream fileName;
	fileName << "out/pressure_" << std::setw(4) << std::setfill('0') << pressurefileNo++ << ".txt";

	// open file
	std::ofstream file(fileName.str().c_str());

	if (!file.is_open())
	{
		std::cout << "Could not write to file \"" << fileName.str() << "\".";
	return;
	}

	std::array<int,2> nCells = {discretization_->p.sizeX() - 2, discretization_->p.sizeY() - 2};

	// write mesh width
	file << "nCells: " << nCells[0] << "x" << nCells[1] 
		<< ", dx: " << discretization_->dx() << ", dy: " << discretization_->dy() << std::endl << std::endl;

	const int fieldWidth = 9;   // number of characters to use for a single value

	// write p
	// ---------
	// write header lines
	file << "p (" << discretization_->p.sizeX() << "x" << discretization_->p.sizeY() << "): " << std::endl 
		<< std::string(fieldWidth, ' ') << "|";
	for (int i = discretization_->pIBegin(); i < discretization_->pIEnd(); i++)
	{
		file << std::setw(fieldWidth) << i;
	}
	file << std::endl << std::string(fieldWidth*(discretization_->p.sizeX()+2)+1, '-') << std::endl;

	// write p values
	for (int j = discretization_->pJEnd()-1; j >= discretization_->pJBegin(); j--)
	{
		file << std::setw(fieldWidth) << j << "|";
		for (int i = discretization_->pIBegin(); i < discretization_->pIEnd(); i++)
		{
			file << std::setw(fieldWidth) << std::setprecision(fieldWidth-6) << discretization_->p(i,j);
		}
		file << std::endl;
	}
	file << std::endl;
}

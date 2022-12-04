#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Solver.h"


bool getData(const std::string& inputPath, std::vector<Point>& points)
{
	std::ifstream out;
	out.open(inputPath);

	if (out.is_open())
	{
		std::string strPoints;
		if (!getline(out, strPoints))
		{
			std::cout << "Not enough lines in input" << std::endl;
			return false;
		}

		try {

			bool isSecond = false;
			int x;
			std::string num;
			
			std::size_t pos;
			do
			{
				std::stringstream ssl(strPoints);
				while (getline(ssl, num, ' '))
				{
					int tmp = std::stoi(num, &pos);
					if (pos != num.size())
					{
						std::cout << ("Extra chars in int def" + num).data() << std::endl;
						return false;
					}
					if (isSecond)
					{
						points.push_back({ x, tmp });
						isSecond = false;
					}
					else
					{
						x = tmp;
						isSecond = true;
					}
				}
				if (isSecond == true)
				{
					std::cout << "Odd number of coordinates" << std::endl;
					return false;
				}
			} while (getline(out, strPoints));
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << ("Can't open" + inputPath).data() << std::endl;
		return false;
	}
	out.close();
	return true;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 0;

	std::vector<Point> points;
	if (!getData(argv[1], points))
		return 0;
	else 
	{
		std::vector<int> answer = Solver::QuickHull(points);
		for (int j = 0; j < answer.size(); j++)
			std::cout << answer[j] << " ";
		std::cout <<std::endl;		
	}
	return 0;
}


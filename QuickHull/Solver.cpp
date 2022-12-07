#include "Solver.h"

void Solver::FindLeftRight(const std::vector<Point>& points, int& i_left, int& i_right)
{
	Point max = points[0], min = points[0];
	i_right = 0;
	i_left = 0;
	for (int i = 1; i < points.size(); i++)
	{
		if (points[i].x > max.x || points[i].x == max.x && points[i].y > max.y)
		{
			max = points[i];
			i_right = i;
		}

		if (points[i].x < min.x || points[i].x == min.x && points[i].y < min.y)
		{
			min = points[i];
			i_left = i;
		}			
	}
}


long long Solver::Det(Point left, Point right, Point point)
{
	return point.x*(left.y - right.y) - point.y*(left.x - right.x) + (left.x*right.y - right.x*left.y);
}


std::vector<int> Solver::GetLeftPoints(const std::vector<Point>& points, const std::vector<int>& S,
										int i_left, int i_right)
{
	std::vector<int> SLeft;
	for (int i = 0; i < S.size(); i++)
	{
		if (S[i] != i_left && S[i] != i_right)
			if (Det(points[i_left], points[i_right], points[S[i]]) > 0)
				SLeft.push_back(S[i]);
	}
	return SLeft;
}

void Solver::QuickHullForHalf(const std::vector<Point>& points, const std::vector<int>& S, std::vector<int>& answer,
											int i_left, int i_right)
{
	if (S.size() == 0)
		return;

	long long max_area = Det(points[i_left], points[i_right], points[S[0]]), area;
	int i_max = S[0];
	for (int i = 1; i < S.size(); i++)
	{
		area = Det(points[i_left], points[i_right], points[S[i]]);
		if (area > max_area || area == max_area && points[S[i]].x < points[i_max].x)
		{
			max_area = area;
			i_max = S[i];
		}
	}
	
	QuickHullForHalf(points, GetLeftPoints(points, S, i_max, i_right), answer, i_max, i_right);
	answer.push_back(i_max);
	QuickHullForHalf(points, GetLeftPoints(points, S, i_left, i_max), answer, i_left, i_max);
	
}


std::vector<int> Solver::QuickHull(std::vector<Point> points)
{	
	int i_left, i_right;
	std::vector<int> answer;

	FindLeftRight(points, i_left, i_right);
	if (i_right == i_left)
	{
		answer.push_back(0);
		return answer;
	}

	std::vector<int> S1, S2; 
	for (int i = 0; i < points.size(); i++)
	{
		if (i != i_left && i != i_right)
			if (Det(points[i_left], points[i_right], points[i]) > 0)
				S1.push_back(i);
			else if (Det(points[i_left], points[i_right], points[i]) < 0)
				S2.push_back(i);
	}

	answer.push_back(i_left);
	QuickHullForHalf(points, S2, answer, i_right, i_left);
	answer.push_back(i_right);
	QuickHullForHalf(points, S1, answer, i_left, i_right);

	return answer;
}

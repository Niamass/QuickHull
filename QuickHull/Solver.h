#pragma once
#include <vector>

struct Point 
{
	long long x, y;
};


class Solver 
{
private:
	static void FindLeftRight(const std::vector<Point>&, int&, int&);
	static std::vector<int> GetLeftPoints(const std::vector<Point>&, const std::vector<int>&, int, int);
	static void QuickHullForHalf(const std::vector<Point>&, const std::vector<int>&, std::vector<int>&, int, int);
	static long long Det(Point, Point, Point);
public:
	static std::vector<int> QuickHull(std::vector<Point>);
};
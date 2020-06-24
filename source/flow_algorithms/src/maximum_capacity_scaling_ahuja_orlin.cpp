#include <maximum_capacity_scaling_ahuja_orlin.hpp>
#include <algorithm>
#include <iostream>
#include <stack>

int findMaxCapacity(std::vector<std::vector<int>> matrix)
{
	auto maxCapacity = 0;
	for (auto adjancyList: matrix)
	{
		for (auto capacity: adjancyList)
		{
			if (capacity > maxCapacity)
			{
				maxCapacity = capacity;
			}
		}
	}
	return maxCapacity;
}

int computeReferenceResidue(int maxCapacity)
{
	auto refResidue = 1;
	while (maxCapacity != 1)
	{
		refResidue *= 2;
		maxCapacity /= 2;
	}
	return refResidue;
}

bool dfs(const std::vector<std::vector<int>>& matrix, std::vector<bool>& visited, int refResidue, int start, int stock, std::vector<int>& outPath)
{
	visited[start] = true;
	for (auto y = 1; y < matrix[start].size(); ++y)
	{
		auto capacity = matrix[start][y];
		if (!visited[y] && capacity >= refResidue)
		{
			outPath.push_back(y);
			if (y == stock) return true;
			if (dfs(matrix, visited, refResidue, y, stock, outPath)) return true;
			outPath.pop_back();
		}
	}
	return false;
}

std::vector<int> findPathToStock(const std::vector<std::vector<int>>& matrix, int refResidue, int start, int stock)
{
	std::vector<bool> visited(matrix.size(), false);
	std::vector<int> outPath(1, start);
	bool pathFound = dfs(matrix, visited, refResidue, start, stock, outPath);
	return pathFound ? outPath : std::vector<int>();
}

int computeMinCapacity(const std::vector<std::vector<int>>& matrix, const std::vector<int>& path)
{
	auto minCapacity = matrix[path[0]][path[1]];
	for (int i=0; i<path.size()-1; ++i)
	{
		int capacity = matrix[path[i]][path[i+1]];
		if (capacity < minCapacity)
		{
			minCapacity = capacity;
		}
	}
	return minCapacity;
}

void increaseFlow(std::vector<std::vector<int>>& matrix, const std::vector<int>& path, int minCapacity)
{
	std::cout << "se face marire de flux cu r(D) = " << minCapacity << " pe: ";
	for (auto node : path) 
	{
		std::cout << node << ' ';
	}
	std::cout << '\n';

	for (int i = 0; i < path.size() - 1; ++i)
	{
		matrix[path[i]][path[i + 1]] -= minCapacity;
		matrix[path[i + 1]][path[i]] += minCapacity;
	}
}

std::vector<std::vector<int>> computeMaxFlow(std::vector<std::vector<int>> matrix, int start, int stock)
{
	auto maxCapacity = findMaxCapacity(matrix);
	auto refResidue = computeReferenceResidue(maxCapacity);
	while (refResidue >= 1)
	{
		auto path = findPathToStock(matrix, refResidue, start, stock);
		if (!path.empty())
		{
			auto minCapacity = computeMinCapacity(matrix, path);
			increaseFlow(matrix, path, minCapacity);
		}
		else
		{
			refResidue /= 2;
		}
	}
	return matrix;
}

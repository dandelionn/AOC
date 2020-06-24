#include <shortest_path_ahuja_orlin.hpp>
#include <iostream>

constexpr int INF = 999999;

void computeDistances(const std::vector<std::vector<int>>& matrix, int start, int stock, std::vector<int>& out)
{
	auto distance = out[start] + 1;
	for (auto y = 1; y < matrix[start].size(); ++y)
	{
		auto capacity = matrix[start][y];
		if (capacity > 0 && distance < out[y])
		{
			out[y] = distance;
			if (y != stock)
			{
				computeDistances(matrix, y, stock, out);
			}
		}
	}
}

std::vector<int> computeDistances(const std::vector<std::vector<int>>& matrix, int start, int stock)
{
	std::vector<int> distances(matrix.size(), INF);
	distances[start] = 0;
	computeDistances(matrix, start, stock, distances);
	std::reverse(distances.begin() + 1, distances.end());
	return distances;
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

std::vector<int> findPath(const std::vector<int>& prev, int start, int stock)
{
	std::vector<int> path;
	auto currentNode = stock;
	path.push_back(stock);
	while (prev[currentNode] != 0)
	{
		currentNode = prev[currentNode];
		path.push_back(currentNode);
	}
	std::reverse(path.begin(), path.end());
	return path;
}

int computeMinCapacity(const std::vector<std::vector<int>>& matrix, const std::vector<int>& path)
{
	auto minCapacity = matrix[path[0]][path[1]];
	for (int i = 0; i<path.size() - 1; ++i)
	{
		int capacity = matrix[path[i]][path[i + 1]];
		if (capacity < minCapacity)
		{
			minCapacity = capacity;
		}
	}
	return minCapacity;
}

int getNextNode(int currentNode, const std::vector<int>& adjacentList, const std::vector<int>& distances)
{
	int node = currentNode;
	for (auto y = 1; y < adjacentList.size(); ++y)
	{
		auto capacity = adjacentList[y];
		if (capacity > 0 && distances[node] > distances[y])
		{
			node = y;
		}
	}

	return node;
}

int findSmallestAdjacentLabel(const std::vector<int>& adjacentList, const std::vector<int>& distances)
{
	int minLabel = INF;
	for (auto y = 1; y < adjacentList.size(); ++y)
	{
		auto capacity = adjacentList[y];
		if (capacity > 0 && distances[y] < minLabel)
		{
			minLabel = distances[y];
		}
	}

	return minLabel;
}

const std::vector<std::vector<int>> computeMaxFlow(std::vector<std::vector<int>> matrix, int start, int stock)
{
	std::vector<int> prev(matrix.size(), 0);
	auto distances = computeDistances(matrix, start, stock);
	auto currentNode = start;
	while (distances[start] < (matrix.size()-1))
	{
		auto nextNode = getNextNode(currentNode, matrix[currentNode], distances);
		if (nextNode != currentNode) 
		{
			//advance
			prev[nextNode] = currentNode;
			currentNode = nextNode;
			
			if (currentNode == stock)
			{
				auto path = findPath(prev, start, stock);
				auto minCapacity = computeMinCapacity(matrix, path);
				increaseFlow(matrix, path, minCapacity);
				currentNode = start;
			}
		}
		else
		{
			//return
			auto minLabel = findSmallestAdjacentLabel(matrix[currentNode], distances);
			distances[currentNode] = minLabel + 1;
			if (currentNode != start)
			{
				currentNode = prev[currentNode];
			}
		}
	}

	return matrix;
}
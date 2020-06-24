#include <preflow_with_biggest_label.hpp>
#include <vector>
#include <queue>
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

std::vector<int> initialise(std::vector<std::vector<int>>& matrix, std::vector<int>& distances, int start, int stock, std::vector<int>& e)
{
	std::vector<int> nodesToBeEnqueued;

	for (auto y = 1; y < matrix[start].size(); ++y)
	{
		auto capacity = matrix[start][y];
		if (capacity > 0)
		{
			matrix[y][start] += matrix[start][y];
			e[start] -= matrix[start][y];
			e[y] = matrix[start][y];
			matrix[start][y] = 0;
			if (e[y] > 0 && y != stock)
			{
				nodesToBeEnqueued.push_back(y);
			}
		}
	}
	distances[start] = matrix[start].size()-1; 

	return nodesToBeEnqueued;
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

void advance(std::vector<std::vector<int>>& matrix, int currentNode, int nextNode, std::vector<int>& e)
{
	auto flowUnits = std::min(matrix[currentNode][nextNode], e[currentNode]);
	e[nextNode] += flowUnits;
	e[currentNode] -= flowUnits;
	matrix[currentNode][nextNode] -= flowUnits;
}

void goback(std::vector<std::vector<int>>& matrix, int currentNode, std::vector<int>& distances)
{
	auto minLabel = findSmallestAdjacentLabel(matrix[currentNode], distances);
	distances[currentNode] = minLabel + 1;
}

std::vector<std::vector<int>> computeMaxFlow(std::vector<std::vector<int>> matrix, int start, int stock)
{
	std::vector<int> excess(matrix.size(), 0);
	auto distances = computeDistances(matrix, start, stock);
	auto compare = [distances](int x, int y) { return distances[x] < distances[y]; };
	auto nodesToBeEnqueued = initialise(matrix, distances, start, stock, excess);
	std::priority_queue<int, std::vector<int>, decltype(compare) > q(compare);
	std::vector<bool> inQueue(matrix.size(), false);

	for (auto node : nodesToBeEnqueued)
	{
		q.push(node);
		inQueue[node] = true;
	}
	
	while (!q.empty())
	{
		auto currentNode = q.top();
		q.pop();
		inQueue[currentNode] = false;
		bool exit = false;
		do
		{
			auto nextNode = getNextNode(currentNode, matrix[currentNode], distances);
			if (nextNode != currentNode) // valid arc
			{
				advance(matrix, currentNode, nextNode, excess);
				if (!inQueue[nextNode])
				{
					q.push(nextNode);
				}
			}
			else
			{		
				if (excess[currentNode] > 0)
				{
					exit = true;
					//return
					goback(matrix, currentNode, distances);
				}
			}
		} 
		while (excess[currentNode] != 0 && !exit);
		if (excess[currentNode] > 0)
		{
			q.push(currentNode);
		}
	}

	return matrix;
}
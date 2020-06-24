#include <io.hpp>

std::vector<std::vector<int>> createEmptyAdjacencyMatrix(int n)
{
	std::vector<std::vector<int>> matrix;
	for (auto i = 0; i < n; ++i)
	{
		matrix.push_back(std::vector<int>(n, 0));
	}
	return matrix;
}

std::vector<std::vector<int>> readFile(const std::string& filename)
{
	auto n = 0;
	std::ifstream fin(filename);
	fin >> n;
	
	auto matrix = createEmptyAdjacencyMatrix(n+1);

	while (!fin.eof())
	{
		auto x = 0, y = 0, c=0;
		fin >> x >> y >> c;
		matrix[x][y] = c;
	}

	return matrix;
}

void printAdjancyMatrix(const std::vector<std::vector<int>>& matrix)
{
	for (auto x = 1; x < matrix.size(); ++x)
	{
		for (auto y = 1; y < matrix.size(); ++y)
		{
			if (matrix[x][y] != 0)
			{
				std::cout << x << ' ' << y << ' ' << matrix[x][y] <<'\n';
			}
		}
	}
}

void printMaxFlowArcs(const std::vector<std::vector<int>>& matrix, const std::vector<std::vector<int>>& computedMatrix)
{
	std::cout << "Flux maxim:" << '\n';
	for (auto x = 1; x < matrix.size(); ++x)
	{
		for (auto y = 1; y < matrix.size(); ++y)
		{
			if (matrix[x][y] != 0)
			{
				int diff = matrix[x][y] - computedMatrix[x][y];
				int flow = diff >= 0 ? diff : 0;
				std::cout << x << ' ' << y << ' ' << flow << ',' << matrix[x][y] << '\n';
			}
		}
	}
}

void printMessage(std::string message)
{
	std::cout << '\n' << message << '\n';
}

std::vector<Job> readJobsData(std::string filename)
{
	auto n = 0; // nr of jobs
	auto m = 0; // nr of devices
	std::ifstream fin(filename);

	std::vector<Job> jobs;
	while (!fin.eof())
	{
		auto processTime = 0.f;
		auto aparitionDay = 0;
		auto finalizationDay = 0;
		fin >> processTime >> aparitionDay >> finalizationDay;
		jobs.push_back(Job(processTime, aparitionDay, finalizationDay));
	}

	return jobs;
}
int removeDecimalsFactor(float x)
{
	auto factor = 1;
	while ((x - std::floor(x)) != 0.0)
	{
		x *= 10;
factor *= 10;
	}

	return factor;
}

int removeDecimalsFactor(const std::vector<Job> jobs)
{
	int maxFactor = 1;
	for (auto job : jobs)
	{
		auto factor = removeDecimalsFactor(job.processTime);
		if (factor > maxFactor)
		{
			maxFactor = factor;
		}
	}

	return maxFactor;
}

int findMaxDay(const std::vector<Job> jobs)
{
	int maxDay = jobs.front().finalizationDay;
	for (auto job : jobs)
	{
		if (job.finalizationDay > maxDay)
		{
			maxDay = job.finalizationDay;
		}
	}
	return maxDay;
}

std::vector<std::vector<int>> splitDays(std::vector<Job> jobs)
{
	std::vector<std::vector<int>> mask(findMaxDay(jobs) + 1);
	for (auto i = 1; i < jobs.size(); ++i)
	{
		for (auto j = jobs[i].aparitionDay; j <= jobs[i].finalizationDay; ++j)
		{
			mask[j].push_back(i);
		}
	}

	return mask;
}

std::vector<std::vector<int>> createNodesForDayIntervals(const std::vector<std::vector<int>>& mask)
{
	std::vector<std::vector<int>> result(100);
	auto delta = 0;
	// mask[0] will always be empty
	for (auto i = 1; i < mask.size(); ++i)
	{
		if (mask[i].empty() && delta > 0)
		{
			int nodeValue = (i - delta) * 10 + (i - 1);
			result[nodeValue].assign(mask[i - 1].begin(), mask[i - 1].end());
			delta = 0;
		}
		if (!mask[i].empty())
		{
			if (mask[i] == mask[i - 1])
			{
				delta++;
			}
			else
			{
				if (delta > 0)
				{
					int nodeValue = (i - delta) * 10 + (i - 1);
					result[nodeValue].assign(mask[i - 1].begin(), mask[i - 1].end());
				}
				delta = 1;
			}
		}
	}
	if (delta > 0)
	{
		auto i = mask.size();
		int nodeValue = (i - delta) * 10 + (i - 1);
		result[nodeValue].assign(mask[i - 1].begin(), mask[i - 1].end());
	}

	return result;
}

int computeDays(int nodeForDayInterval)
{
	return nodeForDayInterval / 10 - nodeForDayInterval % 10 + 1;
}

std::vector<std::vector<int>> createMatrix(std::vector<Job> jobs, std::vector<std::vector<int>> nodeForDayIntervals, int factor, int devices)
{
	auto matrix = createEmptyAdjacencyMatrix(200);
	auto startNode = 100;
	auto stockNode = 150;
	for (auto y = 1; y < jobs.size(); ++y)
	{
		matrix[startNode][y] = (int)(jobs[y].processTime * factor);
	}
	for (auto y = 1; y < nodeForDayIntervals.size(); ++y)
	{
		if (!nodeForDayIntervals[y].empty())
		{
			for (auto job : nodeForDayIntervals[y])
			{
				matrix[job][y] = computeDays(y) * factor;
			}
			matrix[y][stockNode] = devices * factor;
		}	
	}
	return matrix;
}

std::vector<std::vector<int>> processJobsData(std::vector<Job> jobs)
{
	auto mask = splitDays(jobs);
	auto nodeForDayIntervals = createNodesForDayIntervals(mask);
	int devices = 3;
	int factor = removeDecimalsFactor(jobs);
	auto matrix = createMatrix(jobs, nodeForDayIntervals, factor, devices);

	return matrix;
}
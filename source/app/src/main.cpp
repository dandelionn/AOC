#include <io.hpp>
//#include <shortest_path_ahuja_orlin.hpp>
//#include <edmonds_karp.hpp>
#include <preflow_fifo.hpp>
//#include <preflow_with_biggest_label.hpp>
//#include <preflow_with_excess_scalling.hpp>
//#include <maximum_capacity_scaling_ahuja_orlin.hpp>

int main()
{
	auto matrix = readFile("C:\\Users\\Paul\\Desktop\\flow.in");
	//printAdjancyMatrix(matrix);
	auto startNode = 1;
	auto stockNode = 6;
	auto computedMatrix = computeMaxFlow(matrix, startNode, stockNode);
	printMaxFlowArcs(matrix, computedMatrix);

	/*auto jobs = readJobsData("C:\\Users\\Paul\\Desktop\\problem.in");
	matrix = processJobsData(jobs);
	computedMatrix = computeMaxFlow(matrix, startNode, stockNode);
	printMaxFlowArcs(matrix, computedMatrix);*/
}


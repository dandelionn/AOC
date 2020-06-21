#include <io.hpp>
#include <maximum_capacity_scaling_ahuja_orlin.hpp>
#include <shortest_path_ahuja_orlin.hpp>
#include <edmonds_karp.hpp>
#include <preflow_fifo.hpp>
#include <preflow_with_biggest_label.hpp>
#include <preflow_with_excess_scalling.hpp>


int main()
{
	printMessage("ROOTED TREE");
	auto tree = readFile("flow.in");
	printTree(tree);

	std::getchar();
}


#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <memory>
#include <deque>
#include <string>

struct Job {
	Job(float processTime, int aparitionDay, int finalizationDay) :processTime(processTime), aparitionDay(aparitionDay), finalizationDay(finalizationDay) {}
	float processTime;
	int aparitionDay;
	int finalizationDay;
};

void printMessage(std::string message);
void printAdjancyMatrix(const std::vector<std::vector<int>>& matrix);
std::vector<std::vector<int>> readFile(const std::string& filename);
void printMaxFlowArcs(const std::vector<std::vector<int>>& matrix, const std::vector<std::vector<int>>& computedMatrix);
std::vector<Job> readJobsData(std::string filename);
std::vector<std::vector<int>> processJobsData(std::vector<Job> jobs);


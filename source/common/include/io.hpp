#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <memory>
#include <deque>
#include <string>

std::vector<std::vector<int>> readFile(std::string filename);
template<class Container>
void printToConsole(const Container& container, std::string message);
void printMessage(std::string message);
void printTree(const std::vector<std::vector<int>>& tree);

template<class Container>
void printValues(const Container& container);
void printLine(std::string message);
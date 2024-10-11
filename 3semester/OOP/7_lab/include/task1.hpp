#pragma once

#include <iostream>
#include <random>

#include "list.hpp"

list<list<int>> createMatrix(std::size_t N);
void printMat(const list<list<int>>& mat);
void printArr(const list<int>& arr);
void getRightDiagonal(const list<list<int>>& mat);
void getLeftDiagonal(const list<list<int>>& mat);
void spiralFromCenter(const list<list<int>>& mat);
void spiralFromTopLeft(const list<list<int>>& mat);
void task1();

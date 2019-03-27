#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <deque>

using namespace std;

class CBase; //Predeclares CBase for use in loading of the file.

void loadFile(int& seed, vector<CBase*>& board); //File loading function for the seed and main game map.
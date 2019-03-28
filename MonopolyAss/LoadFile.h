#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <deque>
#include <algorithm>
#include <memory>
#include "Classes.h"

using namespace std;

class CBase; //Predeclares CBase for use in loading of the file.

void loadFile(int& seed, board& Board); //File loading function for the seed and main game map.
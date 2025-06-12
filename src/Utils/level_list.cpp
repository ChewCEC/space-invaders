#include "level_list.hpp"

// Define alien grids for different levels
const std::vector<std::vector<int>> level1Grid = 
{
    { 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
    { 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
    { 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

const std::vector<std::vector<int>> level2Grid = 
{
    { 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
    { 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
    { 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

const std::vector<std::vector<int>> level3Grid = 
{
    { 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
    { 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0 },
    { 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
const std::vector<std::vector<int>> level4Grid = 
{
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
    { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

const std::vector<std::vector<int>> level5Grid = 
{
    { 1, 0, 0, 2, 0, 2, 0, 2, 0, 0, 1 },
    { 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0 },
    { 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1 },
    { 0, 0, 0, 0, 3, 1, 3, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

const std::vector<std::vector<int>> level0Grid = 
{
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};



const std::vector<const std::vector<std::vector<int>>*> LEVELS = {
    &level0Grid,
    &level1Grid,
    &level2Grid,
    &level3Grid,
    &level4Grid,
    &level5Grid
};

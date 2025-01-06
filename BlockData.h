#pragma once
#include "Cell.h"
#include <vector>
#include <array>

struct BlockData {
    int width;
    int height;
    std::vector<Cell> shape;
    // TODO: Color
};

namespace BlockTemplates {
const std::array<BlockData,7> Blocks = {{
        // I Block
        {4,1,{
            Cell::Border,Cell::Border,Cell::Border,Cell::Border
        }},  

        // J Block
        {3,2,{
            Cell::Border,Cell::Empty,Cell::Empty,
            Cell::Border,Cell::Border,Cell::Border
        }},  

        // L Block
        {3,2,{
            Cell::Empty,Cell::Empty,Cell::Border,
            Cell::Border,Cell::Border,Cell::Border
        }},  

        // O Block
        {2,2,{
            Cell::Border,Cell::Border,
            Cell::Border,Cell::Border
        }},  

        // S Block
        {3,2,{
            Cell::Empty,Cell::Border,Cell::Border,
            Cell::Border,Cell::Border,Cell::Empty
        }},  

        // T Block
        {3,2,{
            Cell::Empty,Cell::Border,Cell::Empty,
            Cell::Border,Cell::Border,Cell::Border
        }},  

        // Z Block
        {3,2,{
            Cell::Border,Cell::Border,Cell::Empty,
            Cell::Empty,Cell::Border,Cell::Border
        }}   
    }};
}
#pragma once
#include "Cell.h"
#include <vector>
#include <array>

struct BlockData {
    int width;
    int height;
    std::vector<Cell> cells;
    WORD color;
};

namespace BlockTemplates {
    const std::array<BlockData, 7> Templates = {{
        // I Block
        {4, 1, {
            Cell::Border, Cell::Border, Cell::Border, Cell::Border
        }, 0x0B},  // Light Cyan
        
        // J Block
        {3, 2, {
            Cell::Border, Cell::Empty, Cell::Empty,
            Cell::Border, Cell::Border, Cell::Border
        }, 0x09},  // Blue
        
        // L Block
        {3, 2, {
            Cell::Empty, Cell::Empty, Cell::Border,
            Cell::Border, Cell::Border, Cell::Border
        }, 0x0C},  // Light Red
        
        // O Block
        {2, 2, {
            Cell::Border, Cell::Border,
            Cell::Border, Cell::Border
        }, 0x0E},  // Yellow
        
        // S Block
        {3, 2, {
            Cell::Empty, Cell::Border, Cell::Border,
            Cell::Border, Cell::Border, Cell::Empty
        }, 0x0A},  // Light Green
        
        // T Block
        {3, 2, {
            Cell::Empty, Cell::Border, Cell::Empty,
            Cell::Border, Cell::Border, Cell::Border
        }, 0x0D},  // Light Magenta
        
        // Z Block
        {3, 2, {
            Cell::Border, Cell::Border, Cell::Empty,
            Cell::Empty, Cell::Border, Cell::Border
        }, 0x0C}   // Light Red
    }};
} 
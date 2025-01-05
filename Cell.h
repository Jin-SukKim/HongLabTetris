#pragma once

enum class CellType {
	None = -1,
	Empty = 0,
	Border,
	Block
};

// TODO: Color 및 다른 기능을 추가로 적용 가능하도록 struct로 수정
struct Cell {
	Cell(CellType type = CellType::Empty) : Type(type) {}

	static const Cell None;
	static const Cell Empty;
	static const Cell Border;

	CellType Type = CellType::Empty;
};
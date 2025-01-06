struct Cell {
    Cell(CellType type = CellType::Empty, WORD color = 0x07) 
        : Type(type), Color(color) {}

    static const Cell None;
    static const Cell Empty;
    static const Cell Border;

    CellType Type = CellType::Empty;
    WORD Color = 0x07;  // Default to white on black
}; 
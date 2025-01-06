class Rectangle {
public:
    void SetCell(int x, int y, const Cell& cell);
    Cell GetCell(int x, int y) const;
    void Clear();
    virtual void Render(...);
    void SetDefaultColor(WORD color) { _defaultColor = color; }
    WORD GetDefaultColor() const { return _defaultColor; }
    // 직사각형 영역 채우기
    void Fill(const Cell& cell);
    
    // 직사각형 테두리 그리기
    void DrawBorder(const Cell& cell);
    
    // 특정 영역이 비어있는지 확인 (충돌 검사용)
    bool IsAreaEmpty(int startX, int startY, int width, int height) const;
    
    // 다른 Rectangle과의 충돌 검사
    virtual bool Collision(const Rectangle& other) = 0;
    
    // 위치 정보를 가져오는 메서드들 (이름 통일)
    int GetPosX() const { return _x; }
    int GetPosY() const { return _y; }
    void SetPos(int x, int y) { _x = x; _y = y; }
    
    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }
    
    // 상대적 위치 이동
    void Move(int deltaX, int deltaY) { 
        _x += deltaX; 
        _y += deltaY; 
    }
    
    // 월드 좌표계에서의 시작점을 가져오는 메서드 추가
    void GetWorldPosition(int& startX, int& startY) const {
        startX = _x - _width / 2;
        startY = _y - _height / 2;
    }
    // ...

protected:
    WORD _defaultColor = 0x07;  // 기본 흰색
    static const std::array<char, 4> _val;  // None, Empty, Border, Block에 대한 문자
    bool CheckCellCollision(const Rectangle& other) const;
}; 

class Board;  // Forward declaration of Board class 
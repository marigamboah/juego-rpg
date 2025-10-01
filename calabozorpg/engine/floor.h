#pragma once
class Floor {
public:
    explicit Floor(int f = 1) : floorNum_(f) {}
    int getFloorNum() const { return floorNum_; }
private:
    int floorNum_;
};

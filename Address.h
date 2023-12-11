#ifndef ADDRESS_H
#define ADDRESS_H

class Address {
public:
    Address(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}

    int getX() const { return x; }
    int getY() const { return y; }
  bool operator!=(const Address& other) const {
        return x != other.x || y != other.y;
    }
      bool operator==(const Address& other) const {
        return x == other.x && y == other.y;
    }
  bool operator<(const Address& other) const {
    if (x != other.x) {
        return x < other.x;
    }
    return y < other.y;
}

private:
    int x, y;
};

#endif // ADDRESS_H
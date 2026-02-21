#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Piece {
    
    private:
        char color, type;
        int x, y;
    
    public:
        Piece(char color, char type, int x, int y) : color(color), type(type), x(x), y(y) {}

        char getColor() const { return color; }
        char getType() const { return type; }
        int getX() const { return x; }
        int getY() const { return y; }

        virtual bool moveable(class Board& board, int x2, int y2) = 0;

        virtual ~Piece() {}
};

class Board {

    public:

        int static MOVE;
        vector<Piece*> pieces;

        Board() {}

        ~Board() {
            for (Piece* piece : pieces) {
                delete piece;
            }
        }

        void addPiece(Piece* piece) {
            pieces.push_back(piece);
        }

        Piece* getPieceAt(int x, int y) {
            for (Piece* piece : pieces) {
                if (piece->getX() == x && piece->getY() == y) return piece;
            }
            return nullptr;
        }

        bool emptyRoad(int x1, int y1, int x2, int y2) {
            int dx = (x2 > x1) - (x2 < x1);
            int dy = (y2 > y1) - (y2 < y1);

            int ddx = x1 + dx;
            int ddy = y1 + dy;
            while (ddx != x2 || ddy != y2) {
                if (getPieceAt(ddx, ddy)) {
                    return false;
                }
                ddx += dx;
                ddy += dy;
            }
            return true;
        }
};

class King : public Piece {

    public:
        King(char color, char type, int x, int y) : Piece(color, 'K', x, y) {}

        virtual bool moveable(Board& board, int x2, int y2) {
            if (abs(x2 - getX()) <= 1 && abs(y2 - getY()) <= 1) {
                return true;
            }
            return false;
        }
};

class Queen : public Piece {

    public:
        Queen(char color, char type, int x, int y) : Piece(color, 'Q', x, y) {}

        virtual bool moveable(Board& board, int x2, int y2) {
            if (getX() == x2 || getY() == y2 || abs(x2 - getX()) == abs(y2 - getY())) {
                return board.emptyRoad(getX(), getY(), x2, y2);
            }
            return false;
        }
};

class Rook : public Piece {
    
    public:
        Rook(char color, char type, int x, int y) : Piece(color, 'R', x, y) {}
    
        virtual bool moveable(Board& board, int x2, int y2) {
            if (getX() == x2 || getY() == y2) {
                return board.emptyRoad(getX(), getY(), x2, y2);
            }
            return false;
        }
};

class Bishop : public Piece {
    
    public:
        Bishop(char color, char type, int x, int y) : Piece(color, 'B', x, y) {}

        virtual bool moveable(Board& board, int x2, int y2) {
            if (abs(x2 - getX()) == abs(y2 - getY())) {
                return board.emptyRoad(getX(), getY(), x2, y2);
            }
            return false;
    }
};

class Knight : public Piece {
    
    public:
        Knight(char color, char type, int x, int y) : Piece(color, 'N', x, y) {}
    
        virtual bool moveable(Board& board, int x2, int y2) {
            if ((abs(x2 - getX()) == 2 && abs(y2 - getY()) == 1) || (abs(x2 - getX()) == 1 && abs(y2 - getY()) == 2)) {
                return true;
            }
            return false;
        }
};

class Pawn : public Piece {

    public:
        Pawn(char color, char type, int x, int y) : Piece(color, 'P', x, y) {}

        virtual bool moveable(Board& board, int x2, int y2) {
            if (getColor() == 'W') {
                // حرکت
                if (getX() == x2 && (y2 == getY() + 1 || (getY() == 1 && y2 == getY() + 2)) && !board.getPieceAt(x2, y2)) {
                    return true;
                }
                // تیک
                if (abs(x2 - getX()) == 1 && y2 == getY() + 1 && board.getPieceAt(x2, y2) && board.getPieceAt(x2, y2)->getColor() != getColor()) {
                    return true;
                }
                // آمپاسان
                if (abs(x2 - getX()) == 1 && y2 == getY() + 1) {       // مورب
                    Piece* myPawn = board.getPieceAt(x2, y2 - 1);
                    if (myPawn && myPawn->getType() == 'P' && myPawn->getColor() != getColor() && getY() == 4) {
                        return true;
                    }
                }
            }
            else {
                // حرکت معمولی
                if (getX() == x2 && (y2 == getY() - 1 || (getY() == 6 && y2 == getY() - 2)) && !board.getPieceAt(x2, y2)) {
                    return true;
                }
                // گرفتن مهره
                if (abs(x2 - getX()) == 1 && y2 == getY() - 1 && board.getPieceAt(x2, y2) && board.getPieceAt(x2, y2)->getColor() != getColor()) {
                    return true;
                }
                // حرکت آمپاسان
                if (abs(x2 - getX()) == 1 && y2 == getY() - 1) {
                    Piece* myPawn = board.getPieceAt(x2, y2 + 1); // مهره‌ای که باید گرفته شود
                    if (myPawn && myPawn->getType() == 'P' && myPawn->getColor() != getColor() && getY() == 3) {
                        return true;
                    }
                }
            }
            return false;
        }
};

pair<int, int> position(const string& pos) {
    int x = pos[0] - 'A';
    int y = pos[1] - '1';
    return {x, y};
}


int Board::MOVE;


int main() {

    ifstream i_f("input.txt");
    ofstream o_f("output.txt");

    if (!i_f || !o_f) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    int n;
    i_f >> n;

    Board board;

    for (int i = 0; i < n; ++i) {

        string input;
        i_f >> input;
        
        char color = input[0] == 'W' ? 'W' : 'B';
        char type = input[1];
        auto [x, y] = position(input.substr(2));

        switch (type) {
            case 'K':
                board.addPiece(new King(color, 'K', x, y));
                break;
            case 'Q':
                board.addPiece(new Queen(color, 'Q', x, y));
                break;
            case 'R':
                board.addPiece(new Rook(color, 'R', x, y));
                break;
            case 'B':
                board.addPiece(new Bishop(color, 'B', x, y));
                break;
            case 'N':
                board.addPiece(new Knight(color, 'N', x, y));
                break;
            case 'P':
                board.addPiece(new Pawn(color, 'P', x, y));
                break;
        }
    }

    int m;
    i_f >> m;
    Board::MOVE = m;

    vector<string> results;

    for (int i = 0; i < m; ++i) {

        string move;
        i_f >> move;
        auto [x1, y1] = position(move.substr(0, 2));
        auto [x2, y2] = position(move.substr(2));

        Piece* piece = board.getPieceAt(x1, y1);
        if (!piece) {
            results.push_back("NO");
        }

        else if (piece->moveable(board, x2, y2)) {
            if (board.getPieceAt(x2, y2)) {
                results.push_back("TAKE");
            }
            else if (dynamic_cast<Pawn*>(piece) && abs(x2 - x1) == 1 && !board.getPieceAt(x2, y2)) {
                results.push_back("TAKE"); // آمپاسان
            }
            else {
                results.push_back("YES");
            }
        }

        else {
            results.push_back("NO");
        }
    }

    for (string& result : results) {
        o_f << result << endl;
    }

    i_f.close();
    o_f.close();

    return 0;
}

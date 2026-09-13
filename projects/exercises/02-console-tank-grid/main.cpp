#include <iostream>
#include <string>
#include <vector>
#include <cstddef>

enum class MoveDirection
{
    Up,
    Left,
    Down,
    Right
};

enum class MoveResult
{
    Moved,
    BlockedByBoundary,
    BlockedByWall
};

MoveResult moveTank(
    const std::vector<std::string>& board,
    int& tankX,
    int& tankY,
    MoveDirection direction
)
{
    int candidateX{tankX};
    int candidateY{tankY};

    switch (direction)
    {
        case MoveDirection::Up:
            --candidateY;
            break;
        case MoveDirection::Left:
            --candidateX;
            break;
        case MoveDirection::Down:
            ++candidateY;
            break;
        case MoveDirection::Right:
            ++candidateX;
            break;
    }

    if (candidateX < 0 || candidateY < 0)
    {
        return MoveResult::BlockedByBoundary;
    }

    const auto row{static_cast<std::size_t>(candidateY)};
    const auto column{static_cast<std::size_t>(candidateX)};

    if (row >= board.size())
    {
        return MoveResult::BlockedByBoundary;
    }

    if (column >= board[row].size())
    {
        return MoveResult::BlockedByBoundary;
    }

    if (board[row][column] == '#')
    {
        return MoveResult::BlockedByWall;
    }

    tankX = candidateX;
    tankY = candidateY;

    return MoveResult::Moved;
}

void renderBoard(
    const std::vector<std::string>& board,
    int tankX,
    int tankY)
{
    int y{};

    for (const std::string& row : board)
    {
        int x{};

        for (char tile : row)
        {
            if (x == tankX && y == tankY)
            {
                std::cout << "T";
            }
            else
            {
                std::cout << tile;
            }

            ++x;
        }

        std::cout << "\n";
        ++y;
    }

    std::cout << "Legend: T=tank, .=floor, #=wall, *=mine, E=extraction\n";
}

int main()
{
    const std::vector<std::string> board{
        "########",
        "#......#",
        "#.##...#",
        "#...#E.#",
        "#..*...#",
        "########"
    };
    int tankX{1};
    int tankY{1};

    renderBoard(board, tankX, tankY);

    const std::vector<MoveDirection> moves{
        MoveDirection::Up,
        MoveDirection::Down,
        MoveDirection::Down,
        MoveDirection::Right,
        MoveDirection::Down,
        MoveDirection::Right,
        MoveDirection::Left,
        MoveDirection::Up
    };

    for (MoveDirection move : moves)
    {
        MoveResult moveResult{
            moveTank(board, tankX, tankY, move)
        };

        if (moveResult == MoveResult::Moved)
        {
            renderBoard(board, tankX, tankY);
        }
        else if (moveResult == MoveResult::BlockedByBoundary)
        {
            std::cout << "Blocked by boundary.\n";
        }
        else if (moveResult == MoveResult::BlockedByWall)
        {
            std::cout << "Blocked by wall.\n";
        }
    }

    return 0;
}

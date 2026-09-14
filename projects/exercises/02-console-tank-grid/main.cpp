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

enum class RoundStatus
{
    Playing,
    Won,
    Lost
};

enum class MoveResult
{
    Moved,
    BlockedByBoundary,
    BlockedByWall,
    RoundFinished
};

enum class CommandKind
{
    Move,
    Restart,
    Quit,
    Invalid
};

struct GameState
{
    std::vector<std::string> board;
    int tankX{};
    int tankY{};
    RoundStatus roundStatus{RoundStatus::Playing};
};

struct ParsedCommand
{
    CommandKind kind{CommandKind::Invalid};
    MoveDirection direction{MoveDirection::Up};
};

GameState makeInitialGameState()
{
    return {
        {
            "########",
            "#......#",
            "#.##...#",
            "#...#E.#",
            "#..*...#",
            "########"
        },
        1,
        1,
        RoundStatus::Playing
    };
}

ParsedCommand parseCommand(const std::string& line)
{
    const auto first{line.find_first_not_of(" \t")};

    if (first == std::string::npos)
    {
        return {};
    }

    const auto last{line.find_last_not_of(" \t")};

    // Exactly one non-whitespace character is permitted
    if (first != last)
    {
        return {};
    }

    switch (line[first])
    {
        case 'w':
            return {CommandKind::Move, MoveDirection::Up};
        case 'a':
            return {CommandKind::Move, MoveDirection::Left};
        case 's':
            return {CommandKind::Move, MoveDirection::Down};
        case 'd':
            return {CommandKind::Move, MoveDirection::Right};
        case 'q':
            return {CommandKind::Quit, MoveDirection::Up};
        case 'r':
            return {CommandKind::Restart, MoveDirection::Up};
        default:
            return {};
    }
}

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
    std::cout << "Commands: w=up, a=left, s=down, d=right, r=restart, q=quit\n";
}

int main()
{
    GameState game{makeInitialGameState()};

    renderBoard(game.board, game.tankX, game.tankY);

    while (true)
    {
        std::cout << "\nEnter command: ";

        std::string line;

        if (!std::getline(std::cin, line))
        {
            if (std::cin.eof() && !std::cin.bad())
            {
                std::cout << "\nEnd of input.\n";
                break;
            }

            std::cerr << "\nFailed to read input.\n";
            return 1;
        }

        const ParsedCommand command{parseCommand(line)};

        if (command.kind == CommandKind::Invalid)
        {
            std::cout << "Invalid command. Enter exactly one of: w, a, s, d, r, q.\n";
            continue;
        }

        if (command.kind == CommandKind::Quit)
        {
            std::cout << "Goodbye.\n";
            break;
        }

        if (command.kind == CommandKind::Restart)
        {
            game = makeInitialGameState();

            std::cout << "Round restarted.\n";
            renderBoard(game.board, game.tankX, game.tankY);
            continue;
        }

        const MoveResult moveResult{
            moveTank(game.board, game.tankX, game.tankY, command.direction)
        };

        if (moveResult == MoveResult::BlockedByBoundary)
        {
            std::cout << "Blocked by boundary.\n";
        }
        else if (moveResult == MoveResult::BlockedByWall)
        {
            std::cout << "Blocked by wall.\n";
        }

        renderBoard(game.board, game.tankX, game.tankY);
    }

    return 0;
}

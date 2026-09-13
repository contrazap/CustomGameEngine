#include <iostream>
#include <string>
#include <vector>

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
    std::cout << "Legend: T=tank, .=floor, #=wall, *=mine, E=extraction\n";

    return 0;
}

#include "levels/LevelOne.h"

#include "actors/Ball_Regular.h"
#include "actors/Block_Regular.h"
#include "actors/Block_Boundry.h"
#include "actors/Player.h"

namespace bo
{
	LevelOne::LevelOne(Application* owningApplication)
		: eb::World{owningApplication}
	{
		// Player
		_player = SpawnActor<Player>(sf::Vector2f{ 100.f, 25.f }, sf::Color::White);
		float playerXStartingPos = GetWindowSize().x / 2 - _player.lock()->GetActorGlobalRectBounds().width / 2;
		float playerYStartingPos = GetWindowSize().y * 0.9;
		_player.lock()->SetActorLocation(sf::Vector2f(playerXStartingPos, playerYStartingPos));

		// BLOCKS
		_blocks.lock()->SpawnBlocks(this); /// TODO: look into cache misses in nested for loops, row/col. - Move spawn logic into here. 
        _boundry.lock()->SpawnBoundry(this); /// TODO: Move to Level Base Class

		// BALL
		_ball = SpawnActor<Ball_Regular>(15.f, sf::Color::Cyan);
		float ballXStartingPos = GetWindowSize().x / 2 - _ball.lock()->GetActorGlobalRectBounds().width / 2;
		float ballYStartingPos = GetWindowSize().y * 0.5;
		_ball.lock()->SetActorLocation(sf::Vector2f(ballXStartingPos, ballYStartingPos));
	}

	void LevelOne::BeginPlay()
	{
		PRINT("Level One Begin Play!");
	}
}

/// TODO: Batch & Performance & Debugging
/*==============================================================================
BATCH CREATION AND LEVEL MANAGEMENT

Overview:
---------
Batch creation improves performance by reducing individual memory allocations and
providing a more cache-friendly way to initialize multiple objects at once.

Block Batch Structure:
---------------------
struct BlockBatchData {
	sf::Vector2f position;    // Where block will be placed
	sf::Vector2f size;        // Block dimensions
	sf::Color color;          // Block color
	BlockType type;           // Type (regular, special, etc.)
	int hitPoints;            // Durability
};

How to Use:
-----------
1. Level class prepares vector of BlockBatchData
2. Calls Block::CreateBlocks with this data
3. Stores resulting blocks in level

Example Usage:
-------------
// In Level class:
std::vector<BlockBatchData> batchData;
batchData.reserve(rows * columns);  // Prevent reallocation

// Fill batch data
for(int i = 0; i < rows; i++) {
	for(int j = 0; j < columns; j++) {
		batchData.push_back({
			CalculatePosition(i, j),
			blockSize,
			GetColorForBlock(i, j),
			DetermineBlockType(i, j),
			GetHitPoints(i, j)
		});
	}
}

// Create all blocks at once
auto blocks = Block::CreateBlocks(batchData);

Performance Benefits:
-------------------
1. Single memory allocation for batch data
2. Better cache utilization
3. Reduced overhead from multiple constructor calls
4. Easier memory management
5. More efficient than creating blocks one at a time

Memory Considerations:
--------------------
- PreAllocate vectors using reserve()
- Use move semantics when possible
- Consider using object pools for dynamic block creation
- Clean up inactive blocks periodically

Pattern Management:
-----------------
Store level patterns in easily modifiable format:
const std::vector<std::string> LEVEL_1 = {
	"RRRRR",
	"GGGGG",
	"BBBBB"
};

Where:
R = Red Block
G = Green Block
B = Blue Block
etc.

This makes it easy to design and modify levels.

==============================================================================*/

/*
* Pre allocated level slots
* =============================================================================
* class Level {
private:
    struct GridCell {
        bool isOccupied = false;
        BlockType type = BlockType::None;
        sf::Color color = sf::Color::White;
        int hitPoints = 0;
    };

    // Pre-allocated grid
    static const int MAX_ROWS = 20;
    static const int MAX_COLS = 30;
    GridCell grid[MAX_ROWS][MAX_COLS];

    // Block dimensions and spacing
    sf::Vector2f blockSize{50.f, 20.f};
    sf::Vector2f spacing{5.f, 5.f};
    sf::Vector2f startOffset{100.f, 50.f};

public:
    // Easy way to set up patterns using indices
    void SetBlock(int row, int col, BlockType type, sf::Color color, int hp = 1) {
        if (row < MAX_ROWS && col < MAX_COLS) {
            grid[row][col].isOccupied = true;
            grid[row][col].type = type;
            grid[row][col].color = color;
            grid[row][col].hitPoints = hp;
        }
    }

    // Generate blocks based on occupied grid cells
    void CreateBlocks() {
        std::vector<Block::BlockBatchData> batchData;
        
        for(int row = 0; row < MAX_ROWS; row++) {
            for(int col = 0; col < MAX_COLS; col++) {
                if(grid[row][col].isOccupied) {
                    sf::Vector2f position = {
                        startOffset.x + (blockSize.x + spacing.x) * col,
                        startOffset.y + (blockSize.y + spacing.y) * row
                    };

                    batchData.push_back({
                        position,
                        blockSize,
                        grid[row][col].color,
                        grid[row][col].type,
                        grid[row][col].hitPoints
                    });
                }
            }
        }

        // Create blocks in batch
        blocks = Block::CreateBlocks(batchData);
    }

    // Easy level creation
    void CreateClassicPattern() {
        // Row 1: Red blocks
        for(int col = 0; col < 10; col++) {
            SetBlock(0, col, BlockType::Regular, sf::Color::Red);
        }
        
        // Row 2: Blue blocks
        for(int col = 0; col < 10; col++) {
            SetBlock(1, col, BlockType::Regular, sf::Color::Blue);
        }

        // Create all blocks at once
        CreateBlocks();
    }

    // Or load from a pattern
    void LoadPattern(const std::vector<std::string>& pattern) {
        for(int row = 0; row < pattern.size(); row++) {
            for(int col = 0; col < pattern[row].length(); col++) {
                switch(pattern[row][col]) {
                    case 'R': 
                        SetBlock(row, col, BlockType::Regular, sf::Color::Red);
                        break;
                    case 'B': 
                        SetBlock(row, col, BlockType::Regular, sf::Color::Blue);
                        break;
                    // etc...
                }
            }
        }
        
        CreateBlocks();
    }
};

// Usage:
void Game::LoadLevel1() {
    const std::vector<std::string> LEVEL_1 = {
        "RRRRRRRRRR",
        "BBBBBBBBBB",
        "GGGGGGGGGG",
        "YYYYYYYYYY"
    };
    
    level.LoadPattern(LEVEL_1);
}
*/
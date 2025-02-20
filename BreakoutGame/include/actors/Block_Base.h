#pragma once 

#include "framework/Actor.h"

namespace bo
{
	class Level_Base;
	class Block_Base : public eb::Actor
	{
	protected:
		static const sf::Vector2f DefaultRectSize;

	public:
		Block_Base(eb::World* owningWorld, sf::Color color = sf::Color::White, sf::Vector2f rectSize = DefaultRectSize);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

		virtual ~Block_Base() = default;

		Level_Base* GetCurrentLevel() const { return _currentLevel; }

	private:
		Level_Base* _currentLevel;
	};
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
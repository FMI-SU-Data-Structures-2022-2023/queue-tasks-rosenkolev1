#define CATCH_CONFIG_MAIN // This should come **before** including the 'catch.hpp'.
#include <vector>
#include "catch.hpp"
#include "queueTasks.cpp"

TEST_CASE( "1: Kittens" ) {
    REQUIRE( kittens("BB", 3) == 3 );
    REQUIRE( kittens("SSBB", 3) == 2 );
    REQUIRE( kittens("SSBBOOOOOOOSBOOOOOOOOOSB", 5) == 1 );
    REQUIRE( kittens("SOOSBBOOOOSOOOSBOOOBOOSOOBOOSOOB", 7) == 3 );
}

TEST_CASE( "2: BFS" ) {
    std::vector<vector<int>> g;
    vector<int> first = {1, 2};
    vector<int> second = {0, 2, 3, 6};
    vector<int> empty;
    g.push_back(first);  // 0
    g.push_back(second); // 1
    g.push_back(empty);  // 2
    g.push_back(empty);  // 3
    g.push_back(empty);  // 4
    g.push_back(empty);  // 5
    g.push_back(empty);  // 6
    g.push_back(empty);  // 7
    REQUIRE( bfs(g, 0, 6) == 2 );
    REQUIRE( bfs(g, 5, 6) == -1 );
    REQUIRE( bfs(g, 1, 3) == 1 );
}

TEST_CASE( "3: Horse" ) {
    REQUIRE( horse("A1", "B3") == 1 );
}

TEST_CASE( "4: Island" ) {
	vector<vector<int>> zeroIslands =
    {
        { 0, 0, 0},
        { 0, 0, 0}
    };
	REQUIRE( islands(zeroIslands) == 0 );
	vector<vector<int>> moreIslands =
    {
        { 1, 0, 1},
        { 0, 1, 0}
    };
	REQUIRE( islands(moreIslands) == 3 );
	vector<vector<int>> moreIslands1 =
    {
        { 1, 0, 1},
	{ 0, 0, 0},
	{ 0, 1, 1},
	{ 1, 0, 0},
	{ 1, 0, 1},
	{ 1, 0, 0}
    };
	REQUIRE( islands(moreIslands1) == 5 );
}

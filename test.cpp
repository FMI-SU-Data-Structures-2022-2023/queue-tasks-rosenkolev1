#define CATCH_CONFIG_MAIN // This should come **before** including the 'catch.hpp'.
#include <vector>
#include "catch.hpp"
#include "queueTasks.cpp"

TEST_CASE( "1: Kittens" ) {
    REQUIRE( kittens("BB", 3) == 3 );
    REQUIRE( kittens("SSBB", 3) == 2 );
    REQUIRE(kittens("SOOSBBOOOOSOOOSBOSOOBOSOSOOBOSOSOOB", 7) == 3);
    REQUIRE( kittens("SSBBOOOOOOOSBOOOOOOOOOSB", 5) == 1 );
    //REQUIRE( kittens("SOOSBBOOOOSOOOSBOOOBOOSOOBOOSOOB", 7) == 3 );
    //SOOSBBOOOOSOOOSBOOOBOOSOOBOOSOOB (0, 0, 0, 0, 0, 0, 0)
    //BOOOOSOOOSBOOOBOOSOOBOOSOOB 5 (1, 0, 0, 1, -1, 0, 0)
    //OOOOSOOOSBOOOBOOSOOBOOSOOB 6 (1, 0, 0, 1, -1, -1, 0) 
    //OOOBOOSOOBOOSOOBB 4 (1, 0, 1, 1, -1, -1, 0) 
    //OOSOOBOOSOOBBB  3 (1, 0, 0, 1, -1, -1, 0)
    //OOSOOBBBB  4 (2, 0, 0, 0, -1, -1, 0)
    //BBB  7 (2, 1, 0, 0, -1, -1, -1)
    //BBB  1 (1, 1, 0, 0, -1, -1, -1)
    //BBB  2 (1, 0, 0, 0, -1, -1, -1)
    //BB  3 (1, 0, -1, 0, -1, -1, -1)
    //B  4 (1, 0, -1, -1, -1, -1, -1)
    //B  1 (0, 0, -1, -1, -1, -1, -1)
    //  2 (0, -1, -1, -1, -1, -1, -1)
}

TEST_CASE( "2: BFS" ) {
    std::vector<std::vector<int>> g;
    std::vector<int> first = {1, 2};
    std::vector<int> second = {0, 2, 3, 6};
    std::vector<int> empty;
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
    //Svilen tests
    REQUIRE( horse("A1", "B3") == 1 );

    //My tests
    REQUIRE(horse("A1", "A1") == 0);
    REQUIRE(horse("A1", "A2") == 3);
    REQUIRE(horse("A1", "B2") == 4);
    REQUIRE(horse("A1", "A3") == 2);
    REQUIRE(horse("A1", "C3") == 4);
}

TEST_CASE( "4: Island" ) {

	std::vector<std::vector<int>> zeroIslands =
    {
        { 0, 0, 0},
        { 0, 0, 0}
    };
	REQUIRE( islands(zeroIslands) == 0 );

    std::vector<std::vector<int>> moreIslands =
    {
        { 1, 0, 1},
        { 0, 1, 0}
    };
	REQUIRE( islands(moreIslands) == 3 );

    std::vector<std::vector<int>> moreIslands1 =
    {
        { 1, 0, 1},
	    { 0, 0, 0},
	    { 0, 1, 1},
	    { 1, 0, 0},
	    { 1, 0, 1},
	    { 1, 0, 0}
    };
	REQUIRE( islands(moreIslands1) == 5 );

    //This test is mine
    std::vector<std::vector<int>> moreIslands2 =
    {
        { 1, 0, 1},
        { 0, 0, 0},
        { 0, 1, 1},
        { 1, 0, 0},
        { 1, 1, 1},
        { 1, 1, 0}
    };
    REQUIRE(islands(moreIslands2) == 4);
}

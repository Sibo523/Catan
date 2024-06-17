
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "GameManager.h"
#include <sstream>
#include <iostream>
#include <string>
#define GREEN_TEXT "\033[1;32m"
#define lm_TEXT "\033[1;39m"

///////////////////////////////////////////////////Player Test Cases////////////////////////////////////////////
TEST_CASE("creation of player")
{
    Player player1 = Player("player1", GREEN_TEXT);
    CHECK_EQ(player1.getName(), "player1");
    CHECK_EQ(player1.getColor(), GREEN_TEXT);
    CHECK_EQ(player1.getVictoryPoints(), 0);
    CHECK_EQ(player1.getKnightCount(), 0);
    CHECK_EQ(player1.getResources().at("wood"), 0);
    CHECK_EQ(player1.getResources().at("brick"), 0);
    CHECK_EQ(player1.getResources().at("sheep"), 0);
    CHECK_EQ(player1.getResources().at("wheat"), 0);
    CHECK_EQ(player1.getResources().at("ore"), 0);
}
TEST_CASE("add resources")
{
    Player player1 = Player("player1", GREEN_TEXT);
    player1.addResource("wood", 1);
    player1.addResource("brick", 2);
    player1.addResource("sheep", 3);
    player1.addResource("wheat", 4);
    player1.addResource("ore", 5);
    CHECK_EQ(player1.getResources().at("wood"), 1);
    CHECK_EQ(player1.getResources().at("brick"), 2);
    CHECK_EQ(player1.getResources().at("sheep"), 3);
    CHECK_EQ(player1.getResources().at("wheat"), 4);
    CHECK_EQ(player1.getResources().at("ore"), 5);
    std::map<std::string, int> resources = player1.getResources();
    Player player2 = Player("player2", GREEN_TEXT);
    player2.addResources(resources);
    CHECK_EQ(player2.getResources().at("wood"), 1);
    CHECK_EQ(player2.getResources().at("brick"), 2);
    CHECK_EQ(player2.getResources().at("sheep"), 3);
    CHECK_EQ(player2.getResources().at("wheat"), 4);
    CHECK_EQ(player2.getResources().at("ore"), 5);
}
TEST_CASE("subtract resources")
{
    Player player1 = Player("player1", GREEN_TEXT);
    player1.addResource("wood", 1);
    player1.addResource("brick", 2);
    player1.addResource("sheep", 3);
    player1.addResource("wheat", 4);
    player1.addResource("ore", 5);
    player1.subtractResources({{"wood", 1}, {"brick", 2}, {"sheep", 3}, {"wheat", 4}, {"ore", 5}});
    CHECK_EQ(player1.getResources().at("wood"), 0);
    CHECK_EQ(player1.getResources().at("brick"), 0);
    CHECK_EQ(player1.getResources().at("sheep"), 0);
    CHECK_EQ(player1.getResources().at("wheat"), 0);
    CHECK_EQ(player1.getResources().at("ore"), 0);
}
TEST_CASE("build settlment")
{
    Player player1 = Player("player1", GREEN_TEXT);
    CHECK_EQ(player1.buildSettlement(), false);
    player1.addResource("wood", 1);
    player1.addResource("brick", 1);
    player1.addResource("sheep", 1);
    player1.addResource("wheat", 1);
    CHECK_EQ(player1.buildSettlement(), true);
    CHECK_EQ(player1.getResources().at("wood"), 0);
    CHECK_EQ(player1.getResources().at("brick"), 0);
    CHECK_EQ(player1.getResources().at("sheep"), 0);
    CHECK_EQ(player1.getResources().at("wheat"), 0);
}
TEST_CASE("build road")
{
    Player player1 = Player("player1", GREEN_TEXT);
    CHECK_EQ(player1.buildRoad(), false);
    player1.addResource("wood", 1);
    player1.addResource("brick", 1);
    CHECK_EQ(player1.buildRoad(), true);
    CHECK_EQ(player1.getResources().at("wood"), 0);
    CHECK_EQ(player1.getResources().at("brick"), 0);
}
TEST_CASE("upgrade to city")
{
    Player player1 = Player("player1", GREEN_TEXT);
    CHECK_EQ(player1.upgradeToCity(), false);
    player1.addResource("wheat", 2);
    player1.addResource("ore", 3);
    CHECK_EQ(player1.upgradeToCity(), true);
    CHECK_EQ(player1.getResources().at("wheat"), 0);
    CHECK_EQ(player1.getResources().at("ore"), 0);
}
TEST_CASE("buy development card and use")
{
    Player player1 = Player("player1", GREEN_TEXT);
    KnightCard *knightCard = new KnightCard();
    CHECK_EQ(player1.buyDevCard(knightCard), false);
    player1.addResource("wheat", 1);
    player1.addResource("sheep", 1);
    player1.addResource("ore", 1);
    CHECK_EQ(player1.buyDevCard(knightCard), true);
    CHECK_EQ(player1.useDevelopmentCard("Knight"), true);
    CHECK_EQ(player1.getKnightCount(), 0); // I change it using the switch case in game manager
}
TEST_CASE("amoung of victory points")
{
    Player player1 = Player("player1", GREEN_TEXT);
    CHECK_EQ(player1.getVictoryPoints(), 0);
    player1.addResource("wood", 1);
    player1.addResource("brick", 1);
    player1.addResource("sheep", 1);
    player1.addResource("wheat", 1);
    player1.buildSettlement(); // 1 victory point
    CHECK_EQ(player1.getVictoryPoints(), 1);
    player1.addResource("wheat", 2);
    player1.addResource("ore", 3);
    player1.upgradeToCity(); // 2 victory point
    CHECK_EQ(player1.getVictoryPoints(), 2);
    player1.addResource("wheat", 10);
    player1.addResource("sheep", 10);
    player1.addResource("ore", 10);
    KnightCard *knightCard = new KnightCard();
    player1.buyDevCard(knightCard);
    CHECK_EQ(player1.getVictoryPoints(), 2);
    player1.addKnight();
    player1.largestArmy(); // it autumatically adds 2 victory points the game manager checks if actually needer or not
    CHECK_EQ(player1.getVictoryPoints(), 4);
    VictoryPointCard *victoryPointCard = new VictoryPointCard();
    player1.buyDevCard(victoryPointCard); // seg fault cause the test frees the memory and I free in the player
    CHECK_EQ(player1.getVictoryPoints(), 5);
    delete knightCard;
}

TEST_CASE("Show resources")
{
    Player player1 = Player("player1", GREEN_TEXT);
    CHECK_EQ(player1.showResources(), "wood: 0\nbrick: 0\nsheep: 0\nwheat: 0\nore: 0\nDevelopment Cards:\n");
    player1.addResource("wood", 1);
    player1.addResource("brick", 2);
    player1.addResource("sheep", 3);
    player1.addResource("wheat", 4);
    player1.addResource("ore", 5);
    CHECK_EQ(player1.showResources(), "wood: 1\nbrick: 2\nsheep: 3\nwheat: 4\nore: 5\nDevelopment Cards:\n");
}
///////////////////////////////////////////////////Board Test Cases////////////////////////////////////////////
TEST_CASE("Check dice generation") // and build settlment
{
    Board board = Board();
    Player player1 = Player("player1", GREEN_TEXT);
    std::map<std::string, int> resources = {{"wood", 1}, {"brick", 1}, {"sheep", 1}, {"wheat", 3}, {"ore", 3}};
    player1.addResources(resources);
    board.buildSet(4, 0, 1, &player1, false);
    board.generateResources(6);
    CHECK_EQ(player1.getResources().at("brick"), 1);
    board.upgradeToCity(4, 0, 1, &player1);
    board.generateResources(6);
    CHECK_EQ(player1.getResources().at("brick"), 3);
    player1.addResources(resources);
    CHECK(board.buildRoad(4, 0, 1, &player1));
}
///////////////////////////////////////////////////Settlement Test Cases////////////////////////////////////////////
TEST_CASE("Settlement creation")
{
    Player *player1 = new Player("player1", GREEN_TEXT);
    Settlement settlement = Settlement(player1);
    CHECK_EQ(settlement.getOwnerPtr(), player1);
    CHECK_EQ(settlement.getAmount(), 1);
    settlement.upgradeToCity();
    CHECK_EQ(settlement.getAmount(), 2);
    delete player1;
}
///////////////////////////////////////////////////Tile Test Cases////////////////////////////////////////////
TEST_CASE("Tile creation")
{
    Tile tile = Tile("wood", 5);
    CHECK_EQ(tile.getResource(), "wood");
    CHECK_EQ(tile.getNumberToken(), 5);
    CHECK_EQ(tile.toString(), "wood-5");
    Player *player1 = new Player("player1", GREEN_TEXT);
    Road *road = new Road(player1);
    CHECK_THROWS(tile.addRoad(road, 0));
    tile.addRoad(road, 1);
    CHECK_EQ(tile.getRoadPtr(1), road);
    delete player1;
    delete road;
}
///////////////////////////////////////////////////Card Test Cases////////////////////////////////////////////
TEST_CASE("Card creation")
{
    KnightCard knightCard = KnightCard();
    CHECK_EQ(knightCard.getType(), "Knight");
    VictoryPointCard victoryPointCard = VictoryPointCard();
    CHECK_EQ(victoryPointCard.getType(), "VictoryPoint");
    MonopolyCard monopolyCard = MonopolyCard();
    CHECK_EQ(monopolyCard.getType(), "Monopoly");
    RoadBuildingCard roadBuildingCard = RoadBuildingCard();
    CHECK_EQ(roadBuildingCard.getType(), "RoadBuilding");
    YearOfPlentyCard yearOfPlentyCard = YearOfPlentyCard();
    CHECK_EQ(yearOfPlentyCard.getType(), "YearOfPlenty");
}
///////////////////////////////////////////////////Vertex Test Cases////////////////////////////////////////////
TEST_CASE("Vertex creation")
{
    Vertex vertex = Vertex(1, 2);
    CHECK_THROWS(vertex.getOwnerPlayerPtr(), nullptr);
    CHECK_EQ(vertex.getSettlementPtr(), nullptr);
    Player *player1 = new Player("player1", GREEN_TEXT);
    Settlement *settlement = new Settlement(player1);
    vertex.settle(settlement);
    CHECK_EQ(vertex.getSettlementPtr(), settlement);
    CHECK_EQ(vertex.getOwnerPlayerPtr(), player1);
    CHECK(vertex.isSettled());
    delete player1;
    delete settlement;
}
///////////////////////////////////////////////////Road Test Cases////////////////////////////////////////////
TEST_CASE("Road creation")
{
    Player *player1 = new Player("player1", GREEN_TEXT);
    Road road = Road(player1);
    CHECK_EQ(road.getOwnerPtr(), player1);
    delete player1;
}
//////////////////////////////////////////////////GameManager Test Cases///////////////////////////////////////////
void readAndPrint()
{
    std::string input;
    std::cin >> input;
    std::cout << "input was:" << input << std::endl;
}
TEST_CASE("GameMangager Test case")
{
    std::istringstream iss(R"(
1 2 3
1 2 2
2 2 2
2 2 6
0 0 1
0 0 1
4 0 1
4 0 1
3
1 2 3
1
2 2 3
1
4 2 1
2
8
9
YearOfPlenty
wood
brick
8
7
5
1 
1 1 1 1 1
0 0 0 0 0
y 
6)");
    Player *player1 = new Player("player1", GREEN_TEXT);
    std::map<std::string, int> resources = {{"wood", 10}, {"brick", 10}, {"sheep", 10}, {"wheat", 10}, {"ore", 10}};
    Player *player2 = new Player("player2", CYAN);
    player1->addResources(resources);
    auto *originalCinBuffer = std::cin.rdbuf(iss.rdbuf());
    GameManager gameManager({*player1, *player2});
    gameManager.startGame();
    std::cout << "\n";

    while (!gameManager.checkWinCondition())
    {
        gameManager.play();
        break;
    }
    delete player1;
    delete player2;
    std::cin.rdbuf(originalCinBuffer);
}
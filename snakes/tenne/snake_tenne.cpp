#include "snake_tenne.h"
#include "battlesnake/rules/royale_ruleset.h"

#include <iostream>
#include <random>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace battlesnake::rules;
using namespace battlesnake::interface;

void remove_death_moves(const GameState &state, std::vector<Move> &moves);

Customization SnakeRandom::GetCustomization()
{
    std::cout << "Customization" << std::endl;

    return Customization{
        .color = "#b83700",
        .head = "scarf",
        .tail = "bolt",
        .author = "Robert Hammond"};
};

void SnakeRandom::Start(const GameState &game_state)
{
    std::cout << "Start: " << game_state.game.id << std::endl;
};

void SnakeRandom::End(const GameState &game_state)
{
    std::cout << "End: " << game_state.game.id << std::endl;
};

Battlesnake::MoveResponse SnakeRandom::Move(const GameState &game_state)
{
    std::vector<battlesnake::rules::Move> possible_moves{
        Move::Left,
        Move::Right,
        Move::Up,
        Move::Down,
    };

    remove_death_moves(game_state, possible_moves);

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, possible_moves.size() - 1);

    Battlesnake::MoveResponse result{
        .move = possible_moves[distribution(generator)],
    };

    std::cout << "Move: " << game_state.game.id << " turn " << game_state.turn
              << "  -  " << result.move << std::endl;
    return result;
};

void remove_death_moves(const GameState &state, std::vector<Move> &moves) {
    RoyaleRuleset rules;
    std::unordered_map<SnakeId, Move> move_map;
    for (Move &m : moves) {
        move_map[state.you.id] = m;
        BoardState next = rules.CreateNextBoardState(state.board, move_map, state.turn);
        std::cout << next.snakes[0].IsEliminated() << std::endl;
    }
}
// engine/types.h
#pragma once

// Tipos básicos que usa el tablero y los resultados de turno
enum class TileType { Empty, Player, Enemy, Chest, Tavern };

struct Tile {
    TileType type = TileType::Empty;
};

enum class TurnResult {
    Moved,
    EnemyDefeated,
    PlayerDefeated,
    ChestOpened,
    TavernRest
};

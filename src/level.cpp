//
// Created by chiar on 20/08/2022.
#include "../include/level.hpp"
#include "gui.hpp"
#include "stattome.hpp"
#include "equippable.hpp"
#include "enemy_type.hpp"
#include <cstdlib>
#include <sstream>

#define CORRIDOR_TRIES      30
#define TTL_MAX             10

namespace SpecialRooms {
    enum Type {
        LIBRARY,
        LAST_TYPE
    };
}

Level::Level(Level* parent) {
    Room r;

    this->prev = parent;
    this->next = NULL;

    if (this->prev)
        this->depth = this->prev->depth + 1;
    else
        this->depth = 1;

    //Blank everything
    for (int e = 0; e < MAP_H; ++e) {
        for (int i = 0; i < MAP_W; ++i) {
            this->tiles[i][e] = Tile(false, WALL_CHAR);
        }
    }

    // Find all enemies suitable for this depth
    if (parent)
        this->maximal_enemy = parent->maximal_enemy;
    else
        this->maximal_enemy = 0;
    while ((&EnemyTypeList[this->maximal_enemy])->Level <= this->depth &&
           this->maximal_enemy < LENGTH(EnemyTypeList)) {
        this->maximal_enemy++;
    }

    r.w = (rand() % 15) + 5;
    r.h = (rand() % 5) + 5;
    r.x = rand() % (MAP_W - r.w - 2) + 1;
    r.y = rand() % (MAP_H - r.h - 2) + 1;

    this->stairs_up.x = r.x + rand() % (r.w - 2) + 1;
    this->stairs_up.y = r.y + rand() % (r.h - 2) + 1;
    this->stairs_down.x = -1;   //While this is -1 it means we haven't placed it

    this->ApplyRoom(&r, true);
}

void
Level::ApplyRoom(Room * const r, bool isFirstRoom) {
    Corridor c;
    Room r_child;
    int exits;
    Tile *t;

    exits = 0;

    //Floor
    for (int e = 0; e < r->h; ++e) {
        for (int i = 0; i < r->w; ++i) {
            this->tiles[ i + r->x ][ e + r->y ].setTileType(FLOOR_CHAR);
        }
    }

    if (!isFirstRoom) {                 // Don't put any stuff in first room
        if (rand() % 100 < 1)
            this->MakeSpecialRoom(r);
        else {
            if (rand() % 100 < 5)
                this->AddPillars(r);

            if (rand() % 100 < 20)
                this->AddGold(r);

            if (rand() % 100 < 20)
                this->AddPotion(r);

            if (rand() % 100 < 20)
                this->AddEquippable(r);

            if (rand() % 100 < 80)
                this->EnemySpawn(r);
        }
    }

    //Handle recursively adding children
    for (int i = 0; i < CORRIDOR_TRIES; ++i) {
        c = this->FindRoomCorridorChild(r);
        if (!this->CorridorFits(&c))
            continue;
        r_child = this->RoomFromCorridor(&c);
        if (!this->RoomFits(&r_child))
            continue;

        exits++;
        this->ApplyCorridor(&c);
        this->ApplyRoom(&r_child, false);
    }

    if (this->stairs_down.x == -1 && exits == 0) { // We need to place stairs
        do {
            this->stairs_down.x = r->x + rand() % (r->w - 2) + 1;
            this->stairs_down.y = r->y + rand() % (r->h - 2) + 1;
            t = &this->tiles[this->stairs_down.x][this->stairs_down.y];
        } while (t->getTileType() != FLOOR_CHAR);
    }
}

bool
Level::CorridorFits(Corridor const * const c) {
    Rect r;

    if (c->pos.x <= 1 || c->pos.y <= 1)
        return false;
    if (c->pos.x + c->pos.w >= MAP_W)
        return false;
    if (c->pos.y + c->pos.h >= MAP_H)
        return false;

    r = c->pos;
    if (c->direction == Direction::EAST)
        r.x ++;
    else if (c->direction == Direction::SOUTH)
        r.y ++;

    for (int e = MAX(r.y - 1, 0); e <= r.y + r.h; ++e) {
        for (int i = MAX(r.x - 1, 0); i <= r.x + r.w; ++i) {
            if (this->tiles[i][e].getTileType() == FLOOR_CHAR)
                return false;
        }
    }

    return true;
}

bool
Level::RoomFits(Room const * const r) {
    if (r->x <= 0 || r->y <= 0)
        return false;
    if (r->x + r->w >= MAP_W)
        return false;
    if (r->y + r->h >= MAP_H)
        return false;

    for (int e = MAX(r->y - 1, 0); e <= r->y + r->h; ++e) {
        for (int i = MAX(r->x - 1, 0); i <= r->x + r->w; ++i) {
            if (this->tiles[i][e].getTileType() == FLOOR_CHAR)
                return false;
        }
    }

    return true;
}

void
Level::ApplyCorridor(Corridor const * const c) {
    Rect r;
    Direction::Type d;

    r = c->pos;
    d = c->direction;

    this->tiles[r.x][r.y].setTileType(CLOSED_DOOR_CHAR);
    this->tiles[r.x + r.w][r.y + r.h].setTileType(CLOSED_DOOR_CHAR);
    if (d == Direction::EAST || d == Direction::WEST) {
        for (int i = 1; i < r.w; ++i)
            this->tiles[i + r.x][r.y].setTileType(FLOOR_CHAR);
    }
    else {
        for (int i = 1; i < r.h; ++i)
            this->tiles[r.x][i + r.y].setTileType(FLOOR_CHAR);
    }
}

Room
Level::RoomFromCorridor(Corridor *c) {
    Room r;
    r.w = (rand() % 15) + 5;
    r.h = (rand() % 5) + 5;

    // Only add-sized rooms
    if (r.w % 2 == 0)
        r.w++;
    if (r.h % 2 == 0)
        r.h++;

    if (c->direction == Direction::NORTH) {
        r.x = c->pos.x - rand() % r.w;
        r.y = c->pos.y - r.h;
    }
    else if (c->direction == Direction::SOUTH) {
        r.x = c->pos.x - rand() % r.w;
        r.y = c->pos.y + c->pos.h + 1;
    }
    else if (c->direction == Direction::EAST) {
        r.x = c->pos.x + c->pos.w + 1;
        r.y = c->pos.y - rand() % r.h;
    }
    else { //WEST
        r.x = c->pos.x - r.w;
        r.y = c->pos.y - rand() % r.h;
    }

    return r;
}

Corridor
Level::FindRoomCorridorChild(Room *r) {
    Corridor c;

    if (rand() % 2) { //NORTH OR SOUTH
        c.pos.w = 0;
        c.pos.h = ((rand() % 2) + 1) * 3;
        c.pos.x = r->x + rand() % r->w;
        if (rand() % 2) { //NORTH
            c.direction = Direction::NORTH;
            c.pos.y = r->y - 1 - c.pos.h;
        }
        else { //SOUTH
            c.direction = Direction::SOUTH;
            c.pos.y = r->y + r->h;
        }
    }
    else { //EAST OR WEST
        c.pos.h = 0;
        c.pos.w = ((rand() % 3) + 1) * 3;
        c.pos.y = r->y + rand() % r->h;
        if (rand() % 2) { // WEST
            c.direction = Direction::WEST;
            c.pos.x = r->x - 1 - c.pos.w;
        }
        else { //EAST
            c.direction = Direction::EAST;
            c.pos.x = r->x + r->w;
        }
    }

    return c;
}

bool
Level::TileIsVisible(Point p) {
    return this->tiles[p.x][p.y].isVisible;
}

void
Level::ConditionallyShowObject(Point p, char c, int col) {
    if (!GUI::isOnScreen(p))
        return;
    if (!this->TileIsVisible(p))
        return;
    attron(COLOR_PAIR(col));
    GUI::DrawObjectRelative(p, c);
    attroff(COLOR_PAIR(col));
}

void
Level::RevealSight(Point p, int distance) {
    DoSightBeam(Direction::NORTH, p.x, p.y, distance);
    DoSightBeam(Direction::SOUTH, p.x, p.y, distance);
    DoSightBeam(Direction::EAST, p.x, p.y, distance);
    DoSightBeam(Direction::WEST, p.x, p.y, distance);
}

void
Level::DoSightBeam(Direction::Type d, int x, int y, float ttl) {
    Tile *t;

    if (ttl < 0)
        return;
    t = &this->tiles[x][y];
    t->isVisible = true;
    if (!t->isSeeThrough())
        return;

    if (d == Direction::NORTH) {
        DoSightBeam(Direction::NW, x - 1, y - 1, ttl - 1.41);
        DoSightBeam(Direction::NORTH, x, y - 1, ttl - 1);
        DoSightBeam(Direction::NE, x + 1, y - 1, ttl - 1.41);
    }
    else if (d == Direction::SOUTH) {
        DoSightBeam(Direction::SW, x - 1, y + 1, ttl - 1.41);
        DoSightBeam(Direction::SOUTH, x, y + 1, ttl - 1);
        DoSightBeam(Direction::SE, x + 1, y + 1, ttl - 1.41);
    }
    else if (d == Direction::EAST) {
        DoSightBeam(Direction::NE, x + 1, y - 1, ttl - 1.41);
        DoSightBeam(Direction::EAST, x + 1, y, ttl - 1);
        DoSightBeam(Direction::SE, x + 1, y + 1, ttl - 1.41);
    }
    else if (d == Direction::WEST) {
        DoSightBeam(Direction::NW, x - 1, y - 1, ttl - 1.41);
        DoSightBeam(Direction::WEST, x - 1, y, ttl - 1);
        DoSightBeam(Direction::SW, x - 1, y + 1, ttl - 1.41);
    }
    else if (d == Direction::NW)
        DoSightBeam(Direction::NW, x - 1, y - 1, ttl - 1.41);
    else if (d == Direction::NE)
        DoSightBeam(Direction::NE, x + 1, y - 1, ttl - 1.41);
    else if (d == Direction::SW)
        DoSightBeam(Direction::SW, x - 1, y + 1, ttl - 1.41);
    else if (d == Direction::SE)
        DoSightBeam(Direction::SE, x + 1, y + 1, ttl - 1.41);
}

void
Level::AddGold(Rect *r) {
    Treasure *tres;
    int quantity;
    int TTL;
    Point p;

    quantity = rand() % (this->depth * 10) + 1;

    TTL = 5;
    do {
        p.x = r->x + rand() % r->w;
        p.y = r->y + rand() % r->h;
        if (TTL-- <= 0)
            break;
    } while (this->GetItem(p) || !this->tiles[p.x][p.y].isPassable());

    if (TTL == 0)
        return;

    tres = new Treasure(quantity);
    tres->SetPosition(p.x, p.y);

    this->items.push_back((Item*) tres);

    //Chance of a chain happening
    if (rand() % 100 <= 10)
        this->AddGold(r);
}

void
Level::AddPotion(Rect *r) {
    Potion *potion;
    Potion::Category category;
    int potency;
    int TTL;
    Point p;

    category = (Potion::Category)(rand() % Potion::LAST_CATEGORY);

    //Determine potency. Deeper = stronger
    if (this->depth >= 100)
        potency = Potion::LAST_POTENCY;
    else {
        for (potency = 0; potency < (int)Potion::LAST_POTENCY - 1; potency ++) {
            if (rand() % 100 + this->depth <= 70)
                break;
        }
    }

    TTL = 0;
    do {
        p.x = r->x + rand() % r->w;
        p.y = r->y + rand() % r->h;
        if (TTL++ >= TTL_MAX)
            break;
    } while (this->GetItem(p) || !this->tiles[p.x][p.y].isPassable());

    if (TTL >= TTL_MAX) // We're out of space
        return;

    potion = new Potion((Potion::Potency) potency, category);
    potion->SetPosition(p.x, p.y);

    this->items.push_back((Item*) potion);

    //Chance of a chain happening
    if (rand() % 100 <= 10)
        this->AddPotion(r);
}


std::string
Level::DescriptionOfTile(Point p, Game *g) {
    Tile *t;
    std::stringstream ss;
    std::string s;
    static std::string unknown = "Unexplored space";
    static std::string prefix = "YOU SEE: ";

    if (p.x > MAP_W)
        return unknown;
    if (p.y > MAP_H)
        return unknown;

    t = &this->tiles[p.x][p.y];

    //Basic beginning part
    ss << prefix;

    // Tile information
    if (!t->isVisible)
        return unknown;
    else if (p == this->stairs_up)
        ss << "Stairs up";
    else if (p == this->stairs_down)
        ss << "Stairs down";
    else if (t->getTileType() == FLOOR_CHAR)
        ss << "Granite floor";
    else if (t->getTileType() == WALL_CHAR)
        return prefix + "A granite wall";
    else if (t->getTileType() == PILLAR_CHAR)
        return prefix + "A granite column";
    else if (t->getTileType() == CLOSED_DOOR_CHAR )
        ss << "Closed door";
    else if (t->getTileType() == OPEN_DOOR_CHAR)
        ss << "Open door";
    else if (t->getTileType() == OPEN_DOOR_CHAR)
        ss << "Open door";

    //Character
    if (p == g->character->pos) {
        ss << " and a " << g->character->GetRaceString() << " ";
        ss << g->character->GetClassString();
    }
    else { // Check for enemies
        for (std::list<Enemy>::iterator it = this->enemies.begin();
             it != this->enemies.end(); it++) {
            if (it->pos == p) {
                ss << " and " << it->Description();
                break;
            }
        }
    }

    //Items
    for (std::list<Item*>::iterator it = this->items.begin();
         it != this->items.end(); it++) {
        if (p == (*it)->pos) {
            ss << " and " << (*it)->GetName();
        }
    }

    s = ss.str();

    if (s.length() > 0)
        return s;

    return "SOMETHING WENT WRONG";
}

void
Level::EnemySpawn(Rect *r) {
    EnemyType *et;
    Enemy e;
    int type;
    int total_level;
    int TTL;

    total_level = rand() % this->depth + 3;

    while (total_level > 0) {
        type = rand() % this->maximal_enemy;

        et = &EnemyTypeList[type];
        e = Enemy(et);
        TTL = 0;
        do {
            e.pos.x = r->x + rand() % r->w;
            e.pos.y = r->y + rand() % r->h;
            if (TTL++ >= TTL_MAX)   //we're probably out of space
                break;
        } while (GetEnemy(e.pos) || e.pos == this->stairs_up
                 || !this->tiles[e.pos.x][e.pos.y].isPassable());

        if (TTL >= TTL_MAX) // Out of space
            return;

        if (e.pos == this->stairs_up)
            continue;

        total_level -= et->Level;
        this->enemies.push_back(e);
    }
}

void
Level::RemoveEnemy(Enemy *e) {
    for (std::list<Enemy>::iterator it = this->enemies.begin();
         it != this->enemies.end(); it++) {
        if (&*it == e) {
            this->enemies.erase(it);
            return;
        }
    }

    GUI::Alert("Error removing enemy from list. That's bad.");
}

void
Level::GiveEnemiesTurns(Character *c, int n) {
    for (std::list<Enemy>::iterator it = this->enemies.begin();
         it != this->enemies.end(); it++) {

        //For activating monsters
        if (!it->isActive && CalculateDistance(it->pos, c->pos) <=
                             it->parent_type->baseSIGHT) {
            if (this->CanSee(it->pos, c->pos))
                it->isActive = true;
        }

        if (it->isActive)
            it->mv_energy += c->curMV * n;
        if (it->mv_energy >= it->parent_type->baseMV)
            this->EnemyAdvance(&*it, c);
    }
    GUI::DoRedraw();
}

void
Level::EnemyAdvance(Enemy *e, Character *c) {
    Point target;
    Direction::Type tries[3];
    Tile *t;

    while(e->mv_energy >= e->parent_type->baseMV) {
        e->mv_energy -= e->parent_type->baseMV;

        //Target x
        if (e->pos.x > c->pos.x) {
            tries[0] = Direction::WEST;
            tries[1] = Direction::WEST;
        }
        else if (e->pos.x < c->pos.x) {
            tries[0] = Direction::EAST;
            tries[1] = Direction::EAST;
        }
        else {
            tries[0] = Direction::LAST_DIRECTION;
            if (rand() % 2)
                tries[1] = Direction::EAST;
            else
                tries[1] = Direction::WEST;
        }

        //Target y
        if (e->pos.y > c->pos.y) {
            tries[0] = MoveCardinal(Direction::NORTH, tries[0]);
            if (ABS(e->pos.x - c->pos.x) < ABS(e->pos.y - c->pos.y)) {
                tries[2] = tries[1];
                tries[1] = Direction::NORTH;
            }
            else
                tries[2] = Direction::NORTH;
        }
        else if (e->pos.y < c->pos.y) {
            tries[0] = MoveCardinal(Direction::SOUTH, tries[0]);
            if (ABS(e->pos.x - c->pos.x) < ABS(e->pos.y - c->pos.y)) {
                tries[2] = tries[1];
                tries[1] = Direction::SOUTH;
            }
            else
                tries[2] = Direction::SOUTH;
        }
        else
            tries[2] = (Direction::Type)( rand() % Direction::LAST_DIRECTION );

        if (tries[0] == Direction::LAST_DIRECTION)
            tries[0] = (Direction::Type)( rand() % Direction::LAST_DIRECTION );
        if (tries[0] == tries[1])
            tries[1] = (Direction::Type)( rand() % Direction::LAST_DIRECTION );

        for (int i = 0; i < 3; ++i) {
            target = GetRelativePoint(tries[i], e->pos);

            if (target == c->pos) {
                e->Attack(c);
                return;
            }

            if (this->GetEnemy(target)) // Can't move into an occupied space
                continue;

            t = &this->tiles[target.x][target.y];

            if (t->getTileType() == FLOOR_CHAR
                || t->getTileType() == OPEN_DOOR_CHAR) {
                e->pos = target;
                return;
            }
        }
    }
}

Enemy*
Level::GetEnemy(Point p) {
    for (std::list<Enemy>::iterator it = this->enemies.begin();
         it != this->enemies.end(); it++) {
        if (it->pos == p)
            return &*it;
    }
    return NULL;
}

Item *
Level::GetItem(Point p) {
    for (std::list<Item*>::iterator it = this->items.begin();
         it != this->items.end(); it++) {
        if ((*it)->pos == p)
            return &**it;
    }
    return NULL;
}

void
Level::MakeSpecialRoom(Rect *r) {
    static char const * const library_text[] = {
            "You enter a library whose mouldy shelves are overflowing. In the centre of",
            "the room sits an important-looking book upon a pedestal.",
            NULL};

    int i;
    Item *item;

    i = rand() % SpecialRooms::LAST_TYPE;

    switch (i) {
        case SpecialRooms::LIBRARY:
            this->AddPillars(r);
            this->AddRoomText(r, library_text);
            item = (Item*) new StatTome(this->depth);
            item->pos.x = r->x + r->w / 2;
            item->pos.y = r->y + r->h / 2;
            this->items.push_back(item);
            break;
        case SpecialRooms::LAST_TYPE:
        default:
            GUI::Alert("Error allocating a special room.");
    }
}

void
Level::AddRoomText(Rect *r, char const * const * const msg) {
    RoomText rt;
    rt.pos = *r;
    rt.text = msg;
    rt.seen = false;
    this->roomtexts.push_back(rt);
}

void
Level::AddPillars(Rect *r) {
    Point p;

    p.x = r->x + 1;
    p.y = r->y + 1;
    this->tiles[p.x][p.y].setTileType(PILLAR_CHAR);
    p.y = r->y + r->h - 2;
    this->tiles[p.x][p.y].setTileType(PILLAR_CHAR);
    p.x = r->x + r->w - 2;
    this->tiles[p.x][p.y].setTileType(PILLAR_CHAR);
    p.y = r->y + 1;
    this->tiles[p.x][p.y].setTileType(PILLAR_CHAR);
}

void
Level::CheckForRoomText(Character *c) {
    if (this->roomtexts.size() == 0)
        return;

    for (std::vector<RoomText>::iterator it = this->roomtexts.begin();
         it != this->roomtexts.end(); it++) {
        if (c->pos.x < it->pos.x || c->pos.x >= it->pos.x + it->pos.w)
            continue;
        if (c->pos.y < it->pos.y || c->pos.y >= it->pos.y + it->pos.h)
            continue;
        if (it->seen)
            continue;

        it->seen = true;
        GUI::Alert2(it->text);
    }
}

void
Level::AddEquippable(Rect *r) {
    Equippable *equippable;
    Equippable::Category category;
    int potency;
    int TTL;
    Point p;

    category = (Equippable::Category)(rand() % Equippable::LAST_CATEGORY);

    potency = rand() % this->depth + 1;

    TTL = 0;
    do {
        p.x = r->x + rand() % r->w;
        p.y = r->y + rand() % r->h;
        if (TTL++ >= TTL_MAX)
            break;
    } while (this->GetItem(p) || !this->tiles[p.x][p.y].isPassable());

    if (TTL >= TTL_MAX) // We're probably out of space
        return;

    equippable = new Equippable(category, potency);
    equippable->SetPosition(p.x, p.y);

    this->items.push_back((Item*) equippable);

    //Chance of a chain happening
    if (rand() % 100 <= 10)
        this->AddEquippable(r);
}

void
Level::RevealAll(void) {
    for (int e = 0; e < MAP_H; ++e) {
        for (int i = 0; i < MAP_W; ++i) {
            this->tiles[i][e].isVisible = true;
        }
    }
}

bool //Really rudamentary
Level::CanSee(Point p1, Point p2) {
    Direction::Type d;
    Tile *t;

    while (p1.x != p2.x || p1.y != p2.y) {
        t = &this->tiles[p1.x][p1.y];
        if (!t->isSeeThrough())
            return false;
        d = DirectionFromAToB(p1, p2);
        p1 = GetRelativePoint(d, p1);
    }
    return true;
}

void
Level::ClearObstacles(void) {
    for (int e = 0; e < MAP_H; ++e)
        for (int i = 0; i < MAP_W; ++i)
            this->tiles[i][e].setTileType(FLOOR_CHAR);
}

Level::~Level(void) {
    Item *item;
    for (std::list<Item*>::iterator it = this->items.begin();
         it != this->items.end(); it++) {
        item = &**it;
        switch (item->type) {
            case Item::POTION:
                delete (Potion*) item;
                break;
            case Item::STAT_TOME:
                delete (StatTome*) item;
                break;
            case Item::TREASURE_T:
                delete (Treasure*) item;
                break;
            case Item::EQUIPPABLE:
                delete (Equippable*) item;
                break;
            case Item::GENERIC:
            case Item::LAST_TYPE:
            default:
                delete item;
                break;
        }
    }
    if (this->next)
        delete this->next;
}

//

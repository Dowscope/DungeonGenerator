#include "World.h"

World::World(int aWidth, int aHeight):
    _width(aWidth), _height(aHeight)
{
    _initializeTiles();
    _generateMap();
}

void World::_initializeTiles(){
    for (int y = 0; y < _height; y++)
    {
        for (int x = 0; x < _width; x++)
        {
            Tile *t = new Tile(x, y);
            _tiles.push_back(t);
        }
        
    }
    
    std::cout << "Total tiles initialized: " << _tiles.size() << std::endl;
}

void World::_generateMap(){
    for (int i = 0; i < MAX_ROOMS; i++)
    {
        int x = rand() % _width;
        int y = rand() % _height;
        int w = MIN_ROOM_SIZE + rand() % MAX_ROOM_SIZE;
        int h = MIN_ROOM_SIZE + rand() % MAX_ROOM_SIZE;

        if (x >= _width - w) { x = x - w; }
        if (y >= _height - h) { y = y - h; }

        Room *r = new Room(x, y, w, h);
        if ( !_checkForOverlap(r)){
            _rooms.push_back(r);

            for (int row = y; row < y + h; row++)
            {
                for (int col = x; col < x + w; col++)
                {
                    Tile *t = getTileAt(col, row);
                    t->resetWalls(false);

                    if (row == 0){ t->setWallAt(0, true); }
                    if (col == 0){ t->setWallAt(3, true); }
                    if (row == y + h - 1){ t->setWallAt(2, true);}
                    if (col == x + w - 1){ t->setWallAt(1, true);}

                    t->Visited();
                    t->makeRoomTile();
                }
            }
        }
    }  

    // Make Maze
    // Start at (0,0) for time being.
    Tile* t = getTileAt(0,0);
    t->Visited();
    _mazeStack.push_back(t);

    _walkMaze();
}

void World::_walkMaze(){
    while(!_mazeStack.empty()){
        Tile* t = _mazeStack.back();
        _mazeStack.pop_back();

        t->isCurrent = true;
        Tile* next = _checkNeighbours(t);

        if (next != nullptr){
            _mazeStack.push_back(t);
            _removeWalls(t, next);
            next->Visited();
            _mazeStack.push_back(next);
        }
    }
}

Tile* World::_checkNeighbours(Tile* t){
    std::vector<Tile*> neighbours;
    if (t->getY() > 0) {
        Tile *next = getTileAt(t->getX(), t->getY() - 1);
        if (next && !next->isVisited()){
            neighbours.push_back(next);
        }
    }
    if (t->getX() < _width - 1) {
        Tile *next = getTileAt(t->getX() + 1, t->getY());
        if (next && !next->isVisited()){
            neighbours.push_back(next);
        }
    }
    if (t->getY() < _height - 1) {
        Tile *next = getTileAt(t->getX(), t->getY() + 1);
        if (next && !next->isVisited()){
            neighbours.push_back(next);
        }
    }
    if (t->getX() > 0) {
        Tile *next = getTileAt(t->getX() - 1, t->getY());
        if (next && !next->isVisited()){
            neighbours.push_back(next);
        }
    }
    if (neighbours.empty()){ return nullptr;}

    int random = rand() % neighbours.size();
    return neighbours[random];
}

void World::_removeWalls(Tile* t, Tile* nb){
    
    int x = nb->getX() - t->getX();
    int y = nb->getY() - t->getY();

    if (x != 0){
        if (x == 1){
            t->setWallAt(1, false);
            nb->setWallAt(3, false);
        }
        if (x == -1){
            nb->setWallAt(1, false);
            t->setWallAt(3, false);
        }
    }
    else {
        if (y == 1){
            t->setWallAt(2, false);
            nb->setWallAt(0, false);
        }
        if (y == -1){
            nb->setWallAt(2, false);
            t->setWallAt(0, false);
        }
    }
}

bool World::_checkForOverlap(Room *r){

    if (_rooms.empty() == true){
        return false;
    }
    bool checker = false;

    for (int i = 0; i < _rooms.size(); i++){
        Room *room = _rooms[i];
        if (    r->getX() + r->getW() < room->getX() || 
                r->getY() + r->getH() < room->getY() || 
                r->getX() > room->getX() + room->getW() ||
                r->getY() > room->getY() + room->getH() )
        {

        }
        else {
            checker = true;
        }
    }

    return checker;
}

Tile* World::getTileAt(const int x, const int y){
    for (int i = 0; i < _tiles.size(); i++)
    {
        if (_tiles[i]->getX() == x && _tiles[i]->getY() == y){
            return _tiles[i];
        }
    }
    
    return nullptr;
}


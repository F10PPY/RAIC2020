#include "ai.h"

bool ai::scanForNearestRes(Coord from,Coord &to)
{
    //   int max=map_len-start_tile.x<map_len-start_tile.y?5:6;
    for(int i=1;i<map_len;i++)
    {
        if(from.x-i>=0)
        {
            if(tiles[from.x-i][static_cast<int>(from.y)].res_amount!=0)
                to= {static_cast<char>(from.x-i),from.y};
            return true;
        }
        if(from.y-i>=0)
        {
            if(tiles[static_cast<int>(from.x)][from.y-i].res_amount!=0)
                to={from.x,static_cast<char>(from.y-i)};
            return true;
        }
        if(from.x+i<map_len)
        {
            if(tiles[from.x+i][static_cast<int>(from.y)].res_amount!=0)
                to={static_cast<char>(from.x+i),from.y};
            return true;
        }
        if(from.y+i<map_len)
        {
            if(tiles[static_cast<int>(from.x)][from.y+i].res_amount!=0)
                to= {from.x,static_cast<char>(from.y+i)};
            return true;
        }

        if(from.x-i>=0&&from.y-i>=0)
        {
            if(tiles[from.x-i][from.y-i].res_amount!=0)
                to= {static_cast<char>(from.x-i),static_cast<char>(from.y-i)};
            return true;
        }
        if(from.x-i>=0&&from.y+i<map_len)
        {
            if(tiles[from.x-i][from.y+i].res_amount!=0)
                to= {static_cast<char>(from.x-i),static_cast<char>(from.y+i)};
            return true;
        }
        if(from.x+i<map_len&&from.y-i>=0)
        {
            if(tiles[from.x+i][from.y-i].res_amount!=0)
                to= {static_cast<char>(from.x+i),static_cast<char>(from.y-i)};
            return true;
        }
        if(from.x+i<map_len&&from.y+i<map_len)
        {
            if(tiles[from.x+i][from.y+i].res_amount!=0)
                to= {static_cast<char>(from.x+i),static_cast<char>(from.y+i)};
            return true;
        }
    }
    return false;
}
bool ai::scanForNearestToheal(Coord from,Coord &dest,int len, int &target_id)
{
    for(int i=1;i<len;i++)
    {
        if(from.x-i>=0)
        {
            if(tiles[from.x-i][from.y].type==EntityType::RANGED_UNIT&&my_ranged[tiles[from.x-i][from.y].id].hp<ent_hp[EntityType::RANGED_UNIT])
            {
                dest={from.x-i,from.y};
                target_id=tiles[from.x-i][from.y].id;
                return true;
            }
        }
        if(from.y-i>=0)
        {
            if(tiles[from.x][from.y-i].type==EntityType::RANGED_UNIT&&my_ranged[tiles[from.x][from.y-i].id].hp<ent_hp[EntityType::RANGED_UNIT])
            {
                dest={from.x,from.y-i};
                target_id=tiles[from.x][from.y-i].id;
                return true;
            }
        }
        if(from.x+i<map_len)
        {
            if(tiles[from.x+i][from.y].type==EntityType::RANGED_UNIT&&my_ranged[tiles[from.x+i][from.y].id].hp<ent_hp[EntityType::RANGED_UNIT])
            {
                dest={from.x+i,from.y};
                target_id=tiles[from.x+i][from.y].id;
                return true;
            }

        }
        if(from.y+i<map_len)
        {
            if(tiles[from.x][from.y+i].type==EntityType::RANGED_UNIT&&my_ranged[tiles[from.x][from.y+i].id].hp<ent_hp[EntityType::RANGED_UNIT])
            {
                dest={from.x,from.y+i};
                target_id=tiles[from.x][from.y+i].id;
                return true;
            }
        }
        if(from.x-i>=0&&from.y-i>=0)
        {
            if(tiles[from.x-i][from.y-i].type==EntityType::RANGED_UNIT&&my_ranged[tiles[from.x-i][from.y-i].id].hp<ent_hp[EntityType::RANGED_UNIT])
            {
                dest={from.x-i,from.y-i};
                target_id=tiles[from.x-i][from.y-i].id;
                return true;
            }
        }
        if(from.x-i>=0&&from.y+i<map_len)
        {
            if(tiles[from.x-i][from.y+i].type==EntityType::RANGED_UNIT&&my_ranged[tiles[from.x-i][from.y+i].id].hp<ent_hp[EntityType::RANGED_UNIT])
            {
                dest={from.x-i,from.y+i};
                target_id=tiles[from.x-i][from.y+i].id;
                return true;
            }
        }
        if(from.x+i<map_len&&from.y-i>=0)
        {
            if(tiles[from.x+i][from.y-i].type==EntityType::RANGED_UNIT&&my_ranged[tiles[from.x+i][from.y-i].id].hp<ent_hp[EntityType::RANGED_UNIT])
            {
                dest={from.x+i,from.y-i};
                target_id=tiles[from.x+i][from.y-i].id;
                return true;
            }
        }
        if(from.x+i<map_len&&from.y+i<map_len)
        {
            if(tiles[from.x+i][from.y+i].type==EntityType::RANGED_UNIT&&my_ranged[tiles[from.x+i][from.y+i].id].hp<ent_hp[EntityType::RANGED_UNIT])
            {
                dest={from.x+i,from.y+i};
                target_id=tiles[from.x+i][from.y+i].id;
                return true;
            }
        }
    }
    return false;
}

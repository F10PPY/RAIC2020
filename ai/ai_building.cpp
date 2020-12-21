#include "ai.h"

bool ai::buildHouse()
{
    int best_dist=INT32_MAX;
    int dist=INT32_MAX;
    int best_id;
    int best_pos_n;
    for(size_t pos_n=0;pos_n<house_slots.size();pos_n++)
    {
        if(isFreeToBuild({house_slots[pos_n].x,house_slots[pos_n].y},EntityType::HOUSE))
        {
            for(auto &[id,val]:my_builders)
            {
                if(val.tick_relax_start+max_relax_ticks>=tick_current)continue;
                if(unlikely(val.state>BuilderState::MINING))continue;
                dist=calcDist(val.pos,house_slots[pos_n]);
                if(dist<best_dist)
                {
                    best_dist=dist;
                    best_id=id;
                    best_pos_n=pos_n;
                }
            }
        }
    }
    if(dist!=INT32_MAX)
    {
        my_builders[best_id].state=BuilderState::MOVINGTOBUILD;
        my_builders[best_id].trace.clear();
        my_builders[best_id].target={house_slots[best_pos_n].x+1,house_slots[best_pos_n].y+1};
        my_builders[best_id].target_type=EntityType::HOUSE;
        my_builders[best_id].tick_task_start=tick_current;
        my_builders[best_id].max_trybuild_ticks=calcDist(my_builders[best_id].pos,my_builders[best_id].target)*coef_trybuild;

        my_builders[best_id].pf_move_to=new array<array<int,map_len>,map_len>{};
        my_houses_prod.emplace(std::piecewise_construct, std::forward_as_tuple(best_id),std::forward_as_tuple(InProd({ my_builders[best_id].pf_move_to,house_slots[best_pos_n]})));

        pfFillLinear({house_slots[best_pos_n].x+1,house_slots[best_pos_n].y+1},80,* my_builders[best_id].pf_move_to,map_len);

        res_reserved+=init_price[EntityType::HOUSE];
        return true;
    }
    return false;

}
bool ai::buildTurret(Coord dest)
{
    int best_dist=INT32_MAX;
    int dist=INT32_MAX;
    int best_id;
    if(isFreeToBuild({dest.x,dest.y},EntityType::TURRET))
    {
        for(auto &[id,val]:my_builders)
        {
            if(val.tick_relax_start+max_relax_ticks>=tick_current)continue;
            if(unlikely(val.state>BuilderState::MINING))continue;
            dist=calcDist(val.pos,{dest.x,dest.y});
            if(dist<best_dist)
            {
                best_dist=dist;
                best_id=id;
            }
        }
    }
    if(dist!=INT32_MAX)
    {
        my_builders[best_id].state=BuilderState::MOVINGTOBUILD;
        my_builders[best_id].trace.clear();
        my_builders[best_id].target={dest.x,dest.y};
        my_builders[best_id].target_type=EntityType::TURRET;
        my_builders[best_id].tick_task_start=tick_current;
        my_builders[best_id].max_trybuild_ticks=calcDist(my_builders[best_id].pos,my_builders[best_id].target)*coef_trybuild;

        my_builders[best_id].pf_move_to=new array<array<int,map_len>,map_len>{};
        my_turrets_prod.emplace(std::piecewise_construct, std::forward_as_tuple(best_id),std::forward_as_tuple(InProd({ my_builders[best_id].pf_move_to,{dest.x,dest.y}})));

        pfFillLinear({dest.x,dest.y},80,* my_builders[best_id].pf_move_to,map_len);
        res_reserved+=init_price[EntityType::TURRET];
        return true;
    }
    return false;

}
bool ai::buildRanged(Coord dest)
{
    int best_dist=INT32_MAX;
    int dist=INT32_MAX;
    int best_id;

    for(auto &[id,val]:my_builders)
    {
        if(val.tick_relax_start+max_relax_ticks>=tick_current)continue;
        if(unlikely(val.state>BuilderState::MINING))continue;
        dist=calcDist(val.pos,{dest.x,dest.y});
        if(dist<best_dist)
        {
            best_dist=dist;
            best_id=id;
        }
    }
    if(dist!=INT32_MAX)
    {
        my_builders[best_id].state=BuilderState::MOVINGTOBUILD;
        my_builders[best_id].trace.clear();
        my_builders[best_id].target={dest.x+2,dest.y+2};
        my_builders[best_id].target_type=EntityType::RANGED_BASE;
        my_builders[best_id].tick_task_start=tick_current;
        my_builders[best_id].max_trybuild_ticks=calcDist(my_builders[best_id].pos,my_builders[best_id].target)*coef_trybuild;

        my_builders[best_id].pf_move_to=new array<array<int,map_len>,map_len>{};
        my_ranged_prod.emplace(std::piecewise_construct, std::forward_as_tuple(best_id),std::forward_as_tuple(InProd({ my_builders[best_id].pf_move_to,{dest.x,dest.y}})));

        pfFillLinear({dest.x+2,dest.y+2},80,* my_builders[best_id].pf_move_to,map_len);
        res_reserved+=init_price[EntityType::RANGED_BASE];
        return true;
    }
    return false;
}
void ai::calcRallyPointRanged(Building &building,Coord &dest)
{
    dest={building.pos.x,building.pos.y};
    for(int i=4;i>=0;i--)
    {
        if(pf_init_busy[building.pos.x+i][building.pos.y+5]==0)
        {
            dest.x+=i;
            dest.y+=5;
            return;
        }
        if(pf_init_busy[building.pos.x+5][building.pos.y+i]==0)
        {
            dest.x+=5;
            dest.y+=i;
            return;
        }
    }
}
void ai::calcRallyPointBuilder(Building &building,Coord &dest)
{
    dest={building.pos.x,building.pos.y};
    for(int i=0;i<5;i++)
    {
        if (pf_res[dest.x][dest.y]-pf_init_busy[dest.x][dest.y] < pf_res[building.pos.x-1][building.pos.y+i]-pf_init_busy[dest.x-1][dest.y+i])
        {
            dest={building.pos.x-1,building.pos.y+i};
        }
    }
    for(int i=0;i<5;i++)
    {
        if (pf_res[dest.x][dest.y]-pf_init_busy[dest.x][dest.y] < pf_res[building.pos.x+i][building.pos.y-1]-pf_init_busy[dest.x+i][dest.y-1])
        {
            dest={building.pos.x+i,building.pos.y-1};
        }
    }
    for(int i=0;i<5;i++)
    {
        if (pf_res[dest.x][dest.y]-pf_init_busy[dest.x][dest.y] < pf_res[building.pos.x+i][building.pos.y+5]-pf_init_busy[dest.x+i][dest.y+5])
        {
            dest={building.pos.x+i,building.pos.y+5};
        }
    }
    for(int i=0;i<5;i++)
    {
        if (pf_res[dest.x][dest.y]-pf_init_busy[dest.x][dest.y] < pf_res[building.pos.x+5][building.pos.y+i]-pf_init_busy[dest.x+5][dest.y+i])
        {
            dest={building.pos.x+5,building.pos.y+i};
        }
    }
}




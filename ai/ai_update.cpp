#include "ai.h"
void ai::updateTick(const PlayerView& playerView)
{
    tick_current=playerView.currentTick;
    my_id=playerView.myId;
    fog=playerView.fogOfWar;


    for(auto &it:playerView.players)
    {
        if(it.id==my_id)
        {
            my_res=it.resource;
            my_score=it.score;
        }
    }
    flag_alive=!flag_alive;
    pf_init_busy.fill({});

    for(int i=0;i<map_len_sq;i++)
    {
        tiles[0][i]={};//reset
    }

    for(auto &it:playerView.entities)
    {
        auto &pf_init_busy_ref=pf_init_busy[it.position.x][it.position.y];
        auto &ref= tiles[it.position.x][it.position.y];
        switch (it.entityType)
        {
        case EntityType::RESOURCE:
        {
            ref.type=it.entityType;
            ref.res_amount=it.health;
            ref.id=it.id;
            pf_init_busy_ref=pot_busy_val;
        }
            break;
        case EntityType::BUILDER_UNIT:
        {
            ref.type=it.entityType;
            ref.id=it.id;
            if(*it.playerId.get()==my_id)
            {
                my_builders[it.id].alive=flag_alive;
                my_builders[it.id].pos=it.position;
                my_builders[it.id].hp=it.health;
                pf_init_busy_ref=pot_busy_val;
            }
        }
            break;
        case EntityType::MELEE_UNIT:
        {
            ref.type=it.entityType;
            ref.id=it.id;
            if(*it.playerId.get()==my_id)
            {
                my_melee[it.id].alive=flag_alive;
                my_melee[it.id].pos=it.position;
                my_melee[it.id].hp=it.health;
                pf_init_busy_ref=pot_busy_val;
            }

        }
            break;
        case EntityType::RANGED_UNIT:
        {
//            ref.type=it.entityType;
//            ref.id=it.id;

            if(*it.playerId.get()==my_id)
            {
                ref.type=it.entityType;
                ref.id=it.id;


                my_ranged[it.id].alive=flag_alive;
                my_ranged[it.id].pos=it.position;
                my_ranged[it.id].hp=it.health;
                pf_init_busy_ref=pot_busy_val;
            }
        }
            break;
        case EntityType::BUILDER_BASE:
        {
            for(int i=0;i<ent_len[it.entityType];i++)
            {
                for(int j=0;j<ent_len[it.entityType];j++)
                {
                    tiles[it.position.x+i][it.position.y+j].type=it.entityType;
                    tiles[it.position.x+i][it.position.y+j].id=it.id;
                    pf_init_busy[it.position.x+i][it.position.y+j]=pot_busy_val;
                }
            }
            if(*it.playerId.get()==my_id)
            {
                my_base_builder.tick_reported=tick_current;
                my_base_builder.id=it.id;
                my_base_builder.pos=it.position;
                my_base_builder.hp=it.health;
                if(it.health==ent_hp[EntityType::BUILDER_BASE])
                {
                    for(auto&repairer_id:my_base_builder.assigned_repairers)
                    {
                        my_builders[repairer_id].state=BuilderState::IDLE;
                    }
                    my_base_builder.assigned_repairers.clear();
                }
                my_base_builder.active=it.active;
            }
        }
            break;
        case EntityType::MELEE_BASE:
        {
            for(int i=0;i<ent_len[it.entityType];i++)
            {
                for(int j=0;j<ent_len[it.entityType];j++)
                {
                    tiles[it.position.x+i][it.position.y+j].type=it.entityType;
                    tiles[it.position.x+i][it.position.y+j].id=it.id;
                    pf_init_busy[it.position.x+i][it.position.y+j]=pot_busy_val;
                }
            }
            if(*it.playerId.get()==my_id)
            {
                my_base_melee.tick_reported=tick_current;
                my_base_melee.id=it.id;
                my_base_melee.pos=it.position;
                my_base_melee.hp=it.health;
                if(it.health==ent_hp[EntityType::MELEE_BASE])
                {
                    for(auto&repairer_id:my_base_melee.assigned_repairers)
                    {
                        my_builders[repairer_id].state=BuilderState::IDLE;
                    }
                    my_base_melee.assigned_repairers.clear();
                }
                my_base_melee.active=it.active;

            }
        }
            break;
        case EntityType::RANGED_BASE:
        {
            for(int i=0;i<ent_len[it.entityType];i++)
            {
                for(int j=0;j<ent_len[it.entityType];j++)
                {
                    tiles[it.position.x+i][it.position.y+j].type=it.entityType;
                    tiles[it.position.x+i][it.position.y+j].id=it.id;
                    pf_init_busy[it.position.x+i][it.position.y+j]=pot_busy_val;
                }
            }
            if(*it.playerId.get()==my_id)
            {
                if(!my_ranged.contains(it.id))//new ranged base
                {
                    for(auto&[id,val]:my_ranged_prod)
                    {
                        if(val.pos.x==it.position.x&&val.pos.y==it.position.y)
                        {
                            if(my_builders.contains(id))// IF NOT DIED AT PREVIOUS TICK!!!
                            {
                                my_builders[id].state=BuilderState::IDLE;
                                // my_base_ranged.pf_repair=val.pf_build_init;
                            }
                            my_base_ranged.pf_repair=val.pf_build_init;
                            goto ranged_not_canceled;
                        }
                    }
                    //                            else //fill again
                    //                            {
                    my_base_ranged.pf_repair=new array<array<int,map_len>,map_len>{};
                    pfFillLinear({ it.position.x+2, it.position.y+2},80,* my_base_ranged.pf_repair,map_len);
                    my_ranged_prod.emplace(std::piecewise_construct, std::forward_as_tuple(-1),std::forward_as_tuple(InProd({ my_base_ranged.pf_repair,it.position})));
                }
ranged_not_canceled:
                my_base_ranged.tick_reported=tick_current;
                my_base_ranged.id=it.id;
                my_base_ranged.pos=it.position;
                my_base_ranged.hp=it.health;
                if(it.health==ent_hp[EntityType::RANGED_BASE])
                {
                    for(auto&repairer_id:my_base_ranged.assigned_repairers)
                    {
                        my_builders[repairer_id].state=BuilderState::IDLE;
                    }
                    my_base_ranged.assigned_repairers.clear();
                }
                if(my_base_ranged.active!=it.active)//become active
                {
                    for (auto it2 = my_ranged_prod.cbegin(); it2 != my_ranged_prod.cend();)
                    {
                        if(it2->second.pos.x==it.position.x&&it2->second.pos.y==it.position.y)
                        {
                            my_ranged_prod.erase(it2);
                            break;
                        }
                        else ++it2;
                    }
                }
                my_base_ranged.active=it.active;
            }
        }
            break;
        case EntityType::HOUSE:
        {
            for(int i=0;i<ent_len[it.entityType];i++)
            {
                for(int j=0;j<ent_len[it.entityType];j++)
                {
                    tiles[it.position.x+i][it.position.y+j].type=it.entityType;
                    tiles[it.position.x+i][it.position.y+j].id=it.id;
                    pf_init_busy[it.position.x+i][it.position.y+j]=pot_busy_val;
                }
            }
            if(*it.playerId.get()==my_id)
            {
                if(!my_houses.contains(it.id))//new house
                {
                    for(auto&[id,val]:my_houses_prod)
                    {
                        if(val.pos.x==it.position.x&&val.pos.y==it.position.y)
                        {
                            if(my_builders.contains(id))// IF NOT DIED AT PREVIOUS TICK!!!
                            {
                                my_builders[id].state=BuilderState::IDLE;
                                // my_houses[it.id].pf_repair=val.pf_build_init;
                            }
                            //                            else //fill again
                            //                            {
                            //                                if( my_houses[it.id].pf_repair==nullptr)// IF CANCELED AT PREVIOUS TICK but still become planted
                            //                                {
                            //                                    my_houses[it.id].pf_repair=new array<array<int,map_len>,map_len>{};
                            //                                    pfFillLinear({my_houses[it.id].pos.x+1,my_houses[it.id].pos.y+1},80,* my_houses[it.id].pf_repair,map_len);
                            //                                }
                            //builder died previous tick
                            my_houses[it.id].pf_repair=val.pf_build_init;
                            //  }
                            goto house_not_canceled;
                        }
                    }
                    my_houses[it.id].pf_repair=new array<array<int,map_len>,map_len>{};
                    pfFillLinear({it.position.x+1,it.position.y+1},80,* my_houses[it.id].pf_repair,map_len);
                    my_houses_prod.emplace(std::piecewise_construct, std::forward_as_tuple(-1),std::forward_as_tuple(InProd({ my_houses[it.id].pf_repair,it.position})));
                }
house_not_canceled:
                my_houses[it.id].tick_reported=tick_current;
                my_houses[it.id].id=it.id;
                my_houses[it.id].pos=it.position;
                my_houses[it.id].hp=it.health;
                if(it.health==ent_hp[EntityType::HOUSE])
                {
                    for(auto&repairer_id:my_houses[it.id].assigned_repairers)
                    {
                        my_builders[repairer_id].state=BuilderState::IDLE;
                    }
                    my_houses[it.id].assigned_repairers.clear();
                }
                if(my_houses[it.id].active!=it.active)//become active
                {
                    for (auto it2 = my_houses_prod.cbegin(); it2 != my_houses_prod.cend();)
                    {
                        if(it2->second.pos.x==it.position.x&&it2->second.pos.y==it.position.y)
                        {
                            my_houses_prod.erase(it2);
                            break;
                        }
                        else ++it2;
                    }
                }
                my_houses[it.id].active=it.active;
            }
        }
            break;
        case EntityType::TURRET:
        {
            for(int i=0;i<ent_len[it.entityType];i++)
            {
                for(int j=0;j<ent_len[it.entityType];j++)
                {
                    tiles[it.position.x+i][it.position.y+j].type=it.entityType;
                    tiles[it.position.x+i][it.position.y+j].id=it.id;
                    pf_init_busy[it.position.x+i][it.position.y+j]=pot_busy_val;
                }
            }
            if(*it.playerId.get()==my_id)
            {
                if(!my_turrets.contains(it.id))//new turret
                {
                    for(auto&[id,val]:my_turrets_prod)
                    {
                        if(val.pos.x==it.position.x&&val.pos.y==it.position.y)
                        {
                            if(my_builders.contains(id))// IF NOT DIED AT PREVIOUS TICK!!!
                            {
                                my_builders[id].state=BuilderState::IDLE;
                                my_turrets[it.id].pf_repair=val.pf_build_init;
                            }
                            else //fill again
                            {
                                my_turrets[it.id].pf_repair=new array<array<int,map_len>,map_len>{};
                                pfFillLinear(my_turrets[it.id].pos,80,* my_turrets[it.id].pf_repair,map_len);
                            }
                        }
                    }
                }
                my_turrets[it.id].tick_reported=tick_current;
                my_turrets[it.id].id=it.id;
                my_turrets[it.id].pos=it.position;
                my_turrets[it.id].hp=it.health;
                if(it.health==ent_hp[EntityType::TURRET])
                {
                    for(auto&repairer_id:my_turrets[it.id].assigned_repairers)
                    {
                        my_builders[repairer_id].state=BuilderState::IDLE;
                    }
                    my_turrets[it.id].assigned_repairers.clear();
                }
                if(my_turrets[it.id].active!=it.active)//become active
                {
                    for (auto it2 = my_turrets_prod.cbegin(); it2 != my_turrets_prod.cend();)
                    {
                        if(it2->second.pos.x==it.position.x&&it2->second.pos.y==it.position.y)
                        {
                            my_turrets_prod.erase(it2);
                            break;
                        }
                        else ++it2;
                    }

                }
                my_turrets[it.id].active=it.active;
            }
        }
            break;
        case EntityType::WALL:
        {
            if(*it.playerId.get()==my_id)
            {
                pf_init_busy_ref=pot_busy_val;
            }
        }
            break;
        default:
            break;

        }
    }

    //->remove dead units

    for(auto it = my_builders.begin(); it != my_builders.end();)
    {
        if(!it->second.isAlive())
        {
            if(it->second.state==BuilderState::HEALING)
            {
                healers.erase(it->first);
            }

            if(it->second.state==BuilderState::MOVINGTOBUILD)
            {
                if(it->second.pf_move_to!=nullptr)
                {
                    delete it->second.pf_move_to;
                    it->second.pf_move_to=nullptr;
                }
                //just tryin to erase somewhere
                my_turrets_prod.erase(it->first);
                my_houses_prod.erase(it->first);
                my_ranged_prod.erase(it->first);
                //  my_melee_prod.erase(it->first);


            }
            if(it->second.state==BuilderState::MOVINGTOREPAIR)
            {
                my_base_builder.assigned_repairers.erase(it->first);
                my_base_ranged.assigned_repairers.erase(it->first);
                my_base_melee.assigned_repairers.erase(it->first);
                for(auto &[id,val]:my_houses)
                {
                    val.assigned_repairers.erase(it->first);
                }
                for(auto &[id,val]:my_turrets)  //  no need to check if already erased from another building
                {
                    val.assigned_repairers.erase(it->first);
                }
            }

            it = my_builders.erase(it);
        }
        else
            ++it;
    }
    for(auto it = my_melee.cbegin(); it != my_melee.cend(); )
    {
        if(!it->second.isAlive())
            it = my_melee.erase(it);
        else
            ++it;
    }
    for(auto it = my_ranged.cbegin(); it != my_ranged.cend(); )
    {
        if(!it->second.isAlive())
        {
            for(auto &it2:it->second.assigned_healers)
            {
                healers.erase(it2);
                my_builders[it2].state=BuilderState::IDLE;
            }
            it = my_ranged.erase(it);
        }
        else
            ++it;
    }
    //<-remove dead units

    my_units_count=my_ranged.size()+my_melee.size()+my_builders.size();
    my_food=5*((my_base_builder.active&&my_base_builder.isAlive())+(my_base_melee.active&&my_base_melee.isAlive())+(my_base_ranged.active&&my_base_ranged.isAlive()));
    //remove dead buildings
    for(auto it = my_houses.cbegin(); it != my_houses.cend(); )
    {
        if(!it->second.isAlive())
        {
            for(auto &it2:it->second.assigned_repairers)
            {
                if(my_builders.contains(it2))
                {
                    my_builders[it2].state=BuilderState::IDLE;
                }
            }
            delete it->second.pf_repair;
            it = my_houses.erase(it);

        }
        else
        {
            if(it->second.active)
                my_food+=5;
            ++it;
        }
    }
    for(auto it = my_turrets.cbegin(); it != my_turrets.cend();)
    {
        if(!it->second.isAlive())
        {
            for(auto &it2:it->second.assigned_repairers)
            {
                if(my_builders.contains(it2))
                {
                    my_builders[it2].state=BuilderState::IDLE;
                }
            }
            delete it->second.pf_repair;
            it = my_turrets.erase(it);
        }
        else
            ++it;
    }
    //    if(!my_base_builder.isAlive())
    //    {
    //        for(auto &it2:my_base_builder.assigned_repairers)
    //        {
    //            if(my_builders.contains(it2))
    //            {
    //                my_builders[it2].state=BuilderState::IDLE;
    //            }
    //        }
    //        if (my_base_builder.pf_repair!=nullptr)
    //        {
    //            delete my_base_builder.pf_repair;
    //            my_base_builder.pf_repair=nullptr;
    //        }
    //    }
    //    if(!my_base_ranged.isAlive())
    //    {
    //        for(auto &it2:my_base_ranged.assigned_repairers)
    //        {
    //            if(my_builders.contains(it2))
    //            {
    //                my_builders[it2].state=BuilderState::IDLE;
    //            }
    //            if (my_base_ranged.pf_repair!=nullptr)
    //            {
    //                delete my_base_ranged.pf_repair;
    //                my_base_ranged.pf_repair=nullptr;
    //            }
    //        }

    //    }
    //    if(!my_base_melee.isAlive())
    //    {
    //        for(auto &it2:my_base_melee.assigned_repairers)
    //        {
    //            if(my_builders.contains(it2))
    //            {
    //                my_builders[it2].state=BuilderState::IDLE;
    //            }
    //            if (my_base_melee.pf_repair!=nullptr)
    //            {
    //                delete my_base_melee.pf_repair;
    //                my_base_melee.pf_repair=nullptr;
    //            }
    //        }
    //    }

    //<-remove dead houses/turrets/walls


    //fill busy not planted yet
    for(auto&[id,val]:my_houses_prod)
    {
        pfFill(val.pos,pot_busy_val,pf_init_busy,ent_len[EntityType::HOUSE]);
    }
    for(auto&[id,val]:my_turrets_prod)
    {
        pfFill(val.pos,pot_busy_val,pf_init_busy,ent_len[EntityType::TURRET]);
    }
    for(auto&[id,val]:my_ranged_prod)
    {
        pfFill(val.pos,pot_busy_val,pf_init_busy,ent_len[EntityType::RANGED_BASE]);
    }
    //renew reserved
    res_reserved=0;
    for(auto&[id,val]:my_builders)
    {
        if(val.state==BuilderState::MOVINGTOBUILD)
        {
            res_reserved+=init_price[val.target_type];
        }
    }
    //tick 0
    if(tick_current==0)
    {
        for(auto &[id,val]:my_turrets)
        {
            val.pf_repair=new array<array<int,map_len>,map_len>{};
            pfFillLinear({val.pos.x,val.pos.y},80,*val.pf_repair,map_len);
        }

        my_base_builder.pf_repair=new array<array<int,map_len>,map_len>{};
        pfFillLinear({my_base_builder.pos.x,my_base_builder.pos.y},80,*my_base_builder.pf_repair,map_len);
        if(!fog)
        {
            my_base_ranged.pf_repair=new array<array<int,map_len>,map_len>{};
            pfFillLinear({my_base_ranged.pos.x,my_base_ranged.pos.y},80,*my_base_ranged.pf_repair,map_len);
            my_base_melee.pf_repair=new array<array<int,map_len>,map_len>{};
            pfFillLinear({my_base_melee.pos.x,my_base_melee.pos.y},80,*my_base_melee.pf_repair,map_len);
        }

        if(!fog)
        {
            house_slots={{0,0},{0,4},{3,0},{0,7},{6,0},{0,10},{9,0},{0,13},{12,0},{0,16},{15,0},{0,19},{18,0},{0,22},{21,0},{0,25},{24,0},{0,28},
                         {5,10},{8,10},{20,5}};
        }
        else
            house_slots={{0,0},{0,4},{3,0},{0,7},{6,0},{9,0},{0,16},{0,19},{18,0},{0,22},{21,0},
                         {18,5},{18,9},{18,13},{5,17},{9,17},{13,17},{17,17},{5,21}};
    }

}

#include "ai.h"
void ai::assignRepairers()
{
    //assign repairers
    int best_dist=INT32_MAX;
    int dist=INT32_MAX;
    int best_id;
    for(auto &[house_id,house]:my_houses)
    {
        if(house.hp<ent_hp[EntityType::HOUSE])
        {
            for(auto &[id,val]:my_builders)
            {
                if(house.assigned_repairers.contains(id)||
                        unlikely(val.state>BuilderState::MINING)
                        )continue;
                dist=calcDist(val.pos,house.pos);
                if(dist<best_dist)
                {
                    best_dist=dist;
                    best_id=id;
                }
            }
            if(dist!=INT32_MAX)
            {
                if(house.assigned_repairers.size()==0
                        ||(house.assigned_repairers.size()==1&&ent_hp[EntityType::HOUSE]-house.hp>best_dist*2)
                        ||(house.assigned_repairers.size()==2&&ent_hp[EntityType::HOUSE]-house.hp>best_dist*4)

                        )
                {
                    house.assigned_repairers.emplace(best_id);
                    setActionRepair(best_id,house_id);
                    my_builders[best_id].pf_move_to=house.pf_repair;
                    my_builders[best_id].target_id=house.id;
                    my_builders[best_id].tick_task_start=tick_current;
                    if(pfMoveTrace(my_builders[best_id].pos,house.pos,*my_builders[best_id].pf_move_to,my_builders[best_id].trace))
                    {
                        setActionMove(best_id,house.pos);
#ifdef ENABLE_VW
                        vw_actions.push_back({my_builders[best_id].pos,house.pos});
#endif
                    }
                    my_builders[best_id].state=BuilderState::MOVINGTOREPAIR;
                }
            }
        }
    }
    for(auto &[turret_id,turret]:my_turrets) //assign repairers
    {

        if(turret.hp<ent_hp[EntityType::TURRET])
        {
            best_dist=INT32_MAX;
            dist=INT32_MAX;
            for(auto &[id,val]:my_builders)
            {
                if(turret.assigned_repairers.contains(id)||
                        unlikely(val.state>BuilderState::MINING)
                        )continue;
                dist=calcDist(val.pos,turret.pos);
                if(dist<best_dist)
                {
                    best_dist=dist;
                    best_id=id;
                }
            }
            if(dist!=INT32_MAX)
            {
                if(turret.assigned_repairers.size()<2
                        ||(turret.assigned_repairers.size()==2&&ent_hp[EntityType::HOUSE]-turret.hp>best_dist*2)
                        ||(turret.assigned_repairers.size()==3&&ent_hp[EntityType::HOUSE]-turret.hp>best_dist*4)
                        )
                {
                    turret.assigned_repairers.emplace(best_id);
                    setActionRepair(best_id,turret_id);
                    my_builders[best_id].pf_move_to=turret.pf_repair;
                    my_builders[best_id].target_id=turret.id;
                    my_builders[best_id].tick_task_start=tick_current;
                    if(pfMoveTrace(my_builders[best_id].pos,turret.pos,*my_builders[best_id].pf_move_to,my_builders[best_id].trace))
                    {
                        setActionMove(best_id,turret.pos);
#ifdef ENABLE_VW
                        vw_actions.push_back({my_builders[best_id].pos,turret.pos});
#endif
                    }
                    my_builders[best_id].state=BuilderState::MOVINGTOREPAIR;
                }

            }

        }
    }
    if(my_base_builder.isAlive()&&my_base_builder.hp<ent_hp[EntityType::BUILDER_BASE])
    {
        best_dist=INT32_MAX;
        dist=INT32_MAX;
        for(auto &[builder_id,builder]:my_builders)
        {
            if(my_base_builder.assigned_repairers.contains(builder_id))
                continue;
            dist=calcDist(builder.pos,my_base_builder.pos);
            if(dist<best_dist)
            {
                best_dist=dist;
                best_id=builder_id;
            }
        }
        if(dist!=INT32_MAX)
        {
            if(my_base_builder.assigned_repairers.size()<5
                    ||(my_base_builder.assigned_repairers.size()==5&&ent_hp[EntityType::BUILDER_BASE]-my_base_builder.hp>best_dist*2)
                    ||(my_base_builder.assigned_repairers.size()==6&&ent_hp[EntityType::BUILDER_BASE]-my_base_builder.hp>best_dist*4)
                    )
            {
                my_base_builder.assigned_repairers.emplace(best_id);
                setActionRepair(best_id,my_base_builder.id);
                my_builders[best_id].pf_move_to=my_base_builder.pf_repair;
                my_builders[best_id].target_id=my_base_builder.id;
                my_builders[best_id].tick_task_start=tick_current;
                if(pfMoveTrace(my_builders[best_id].pos,my_base_builder.pos,*my_builders[best_id].pf_move_to,my_builders[best_id].trace))
                {
                    setActionMove(best_id,my_base_builder.pos);
#ifdef ENABLE_VW
                    vw_actions.push_back({my_builders[best_id].pos,my_base_builder.pos});
#endif
                }
                my_builders[best_id].state=BuilderState::MOVINGTOREPAIR;
            }
        }
    }

    if(my_base_ranged.isAlive()&&my_base_ranged.hp<ent_hp[EntityType::RANGED_BASE])
    {
        best_dist=INT32_MAX;
        dist=INT32_MAX;
        for(auto &[builder_id,builder]:my_builders)
        {
            if(my_base_ranged.assigned_repairers.contains(builder_id))
                continue;
            dist=calcDist(builder.pos,my_base_ranged.pos);
            if(dist<best_dist)
            {
                best_dist=dist;
                best_id=builder_id;
            }
        }
        if(dist!=INT32_MAX)
        {
            if(my_base_ranged.assigned_repairers.size()<4
                    ||(my_base_ranged.assigned_repairers.size()==4&&ent_hp[EntityType::RANGED_BASE]-my_base_ranged.hp>best_dist*2)
                    ||(my_base_ranged.assigned_repairers.size()==5&&ent_hp[EntityType::RANGED_BASE]-my_base_ranged.hp>best_dist*4)
                    )
            {
                my_base_ranged.assigned_repairers.emplace(best_id);
                setActionRepair(best_id,my_base_ranged.id);
                my_builders[best_id].pf_move_to=my_base_ranged.pf_repair;
                my_builders[best_id].target_id=my_base_ranged.id;
                my_builders[best_id].tick_task_start=tick_current;
                if(pfMoveTrace(my_builders[best_id].pos,my_base_ranged.pos,*my_builders[best_id].pf_move_to,my_builders[best_id].trace))
                {
                    setActionMove(best_id,my_base_ranged.pos);
#ifdef ENABLE_VW
                    vw_actions.push_back({my_builders[best_id].pos,my_base_ranged.pos});
#endif
                }
                my_builders[best_id].state=BuilderState::MOVINGTOREPAIR;
            }
        }
    }

    if(my_base_melee.isAlive()&&my_base_melee.hp<ent_hp[EntityType::MELEE_BASE])
    {
        best_dist=INT32_MAX;
        dist=INT32_MAX;
        for(auto &[builder_id,builder]:my_builders)
        {
            if(my_base_melee.assigned_repairers.contains(builder_id))
                continue;
            dist=calcDist(builder.pos,my_base_melee.pos);
            if(dist<best_dist)
            {
                best_dist=dist;
                best_id=builder_id;
            }
        }
        if(dist!=INT32_MAX)
        {
            if(my_base_melee.assigned_repairers.size()<4
                    ||(my_base_melee.assigned_repairers.size()==4&&ent_hp[EntityType::MELEE_BASE]-my_base_melee.hp>best_dist*2)
                    ||(my_base_melee.assigned_repairers.size()==5&&ent_hp[EntityType::MELEE_BASE]-my_base_melee.hp>best_dist*4)
                    )
            {
                my_base_melee.assigned_repairers.emplace(best_id);
                setActionRepair(best_id,my_base_melee.id);
                my_builders[best_id].pf_move_to=my_base_melee.pf_repair;
                my_builders[best_id].target_id=my_base_melee.id;
                my_builders[best_id].tick_task_start=tick_current;
                if(pfMoveTrace(my_builders[best_id].pos,my_base_melee.pos,*my_builders[best_id].pf_move_to,my_builders[best_id].trace))
                {
                    setActionMove(best_id,my_base_melee.pos);
#ifdef ENABLE_VW
                    vw_actions.push_back({my_builders[best_id].pos,my_base_melee.pos});
#endif
                }
                my_builders[best_id].state=BuilderState::MOVINGTOREPAIR;
            }
        }
    }
}

#include "ai.h"
vector<EntityType> targets_all_but_res{WALL, HOUSE, BUILDER_BASE, BUILDER_UNIT, MELEE_BASE, MELEE_UNIT, RANGED_BASE, RANGED_UNIT, TURRET};
bool operator== (const Coord &c1, const Coord &c2)
{
    return (c1.x == c2.x &&
            c1.y == c2.y);
}
bool add_flag=false;
void ai::managerMain()
{
#ifdef ENABLE_VW
    vw_actions.clear();
#endif

    actions.entityActions.clear();


    if((!my_builders.empty()&&my_res>30+res_reserved)
            &&(
                ( my_food<=my_units_count+10  &&my_houses_prod.size()==0)
                ||
                (my_houses_prod.size()==1 &&(my_food<=my_units_count+5) )// &&my_builders.size()>15)

                )
            )
    {
        buildHouse();
    }
    if(fog)
    {
        if((!my_builders.empty()&&my_res>470+res_reserved)&&my_ranged_prod.empty()&&!my_base_ranged.active)
        {
            if(isFreeToBuild({11,5},EntityType::RANGED_BASE))
            {
                buildRanged({11,5});
            }
            else if(isFreeToBuild({5,11},EntityType::RANGED_BASE))
            {
                buildRanged({5,11});
            }
            else if(isFreeToBuild({11,11},EntityType::RANGED_BASE))
            {
                buildRanged({11,11});
            }
            else if(isFreeToBuild({12,0},EntityType::RANGED_BASE))
            {
                buildRanged({12,0});
            }
            else if(isFreeToBuild({0,11},EntityType::RANGED_BASE))
            {
                buildRanged({0,11});
            }
        }
        if(!add_flag&&my_base_ranged.tick_reported!=never_reported)
        {
            //            house_slots={{0,0},{0,4},{3,0},{0,7},{6,0},{0,10},{9,0},{0,13},{12,0},{0,16},{15,0},{0,19},{18,0},{0,22},{21,0},{0,25},{24,0},{0,28},
            //                         {5,10},{8,10},{20,5}};

            //            house_slots={{0,0},{0,4},{3,0},{0,7},{6,0},{9,0},{0,16},{0,19},{18,0},{0,22},{21,0},
            //                         {18,5},{18,9},{5,17},{5,21}};
            vector<Coord> add_slots={{0,10},{0,13},{12,0},{15,0},
                                     {6,12},
                                     {12,12},
                                     {12,6}};

            //            if(my_base_ranged.pos==Coord{0,11})
            //            {
            //                add_slots.erase(add_slots.begin(),add_slots.begin()+1);
            //            }
            //            else if(my_base_ranged.pos==Coord{12,0})
            //            {
            //                add_slots.erase(add_slots.begin()+2,add_slots.begin()+3);
            //            }
            //            else if(my_base_ranged.pos==Coord{11,11})
            //            {
            //                add_slots.erase(add_slots.begin()+5);
            //            }
            //            else if(my_base_ranged.pos==Coord{5,11})
            //            {
            //                add_slots.erase(add_slots.begin()+4);
            //            }
            //            else //{11,5}
            //            {
            //                add_slots.erase(add_slots.begin()+6);
            //            }
            house_slots.insert(house_slots.end(),add_slots.begin(),add_slots.end());
            add_flag=true;
        }


    }


    pfCalcRes();
    assignRepairers();
    for(auto &[id,val]:my_builders)
    {
        val.trace.push_back(val.pos);
        Coord dest;
        if(val.state==BuilderState::MOVINGTOBUILD)
        {
            if(val.tick_task_start+val.max_trybuild_ticks<tick_current)
            {
                if(val.pf_move_to!=nullptr)
                {
                    delete val.pf_move_to;
                    val.pf_move_to=nullptr;
                }
                //just tryin to erase somewhere
                my_turrets_prod.erase(id);
                my_houses_prod.erase(id);
                my_ranged_prod.erase(id);
                val.state=BuilderState::IDLE;
                val.tick_relax_start=tick_current;
                setActionBuildStop(id);
                continue;
            }
            else
            {
                switch (val.target_type)
                {
                case EntityType::HOUSE:
                    setActionBuild(id,{val.target.x-1,val.target.y-1},EntityType::HOUSE);
                    break;

                case EntityType::TURRET:
                    setActionBuild(id,{val.target.x,val.target.y},EntityType::TURRET);
                    break;
                case EntityType::RANGED_BASE:
                    setActionBuild(id,{val.target.x-2,val.target.y-2},EntityType::RANGED_BASE);
                    break;
                default:break;
                }

                if(pfMoveTrace(val.pos,dest,*val.pf_move_to,val.trace))
                {
                    setActionMove(id,dest);
                    pf_init_busy[dest.x][dest.y]=pot_busy_val;
                    pf_init_busy[val.pos.x][val.pos.y]=0;

#ifdef ENABLE_VW
                    vw_actions.push_back({val.pos,dest});
#endif
                }
            }

            if(val.trace.size()>=trace_log_sz)
                val.trace.pop_front();
        }
        else if(val.state==BuilderState::MOVINGTOREPAIR)
        {
            setActionRepair(id,val.target_id);
            if(pfMoveTrace(val.pos,dest,*val.pf_move_to,val.trace))
            {
                setActionMove(id,dest);
                //pf_init_busy[dest.x][dest.y]=pot_busy_val;
                //    pf_init_busy[val.pos.x][val.pos.y]=0;

#ifdef ENABLE_VW
                vw_actions.push_back({val.pos,dest});
#endif
            }
            if(val.trace.size()>=trace_log_sz)
                val.trace.pop_front();
        }


//        if(val.state==BuilderState::HEALING&& my_ranged[val.target_id].hp==ent_hp[EntityType::RANGED_UNIT])
//        {
//            val.state=BuilderState::IDLE;
//            healers.erase(id);
//        }
//        else
//        {
//            setActionMove(id,val.target);
//            setActionRepair(id,val.target_id);
//        }

        //scan for heal
//        if((int)healers.size()<max_healers)
//        {
//            Coord to_heal_dest;
//            int to_heal_id;
//            // cout<<scanForNearestToheal(val.pos,to_heal_dest,50,to_heal_id)<<endl;
//            if(scanForNearestToheal(val.pos,to_heal_dest,30,to_heal_id))
//            {
//                if(calcDist(val.pos,to_heal_dest)<15)
//                {
//                    setActionMove(id,to_heal_dest);
//                    setActionRepair(id,to_heal_id);
//                    val.target_id=to_heal_id;
//                    val.state=BuilderState::HEALING;
//                    healers.emplace(id);
//                    my_ranged[to_heal_id].assigned_healers.emplace(id);
//#ifdef ENABLE_VW
//                    vw_actions.push_back({val.pos,to_heal_dest});
//#endif
//                }
//            }
////            else
////            {
////                if( val.state==BuilderState::HEALING)
////                    val.state=BuilderState::IDLE;
////            }
//        }

        if(val.state>BuilderState::MINING)continue;
        if(pfMove(val.pos,dest,pf_res))
        {
            setActionMove(id,dest);
            if(tiles[dest.x][dest.y].res_amount>0)
            {
                val.state=BuilderState::MINING;
                val.trace.clear();
            }
            else
            {
                val.state=BuilderState::MOVINGTOMINE;
                pf_init_busy[dest.x][dest.y]=pot_busy_val;
                pf_init_busy[val.pos.x][val.pos.y]=0;

            }
#ifdef ENABLE_VW
            vw_actions.push_back({val.pos,dest});
#endif
        }
    }
    //decisions
    //  a1=***
    //a2=***
    //b1,b2
    //priorities
    if(my_base_builder.isAlive())
    {
        if((!fog&&
            (
                (my_res>res_reserved+init_price[EntityType::BUILDER_UNIT]-(int)my_builders.size())
                &&(
                    (my_builders.size()<10)
                    ||(my_builders.size()<20&&tick_current<200&&my_houses_prod.size()>0)
                    ||(my_builders.size()<40&&tick_current<700&&my_builders.size()<my_ranged.size()*2.5)

                    )

                // ||(tick_current<200&&my_houses.size()!=0)
                //  ||(tick_current<700&&my_builders.size()<my_ranged.size()*1.5)// less then 1/2 of ranged AND tick is <800
                ))

                ||(fog&&
                   (
                       (my_res>res_reserved+init_price[EntityType::BUILDER_UNIT]-(int)my_builders.size())
                       &&(
                           (my_builders.size()<10)
                           ||(my_builders.size()<25&&my_houses.size()>0)
                           ||(my_ranged_prod.size()!=0&&my_builders.size()<40)
                           ||   (my_builders.size()<40&&tick_current<700&&my_builders.size()<my_ranged.size()*2.5)

                           )

                       // ||(tick_current<200&&my_houses.size()!=0)
                       //  ||(tick_current<700&&my_builders.size()<my_ranged.size()*1.5)// less then 1/2 of ranged AND tick is <800
                       ))
                )

        {
            Coord dest;
            calcRallyPointBuilder(my_base_builder,dest);
#ifdef ENABLE_VW
            vw_actions.push_back({my_base_builder.pos,dest});
#endif
            setActionBuild(my_base_builder.id,dest,EntityType::BUILDER_UNIT);
            res_reserved+=init_price[EntityType::BUILDER_UNIT]+(int)my_builders.size();
        }
        else
            setActionBuildStop(my_base_builder.id);
    }

    if(my_base_ranged.isAlive())
    {
        if(my_res>res_reserved+init_price[EntityType::RANGED_UNIT]+(int)my_ranged.size()
                //  &&((my_builders.size()>=10&&my_builders.size()>my_ranged.size())*2
                //         ||tick_current>=700)
                )
            //  if(my_builders.size()>=12&&my_builders.size()/ clamp(my_ranged.size(),static_cast<size_t>(1),SIZE_MAX)>=1.5)
        {
            Coord dest;
            calcRallyPointRanged(my_base_ranged,dest);
            //  calcRallyPointBuilder(my_base_ranged,dest);
#ifdef ENABLE_VW
            vw_actions.push_back({my_base_ranged.pos,dest});
#endif
            setActionBuild(my_base_ranged.id,dest,EntityType::RANGED_UNIT);
            res_reserved+=init_price[EntityType::RANGED_UNIT]+(int)my_ranged.size();
        }
        else
            setActionBuildStop(my_base_ranged.id);
    }


    if(my_base_melee.isAlive())
    {

        if(my_res>res_reserved+init_price[EntityType::MELEE_UNIT]+(int)my_melee.size()
                &&((my_builders.size()>=15&&my_ranged.size()>my_melee.size()*3)
                   ||tick_current>=700))/// clamp(my_melee.size(),static_cast<size_t>(1),SIZE_MAX)>=4)
            // if(my_builders.size()>=20&&my_builders.size()/ clamp(my_melee.size(),static_cast<size_t>(1),SIZE_MAX)>=4)
        {
            Coord dest;
            calcRallyPointBuilder(my_base_melee,dest);
#ifdef ENABLE_VW
            vw_actions.push_back({my_base_melee.pos,dest});
#endif
            setActionBuild(my_base_melee.id,dest,EntityType::MELEE_UNIT);
            res_reserved+=init_price[EntityType::MELEE_UNIT]+(int)my_melee.size();
        }
        else
            setActionBuildStop(my_base_melee.id);
    }



    for(auto &[id,val]:my_turrets)
    {
        setActionAttackAuto(id,targets_all_but_res,500);
    }
    for(auto &[id,val]:my_melee)
    {
        setActionAttackAuto(id,targets_all_but_res,500);

        if(tick_current>700)
        {

            setActionMove(id,{25,35});
        }
        else if(tick_current>400)
        {
            setActionMove(id,{17,27});
        }
        else   setActionMove(id,{12,22});

    }
    int x=20,y=20;
    if(!my_builders.empty())
    {
        for(auto &[id,val]:my_builders)
        {
            x+=val.pos.x;
            y+=val.pos.y;
        }
        x=x/my_builders.size();
        y=y/my_builders.size();
    }
    bool flag=true;
    //  cout<<x<< " "<<y<<endl;
    for(auto &[id,val]:my_ranged)
    {
        setActionAttackAuto(id,targets_all_but_res,400);
        if(flag)
            setActionMove(id,{clamp(x-5,0,79),clamp(y+5,0,79)});
        else
            setActionMove(id,{clamp(x+5,0,79),clamp(y-5,0,79)});
        flag=!flag;
        //        if(tick_current>700)
        //        {

        //            setActionMove(id,{35,25});

        //        }
        //        else if(tick_current>400)
        //        {

        //            setActionMove(id,{27,17});
        //        }
        //        else    setActionMove(id,{22,12});

    }



}

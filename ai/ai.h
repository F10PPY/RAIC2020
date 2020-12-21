#ifndef MAP_INFO_H
#define MAP_INFO_H
#include "model/Model.hpp"
#include <unordered_set>
#include <iostream>
#include <deque>
#include <string.h>
#include "ntb_util.h"

using namespace std;
const int map_len=80;
constexpr int map_len_sq=map_len*map_len;

//enum EntityType { WALL = 0, HOUSE = 1, BUILDER_BASE = 2,  BUILDER_UNIT = 3, MELEE_BASE = 4,  MELEE_UNIT = 5,    RANGED_BASE = 6,    RANGED_UNIT = 7,    RESOURCE = 8,    TURRET = 9};
enum class BuilderState{IDLE=0,MOVINGTOMINE,MINING,MOVINGTOREPAIR,MOVINGTOBUILD,BUILDING,HEALING};
const string Bstate_str[]={"idle","m2mine","mining","m2repair","m2build","building"};
const int ent_len[10]={1,3,5,1,5,1,5,1,1,2};
const int init_price[10]{10,50,500,10,500,20,500,30,-1,50};
const int ent_hp[10]={50,50,300,10,300,50,300,10,30,100};
const int empty_tile=-1;
const int never_reported=-1;
const int trace_log_sz=10;
constexpr const int pot_busy_val=INT32_MAX/8+1;
constexpr const int pot_target_val=INT32_MAX/2+1;
struct Coord
{
    int x;
    int y;
    Coord(){};
    Coord (int x_,int y_):x(x_),y(y_){};
    Coord(Vec2Int v):x(v.x),y(v.y){};

};

struct Tile
{
  //  bool in_prod=false;
    int id;
    int res_amount=0;
    int type=empty_tile;//remove and use pot_busy instead
};
struct InProd//only need if not planted yet
{

  //  int assigned_builder_id;
    Coord pos;
    array<array<int,map_len>,map_len>*pf_build_init;
 //   array<array<int,map_len>,map_len>pf_build_init;


    InProd(array<array<int,map_len>,map_len>*pf_build_):pf_build_init(pf_build_)
    {

    }
    InProd(array<array<int,map_len>,map_len>*pf_build_, Coord pos_):
        pos(pos_),pf_build_init(pf_build_)//,is_planted(is_planted_),assigned_builder_id(assigned_builder_id_)
    {

    }
};


class ai
{
    struct UnitBuilder
    {
        bool alive;
        int tick_task_start;
        int max_trybuild_ticks;
        int tick_relax_start;
        int hp;
        int target_id;
        unordered_set<int> assigned_healers;
        Coord pos;
        Coord target;
        EntityType target_type;
        array<array<int,map_len>,map_len>*pf_move_to;
        deque <Coord>trace;
        BuilderState state=BuilderState::IDLE;
        bool isAlive()const
        {
            return alive==flag_alive;
        }
    };
    struct Building
    {
        bool active=false;
        int tick_reported=never_reported;
        int hp;
        int id;
        Coord pos;
        unordered_set <int> assigned_repairers;
        array<array<int,map_len>,map_len>*pf_repair;
      //  array<array<int,map_len>,map_len>pf_repair;

        bool isAlive() const
        {
            return ai::tick_current==tick_reported;
        }
    };

public:
    bool fog;
    array<array<int,map_len>,map_len>pf_init_busy;
    unordered_map<int,InProd> my_houses_prod;
    unordered_map<int,InProd> my_turrets_prod;
    unordered_map<int,InProd> my_ranged_prod;//ugly but ok
   // unordered_multimap <EntityType,InProd> inprod_mmap;
    Coord builder_pos_median;
    unordered_set<int>healers;
    int max_healers=5;
    int max_relax_ticks=3;
    float coef_trybuild=1.5;
    //int min_trybuild_ticks=3;
    int res_reserved;
    int my_id,my_res,my_food,my_score;
    int my_units_count=1;
    static bool flag_alive;
    static int tick_current;

    Building my_base_builder;
    Building my_base_melee;
    Building my_base_ranged;

    vector<Coord> house_slots;
    Action actions;
    array<array<Tile,map_len>,map_len>tiles;

    unordered_map <int,UnitBuilder> my_builders; //[id,val]
    unordered_map <int,UnitBuilder> my_ranged;
    unordered_map <int,UnitBuilder> my_melee;
    unordered_map <int,Building> my_houses;
    unordered_map <int,Building> my_turrets;
    unordered_map <int,Building> my_walls;

    //PF->
    //  int pf_res[map_len][map_len];
    array<array<int,map_len>,map_len> pf_res;
    void pfCalcRes();
    bool pfMove(Coord start, Coord &dest,array<array<int,map_len>,map_len>&pf);
    bool pfMoveTrace(Coord start,Coord &dest,array<array<int,map_len>,map_len>&pf,deque<Coord>&trace);
    void calcRallyPointBuilder(Building &building, Coord &dest);
    void calcRallyPointRanged(Building &building,Coord &dest);
    void pfCalcBuild(array<array<int,map_len>,map_len>&pf_init,array<array<int,map_len>,map_len>&pf_final);
    void pfFillLinear(Coord pos, int init, array<array<int,map_len>,map_len>&pf, int len, int addition=0);
    void pfFillLinearQube(Coord pos, int init, int addition, array<array<int,map_len>,map_len>&pf, int len);
    void pfFill(Coord pos,int init,array<array<int,map_len>,map_len>&pf,int len);
    //<-PF


    void setActionMove(int id, Coord dest,bool findClosest=true, bool breakThrough=true);
    void setActionMoveStop(int id);
    void setActionBuild(int id,Coord dest,EntityType ent);
    void setActionBuildStop(int id);
    void setActionRepair(int id, int target);
    void setActionAttackAuto(int id, std::vector<EntityType> &AutoAttackTargets,int max_nodes=1000);
    void setActionAttackTarget(int id,int target, std::vector<EntityType> &AutoAttackTargets, int max_nodes=1000);

    void updateTick(const PlayerView& playerView);
    void managerMain();
    bool buildHouse();
    bool buildTurret(Coord dest);
    bool buildRanged(Coord dest);
    void assignRepairers();
    bool isEmptyTiles(int x,int y,int len)
    {
        for(int i=0;i<len;i++)
        {
            for(int j=0;j<len;j++)
            {
                if(tiles[x+i][y+j].type!=empty_tile)
                    return false;
            }
        }
        return true;
    }
    bool isFreeToBuild(Coord base, EntityType ent_type)
    {
        for(int i=0;i<ent_len[ent_type];i++)
        {
            for(int j=0;j<ent_len[ent_type];j++)
            {
//                if(tiles[base.x+i][base.y+j].type!=empty_tile
//                        ||tiles[base.x+i][base.y+j].in_prod
//                        )
                if(pf_init_busy[base.x+i][base.y+j]!=0)
                    return false;
            }
        }
        return true;
    }
    int calcDist(const int x1, const int x2, const int y1, const int y2)
    {
        return abs(x1-x2)+abs(y1-y2);
    }
    int calcDist(const Coord p1, const Coord p2)
    {
        return abs(p1.x-p2.x)+abs(p1.y-p2.y);
    }
#ifdef ENABLE_VW
    struct VWAction
    {
        Coord from,to;
    };
    vector <VWAction> vw_actions;
#endif

    //outdated->
    bool scanForNearestRes(Coord from,Coord &to);
    bool scanForNearestToheal(Coord from, Coord &dest, int len, int &target_id);
};







#endif // MAP_INFO_H

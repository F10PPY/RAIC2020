#include "ai.h"

int ai::tick_current=0;
bool ai::flag_alive;
void ai::setActionMove(int id, Coord dest,bool findClosest, bool breakThrough)
{
    MoveAction ma({dest.x,dest.y},findClosest,breakThrough);
    actions.entityActions[id].moveAction=std::make_shared<MoveAction>(ma);
}
void ai::setActionMoveStop(int id)
{
    actions.entityActions[id].moveAction=nullptr;
}
void ai::setActionBuild(int id,Coord dest,EntityType ent)
{
    BuildAction ba{ent,{dest.x,dest.y}};
    actions.entityActions[id].buildAction=std::make_shared<BuildAction>(ba);
}
void ai::setActionBuildStop(int id)
{
    actions.entityActions[id].buildAction=nullptr;;
}
void ai::setActionRepair(int id, int target)
{
    RepairAction ra{target};
    actions.entityActions[id].repairAction=std::make_shared<RepairAction>(ra);
}
void ai::setActionAttackAuto(int id, std::vector<EntityType> &AutoAttackTargets,int max_nodes)
{
    AutoAttack atk{max_nodes,AutoAttackTargets};
    AttackAction aa{nullptr,make_shared<AutoAttack>(atk)};
    actions.entityActions[id].attackAction=std::make_shared<AttackAction>(aa);
}
void ai::setActionAttackTarget(int id,int target, std::vector<EntityType> &AutoAttackTargets, int max_nodes)
{
    AutoAttack atk{max_nodes,AutoAttackTargets};
    AttackAction aa{std::make_shared<int>(target),make_shared<AutoAttack>(atk)};
    actions.entityActions[id].attackAction=std::make_shared<AttackAction>(aa);
}


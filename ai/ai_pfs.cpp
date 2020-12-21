#include "ai.h"
void ai::pfCalcRes()
{

    for(int i=0;i<map_len;i++)
    {
        for(int j=0;j<map_len;j++)
        {
            pf_res[i][j]=0;//set default val
        }
    }
    //set my corner negative potential
   // if(tick_current<200)
    {
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<30;j++)
        {
            pf_res[i][j]-=928000-16000*(i+j);
        }
    }
    }


    array <int,30>pot_res;
    const int pot_res_len = pot_res.size();
    //   static const int pf_pot_res[9]={256,128,64,32,16,8,4,2,1};
    //   static const int pf_pot_res[16]={16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};//256,128,64,32,16,8,3,2,1};

    int x=1;
    for(int n=pot_res_len-10;n>=0;n--)
    {
        pot_res[n]=x;
        x*=2;
    }
    x=pot_res[15];
    for(int n=15;n<pot_res_len;n++)
    {
        pot_res[n]=x--;
    }


    for(int i=0;i<map_len;i++)
    {
        for(int j=0;j<map_len;j++)
        {
            if(tiles[i][j].res_amount>0)
            {
                for(int y=0;y<pot_res_len;y++)
                {
                    for(int x=-(pot_res_len-1)+y;x<=(pot_res_len-1)-y;x++)
                    {
                        //upper  side
                        if(i+x<0||i+x>map_len-1||j+y<0||j+y>map_len-1)continue;
                        pf_res[i+x][j+y]+=pot_res[abs(x)+y];
                        if(y==0)continue;//mid lane one first time

                        //lower  side
                        if(i+x<0||i+x>map_len-1||j-y<0||j-y>map_len-1)continue;
                        pf_res[i+x][j-y]+=pot_res[abs(x)+y];
                    }
                }
                pf_res[i][j]=pot_target_val;// set self field for resource
            }
        }
    }
    //   const int pf_pot_my_builder[]={-17,-16,-15,-14,-3};
    // const int pot_builder_len = 5;
    array <int,10>pot_my_builder;
    int sz=pot_my_builder.size();
    int x2=pot_res[0];
    for(int n=0;n<sz;n++)
    {
        pot_my_builder[n]=-x2;
        x2/=2.2;
    }
    //   sz-=3;
    for (auto& [id,val]:my_builders)
    {

        if(val.state==BuilderState::MINING)
        {
            for(int y=0;y<sz;y++)
            {
                for(int x=-(sz-1)+y;x<=(sz-1)-y;x++)
                {
                    if(val.pos.x+x<0||val.pos.x+x>map_len-1||val.pos.y+y<0||val.pos.y+y>map_len-1)continue;
                    pf_res[val.pos.x+x][val.pos.y+y]+=pot_my_builder[abs(x)+y];
                    if(y==0)continue;//mid lane one first time

                    if(val.pos.x+x<0||val.pos.x+x>map_len-1||val.pos.y-y<0||val.pos.y-y>map_len-1)continue;
                    pf_res[val.pos.x+x][val.pos.y-y]+=pot_my_builder[abs(x)+y];
                }
            }
        }
      //  pf_res[val.pos.x][val.pos.y]=-pot_res[0]*8;// set self field
    }



//    for (auto& [id,val]:my_ranged)
//    {
//        pf_res[val.pos.x][val.pos.y]=-pot_res[0]*8;// set self field
//    }
//    for (auto& [id,val]:my_melee)
//    {
//        pf_res[val.pos.x][val.pos.y]=-pot_res[0]*8;// set self field
//    }


//    //->buildings self pot
//    if(my_base_builder.isAlive())
//    {
//        for(int i=0;i<ent_len[EntityType::BUILDER_BASE];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::BUILDER_BASE];j++)
//            {
//                pf_res[my_base_builder.pos.x+i][my_base_builder.pos.y+j]=-pot_res[0]*8;
//            }
//        }
//    }
//    if(my_base_melee.isAlive())
//    {
//        for(int i=0;i<ent_len[EntityType::MELEE_BASE];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::MELEE_BASE];j++)
//            {
//                pf_res[my_base_melee.pos.x+i][my_base_melee.pos.y+j]=-pot_res[0]*8;
//            }
//        }
//    }
//    if(my_base_ranged.isAlive())
//    {
//        for(int i=0;i<ent_len[EntityType::RANGED_BASE];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::RANGED_BASE];j++)
//            {
//                pf_res[my_base_ranged.pos.x+i][my_base_ranged.pos.y+j]=-pot_res[0]*8;
//            }
//        }
//    }
//    for (auto& [id,val]:my_turrets)
//    {
//        for(int i=0;i<ent_len[EntityType::TURRET];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::TURRET];j++)
//            {
//                pf_res[val.pos.x+i][val.pos.y+j]=-pot_res[0]*8;
//            }
//        }
//    }
//    for (auto& [id,val]:my_houses)
//    {
//        for(int i=0;i<ent_len[EntityType::HOUSE];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::HOUSE];j++)
//            {
//                pf_res[val.pos.x+i][val.pos.y+j]=-pot_res[0]*8;
//            }
//        }
//    }
//    for(auto&[ent_type,val]:inprod_mmap)
//    {
//        if(!val.is_planted)
//        {
//            for(int i=0;i<ent_len[ent_type];i++)
//            {
//                for(int j=0;j<ent_len[ent_type];j++)
//                {
//                    pf_res[val.pos.x+i][val.pos.y+j]=-pot_res[0]*8;
//                }
//            }
//        }
//    }
}
//void ai::pfFillBusy(int pot)
//{
//    for (auto& [id,val]:my_builders)
//    {
//        pf_init_busy[val.pos.x][val.pos.y]=pot;
//    }
//    for (auto& [id,val]:my_ranged)
//    {
//        pf_init_busy[val.pos.x][val.pos.y]=pot;
//    }
//    for (auto& [id,val]:my_melee)
//    {
//         pf_init_busy[val.pos.x][val.pos.y]=pot;
//    }


//    //->buildings self pot
//    if(my_base_builder.isAlive())
//    {
//        for(int i=0;i<ent_len[EntityType::BUILDER_BASE];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::BUILDER_BASE];j++)
//            {
//                pf_init_busy[my_base_builder.pos.x+i][my_base_builder.pos.y+j]=pot;
//            }
//        }
//    }
//    if(my_base_melee.isAlive())
//    {
//        for(int i=0;i<ent_len[EntityType::MELEE_BASE];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::MELEE_BASE];j++)
//            {
//                 pf_init_busy[my_base_melee.pos.x+i][my_base_melee.pos.y+j]=pot;
//            }
//        }
//    }
//    if(my_base_ranged.isAlive())
//    {
//        for(int i=0;i<ent_len[EntityType::RANGED_BASE];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::RANGED_BASE];j++)
//            {
//                pf_init_busy[my_base_ranged.pos.x+i][my_base_ranged.pos.y+j]=pot;
//            }
//        }
//    }
//    for (auto& [id,val]:my_turrets)
//    {
//        for(int i=0;i<ent_len[EntityType::TURRET];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::TURRET];j++)
//            {
//                pf_init_busy[val.pos.x+i][val.pos.y+j]=pot;
//            }
//        }
//    }
//    for (auto& [id,val]:my_houses)
//    {
//        for(int i=0;i<ent_len[EntityType::HOUSE];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::HOUSE];j++)
//            {
//               pf_init_busy[val.pos.x+i][val.pos.y+j]=pot;
//            }
//        }
//    }
//    for (auto& [id,val]:my_walls)
//    {
//        for(int i=0;i<ent_len[EntityType::WALL];i++)
//        {
//            for(int j=0;j<ent_len[EntityType::WALL];j++)
//            {
//               pf_init_busy[val.pos.x+i][val.pos.y+j]=pot;
//            }
//        }
//    }
//    for(auto&[ent_type,val]:inprod_mmap)
//    {
//      //  if(!val.is_planted) //doesn't matter if we overwrite from houses val
//       // {
//            for(int i=0;i<ent_len[ent_type];i++)
//            {
//                for(int j=0;j<ent_len[ent_type];j++)
//                {
//                     pf_init_busy[val.pos.x+i][val.pos.y+j]=pot;
//                }
//            }
//     //   }
//    }
//}
bool ai::pfMove(Coord start,Coord &dest,array<array<int,map_len>,map_len>&pf)
{
//    array<array<int,map_len>,map_len> trace;
//    for(auto &it:)

    int x=0,y=0;

//    if(start_tile.x+1<map_len)
//    {
//        if(pf_res[start_tile.x][start_tile.y]<pf_res[start_tile.x+1][start_tile.y])
//        {
//            x=1;y=0;
//        }
//    }
    if(start.x+1<map_len)
    {
        if(pf[start.x][start.y]-pf_init_busy[start.x][start.y]<pf[start.x+1][start.y]-pf_init_busy[start.x+1][start.y])
        {
            x=1;y=0;
        }
    }

    if(start.y+1<map_len)
    {
        if(pf[start.x+x][start.y]-pf_init_busy[start.x+x][start.y]<pf[start.x][start.y+1]-pf_init_busy[start.x][start.y+1])
        {
            x=0;y=1;
        }
    }
    if(start.x-1>=0)
    {
        if(pf[start.x+x][start.y+y]-pf_init_busy[start.x+x][start.y+y]<pf[start.x-1][start.y]-pf_init_busy[start.x-1][start.y])
        {
            y=0;x=-1;
        }
    }
    if(start.y-1>=0)
    {
        if(pf[start.x+x][start.y+y]-pf_init_busy[start.x+x][start.y+y]<pf[start.x][start.y-1]-pf_init_busy[start.x][start.y-1])
        {
            y=-1;x=0;
        }
    }
    if(x==y&&x==0)
        return false;

    dest.x=start.x+x;
    dest.y=start.y+y;

    return true;
}
bool ai::pfMoveTrace(Coord start,Coord &dest,array<array<int,map_len>,map_len>&pf,deque<Coord>&trace)
{
    static array<array<int,map_len>,map_len> pf_trace;
    pf_trace.fill({});
    for(auto &it:trace)
    {
//        if(pf_trace[it.x][it.y]!=0)//frequent point
//        {
//           // pf_trace[it.x][it.y]-=pf_trace[it.x][it.y];
//            pf_trace[it.x][it.y]-=1;
//        }
        pf_trace[it.x][it.y]-=1;
    }

    int x=0,y=0;


    if(start.x+1<map_len)
    {
        if(pf[start.x][start.y]-pf_init_busy[start.x][start.y]+pf_trace[start.x][start.y]<pf[start.x+1][start.y]-pf_init_busy[start.x+1][start.y]+pf_trace[start.x+1][start.y])
        {
            x=1;y=0;
        }
    }

    if(start.y+1<map_len)
    {
        if(pf[start.x+x][start.y]-pf_init_busy[start.x+x][start.y]+pf_trace[start.x+x][start.y]<pf[start.x][start.y+1]-pf_init_busy[start.x][start.y+1]+pf_trace[start.x][start.y+1])
        {
            x=0;y=1;
        }
    }
    if(start.x-1>=0)
    {
        if(pf[start.x+x][start.y+y]-pf_init_busy[start.x+x][start.y+y]+pf_trace[start.x+x][start.y+y]<pf[start.x-1][start.y]-pf_init_busy[start.x-1][start.y]+pf_trace[start.x-1][start.y])
        {
            y=0;x=-1;
        }
    }
    if(start.y-1>=0)
    {
        if(pf[start.x+x][start.y+y]-pf_init_busy[start.x+x][start.y+y]+pf_trace[start.x+x][start.y+y]<pf[start.x][start.y-1]-pf_init_busy[start.x][start.y-1]+pf_trace[start.x][start.y-1])
        {
            y=-1;x=0;
        }
    }
    if(x==y&&x==0)
        return false;

    dest.x=start.x+x;
    dest.y=start.y+y;

    return true;
}




void ai::pfCalcBuild(array<array<int,map_len>,map_len>&pf_init,array<array<int,map_len>,map_len>&pf_final)
{
    pf_final=pf_init;

}
void ai::pfFillLinear(Coord pos, int init, array<array<int,map_len>,map_len>&pf, int len,int addition)
{
    for(int y=0;y<len;y++)
    {
        for(int x=-(len-1)+y;x<=(len-1)-y;x++)
        {
            //upper  side
            if(pos.x+x<0||pos.x+x>map_len-1||pos.y+y<0||pos.y+y>map_len-1)continue;
            pf[pos.x+x][pos.y+y]=init-abs(x)-y+addition;
            if(y==0)continue;//mid lane one first time

            //lower  side
            if(pos.x+x<0||pos.x+x>map_len-1||pos.y-y<0||pos.y-y>map_len-1)continue;
            pf[pos.x+x][pos.y-y]=init-abs(x)-y+addition;
        }
    }
}
//void ai::pfFillLinearQube(Coord pos, int init, int addition, array<array<int,map_len>,map_len>&pf, int len)
//{
//    for(int y=0;y<len;y++)
//    {
//        for(int x=-(len-1)+y;x<=(len-1)-y;x++)
//        {
//            if(y>len-2||x>len-2)continue;

//            if(pos.x+x<0||pos.x+x>map_len-1||pos.y+y<0||pos.y+y>map_len-1)continue;
//            pf[pos.x+x][pos.y+y]=init-abs(x)-y+addition;
//            if(y==0)continue;

//            if(pos.x+x<0||pos.x+x>map_len-1||pos.y-y<0||pos.y-y>map_len-1)continue;
//            pf[pos.x+x][pos.y-y]=init-abs(x)-y+addition;
//        }
//    }
//}
 void ai::pfFill(Coord pos,int val,array<array<int,map_len>,map_len>&pf,int len)
 {
     for(int i=0;i<len;i++)
     {
         for(int j=0;j<len;j++)
         {
             pf[pos.x+i][pos.y+j]=val;
         }
     }
 }

#include "vw.h"
#include <unistd.h>
void vw::renderLoop(ai &ai)
{
    static  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1), 0.0f, static_cast<float>(1));
    static int frames_per_tick=20;
    int frames_elapsed=0;
    while (!glfwWindowShouldClose(window))
    {
        toggle_quit=false;
        processInput(window);
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_simple.use();
        glBindVertexArray(VAO_map_tiles);
        //-->draw minerals
        shader_simple.setVec4("uni_shader_color", 0,0.4,0.4);
        for (size_t n=0;n<map_len_sq;n++)
        {
            if((ai.tiles[0][n].res_amount)>0)
            {
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(n*24));//(void*)&mapTilesVerts[0][0]);
            }
        }
        //->draw builder base
        if(ai.my_base_builder.isAlive())
        {
            shader_simple.setVec4("uni_shader_color", 0.30,0.3,0);
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<5;j++)
                {
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>((( ai.my_base_builder.pos.x+i)*80+ ai.my_base_builder.pos.y+j)*24));
                    //   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)((( ai.base_builder.pos.x)*80+ ai.base_builder.pos.y+j)*24));
                }
            }
        }
        //->draw ranged base
        if(ai.my_base_ranged.isAlive())
        {
            shader_simple.setVec4("uni_shader_color",  0,0.35,0);
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<5;j++)
                {
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>((( ai.my_base_ranged.pos.x+i)*80+ ai.my_base_ranged.pos.y+j)*24));
                }
            }
        }
        //->draw melee base
        if(ai.my_base_melee.isAlive())
        {
            shader_simple.setVec4("uni_shader_color",0.2,0.1,0);
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<5;j++)
                {
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>((( ai.my_base_melee.pos.x+i)*80+ ai.my_base_melee.pos.y+j)*24));
                }
            }
        }
        //->draw house
        for(auto &[id,val]:ai.my_houses)
        {
            shader_simple.setVec4("uni_shader_color", 0.7,0.3,0.3);
            if(val.isAlive())
            {
                for(int i=0;i<3;i++)
                {
                    for(int j=0;j<3;j++)
                    {
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>((( val.pos.x+i)*80+ val.pos.y+j)*24));
                    }
                }
            }
        }
        //->draw turrets
        for (auto &[id, val]:ai.my_turrets)
        {
            shader_simple.setVec4("uni_shader_color", 0.4,0.2,0);
            if(val.isAlive())
            {
                for(int i=0;i<2;i++)
                {
                    for(int j=0;j<2;j++)
                    {
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>((( val.pos.x+i)*80+ val.pos.y+j)*24));
                    }
                }
            }
        }
        //->draw builders
        shader_simple.setVec4("uni_shader_color", 0.30,0.3,0);
        for (auto &[id, obj]:ai.my_builders)
        {
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>((obj.pos.x*80+obj.pos.y)*24));
        }
        //->draw ranged
        shader_simple.setVec4("uni_shader_color", 0,0.35,0);
        for (auto &[id, obj]:ai.my_ranged)
        {
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>((obj.pos.x*80+obj.pos.y)*24));
        }
        //->draw melee
        shader_simple.setVec4("uni_shader_color", 0.2,0.1,0);
        for (auto &[id, obj]:ai.my_melee)
        {
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>((obj.pos.x*80+obj.pos.y)*24));
        }
        glBindVertexArray(0);



        //->draw grid

        if(toggle_grid)
        {
            shader_simple.setVec4("uni_shader_color", 0.2,0.2,0.2);
            glBindVertexArray(VAO_map_grid);

            for(size_t n=0;n<map_len_sq+2;n++)
            {
                glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(n*8));
            }
            glBindVertexArray(0);
        }


        //->draw actions
        shader_geom.use();
        glBindVertexArray(VAO_map_action);
        for(auto &it:ai.vw_actions)
        {
            shader_geom.setVec3("uni_shader_color", 1.0,0.0,0.0);
            shader_geom.setVec4("uni_offset",it.from.x*step,it.from.y*step,it.to.x*step,it.to.y*step);
            glDrawArrays(GL_POINTS, 0, 1);
        }
        for(auto &[id,val]:ai.my_builders)
        {
            if(val.state==BuilderState::MOVINGTOBUILD)
            {
                shader_geom.setVec3("uni_shader_color", 0.0,0.0,1.0);
                shader_geom.setVec4("uni_offset",val.pos.x*step,val.pos.y*step,val.target.x*step,val.target.y*step);
                glDrawArrays(GL_POINTS, 0, 1);
            }

        }
        glBindVertexArray(0);


        shader_text.use();
        shader_text.setMat4("projection",projection);
        float step_text=0.005625;

        if(toggle_show_hp)
        {
            for(auto &[id,val]:ai.my_builders)
            {
                renderText(shader_text, std::to_string(val.hp), 0.5+static_cast<float>(val.pos.x)*step_text, 0.5+static_cast<float>(val.pos.y)*step_text, 0.000045f, glm::vec3(1, 1, 1));
            }
            for(auto &[id,val]:ai.my_ranged)
            {
                renderText(shader_text, std::to_string(val.hp), 0.5+static_cast<float>(val.pos.x)*step_text, 0.5+static_cast<float>(val.pos.y)*step_text, 0.000045f, glm::vec3(1, 1, 1));
            }
            for(auto &[id,val]:ai.my_melee)
            {
                renderText(shader_text, std::to_string(val.hp), 0.5+static_cast<float>(val.pos.x)*step_text, 0.5+static_cast<float>(val.pos.y)*step_text, 0.000045f, glm::vec3(1, 1, 1));
            }
            for(auto &[id,val]:ai.my_houses)
            {
                renderText(shader_text, std::to_string(val.hp), 0.5+static_cast<float>(val.pos.x)*step_text, 0.5+static_cast<float>(val.pos.y)*step_text, 0.000045f, glm::vec3(1, 1, 1));
            }
            for(auto &[id,val]:ai.my_houses)
            {
                renderText(shader_text, std::to_string(val.hp), 0.5+static_cast<float>(val.pos.x)*step_text, 0.5+static_cast<float>(val.pos.y)*step_text, 0.000045f, glm::vec3(1, 1, 1));
            }
            for(auto &[id,val]:ai.my_turrets)
            {
                renderText(shader_text, std::to_string(val.hp), 0.5+static_cast<float>(val.pos.x)*step_text, 0.5+static_cast<float>(val.pos.y)*step_text, 0.000045f, glm::vec3(1, 1, 1));
            }
            if(ai.my_base_builder.isAlive())
            {
                renderText(shader_text, std::to_string(ai.my_base_builder.hp), 0.5+static_cast<float>(ai.my_base_builder.pos.x)*step_text, 0.5+static_cast<float>(ai.my_base_builder.pos.y)*step_text, 0.000045f, glm::vec3(1, 1, 1));
            }
            if(ai.my_base_melee.isAlive())
            {
                renderText(shader_text, std::to_string(ai.my_base_melee.hp), 0.5+static_cast<float>(ai.my_base_melee.pos.x)*step_text, 0.5+static_cast<float>(ai.my_base_melee.pos.y)*step_text, 0.000045f, glm::vec3(1, 1, 1));
            }
            if(ai.my_base_ranged.isAlive())
            {
                renderText(shader_text, std::to_string(ai.my_base_ranged.hp), 0.5+static_cast<float>(ai.my_base_ranged.pos.x)*step_text, 0.5+static_cast<float>(ai.my_base_ranged.pos.y)*step_text, 0.000045f, glm::vec3(1, 1, 1));
            }
        }
        if(toggle_builder_state)
        {
            for(auto &[id,val]:ai.my_builders)
            {
                renderText(shader_text, Bstate_str[static_cast<int>(val.state)], 0.5+static_cast<float>(val.pos.x)*step_text, 0.5+static_cast<float>(val.pos.y)*step_text+step_text/2, 0.00004f, glm::vec3(1, 1, 1));
            }
        }
        if(toggle_pf_busy)
        {
            for (unsigned int i=0;i<map_len/3;i++)
            {
                for (unsigned int j=0;j<map_len/3;j++)
                {
                    if(ai.pf_res[i][j]!=0)
                    {
                        renderText(shader_text, std::to_string(ai.pf_init_busy[i][j]), 0.5+static_cast<float>(i)*step_text, 0.5+static_cast<float>(j)*step_text, 0.00004f, glm::vec3(1, 1, 1));
                    }
                }
            }
        }
        if(toggle_pf_res)
        {
            for (unsigned int i=0;i<map_len/3;i++)
            {
                for (unsigned int j=0;j<map_len/3;j++)
                {
                    //if(ai.pf_res[i][j]!=0)
                    {
                        renderText(shader_text, std::to_string(ai.pf_res[i][j]), 0.5+static_cast<float>(i)*step_text, 0.5+static_cast<float>(j)*step_text, 0.00004f, glm::vec3(1, 1, 1));
                    }
                }
            }
        }
        if(toggle_pf_build)
        {
            if(!ai.my_houses_prod.empty())
            {
                for (unsigned int i=0;i<map_len/3;i++)
                {
                    for (unsigned int j=0;j<map_len/3;j++)
                    {
                        {
                            renderText(shader_text, std::to_string(ai.my_houses_prod.begin()->second.pf_build_init->data()[i][j]), 0.5+static_cast<float>(i)*step_text, 0.5+static_cast<float>(j)*step_text, 0.00004f, glm::vec3(1, 1, 1));

                         //   renderText(shader_text, std::to_string(ai.pf_res[i][j]), 0.5+static_cast<float>(i)*step_text, 0.5+static_cast<float>(j)*step_text, 0.00004f, glm::vec3(1, 1, 1));
                        }
                    }
                }
            }
        }



        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Controls");
        ImGui::Text("Tick = %d", ai.tick_current);
        ImGui::SameLine();
        ImGui::Checkbox("Pause", &toggle_pause);
        //        if (ImGui::Button("Pause"))
        //        {
        //            toggle_pause = !toggle_pause;
        //        }
        ImGui::SameLine();
        if (ImGui::Button("Next"))
        {
            toggle_quit=true;
        }
        ImGui::SliderInt("FPT", &frames_per_tick, 1, 30);
        ImGui::Checkbox("Grid", &toggle_grid);
        ImGui::Checkbox("HP", &toggle_show_hp);
        ImGui::Checkbox("PF Busy", &toggle_pf_busy);
        ImGui::SameLine();
        ImGui::Checkbox("PF Res", &toggle_pf_res);
        ImGui::SameLine();
        ImGui::Checkbox("PF Build", &toggle_pf_build);
        ImGui::Checkbox("Builder state", &toggle_builder_state);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        // ImGui::Text("H = %i",viewportH);
        //  ImGui::Text("W = %i",viewportW);
        // ImGui::Text("X = %i", viewportX);
        //  ImGui::Text("Y = %i",viewportY);
        ImGui::End();


        ImGui::Begin("Info");
        ImGui::Text("My score: %i",ai.my_score);
        ImGui::Text("My res: %i",ai.my_res);
        ImGui::SameLine();
        ImGui::Text("reserved: %i",ai.res_reserved);
        ImGui::Text("My units: %i",ai.my_units_count);
        ImGui::SameLine();
        ImGui::Text("B: %lu",ai.my_builders.size());
        ImGui::SameLine();
        ImGui::Text("R: %lu",ai.my_ranged.size());
        ImGui::SameLine();
        ImGui::Text("M: %lu",ai.my_melee.size());
        ImGui::Text("My food: %i",ai.my_food);
        ImGui::Text("In prod: houses: %lu",ai.my_houses_prod.size());
        ImGui::SameLine();
        ImGui::Text("turrets: %lu",ai.my_turrets_prod.size());
        ImGui::End();


        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);


        if((!toggle_pause)&&(++frames_elapsed>=frames_per_tick))return;
        if(toggle_quit)return;

    }

}


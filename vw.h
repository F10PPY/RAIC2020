#ifndef VW_H
#define VW_H
#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "vw_shaders.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ai/ai.h"
using std::cout;
using std::endl;

using vertex = std::array<float, 3>;
class  vw
{
    //ImGui->
    bool toggle_quit=false;
    bool toggle_pause = false;
    bool toggle_grid = true;
    bool toggle_pf_busy=false;
    bool toggle_pf_build=false;
    bool toggle_pf_res=false;
    bool toggle_show_hp=true;
    bool toggle_builder_state=true;
    //<-ImGui
    static GLint  viewportX,viewportY;
    static GLsizei viewportW,viewportH;
    GLFWwindow* window;
    Shader shader_simple;
    Shader shader_geom;
    Shader shader_text;
    static const int map_len=80;
    static constexpr int map_len_sq=map_len*map_len;
    std::array<std::array<std::array<vertex,4>,map_len>,map_len> mapTilesVerts;
    std::array<std::array<vertex,2>,map_len_sq+2> mapGridVerts;
    float step=0.9f/map_len;
    vertex mapActionPoint{step/2,step/2,0};
    //  std::array<std::array<vertex,2>,map_len_sq+2> mapActionVerts;
    //  std::array<vertex,map_len_sq*2> mapActionVerts;

    unsigned int VAO_map_tiles,VBO_map_tiles,EBO_map_tiles;
    unsigned int VAO_map_grid,VBO_map_grid,EBO_map_grid;
    unsigned int VAO_map_action,VBO_map_actions;
    unsigned int VAO_text,VBO_text;

    /// Holds all state information relevant to a character as loaded using FreeType
    struct Character
    {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2   Size;      // Size of glyph
        glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Horizontal offset to advance to next glyph
    };
    std::map<GLchar, Character> Characters;

public:
    void prepareMapActionsVAO()
    {
        glGenVertexArrays(1, &VAO_map_action);
        glGenBuffers(1, &VBO_map_actions);

        glBindVertexArray(VAO_map_action);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_map_actions);
        glBufferData(GL_ARRAY_BUFFER, 3*sizeof(float), &mapActionPoint, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
//    void prepareMapActions()
//    {
//        mapActionPoint=
//        for(int i=0;i<map_len;i++)
//        {
//            for(int j=0;j<map_len;j++)
//            {
//                mapActionPoint[i][j][0]={i*step+step/2,j*step,0};
//                mapActionPoint[i][j][1]={i*step+step/2,j*step+step/2,0};
//            }

//        }
//    }

    void prepareMapGridVAO()
    {
        unsigned int indices[map_len*4+4];
        for(int n=0;n<map_len*4+4;n++)
        {
            indices[n]=n;
        }

        glGenVertexArrays(1, &VAO_map_grid);
        glGenBuffers(1, &VBO_map_grid);
        glGenBuffers(1, &EBO_map_grid);

        glBindVertexArray(VAO_map_grid);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_map_grid);
        glBufferData(GL_ARRAY_BUFFER, map_len_sq*2*3*sizeof(float)+4*3*sizeof(float), &mapGridVerts, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_map_grid);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);

    }

    void prepareMapTilesVAO()
    {

        unsigned int indices[map_len_sq*6];
        indices[0]=0;
        indices[1]=1;
        indices[2]=3;
        indices[3]=1;
        indices[4]=2;
        indices[5]=3;

        for(int n=6;n<map_len_sq*6;n++)
        {
            indices[n]=indices[n-6]+4;
        }
        //        float vertices[] = {
        //                0.5f,  0.5f, 0.0f,  // top right
        //                0.5f, -0.5f, 0.0f,  // bottom right
        //               -0.5f, -0.5f, 0.0f,  // bottom left
        //               -0.5f,  0.5f, 0.0f   // top left
        //           };

        glGenVertexArrays(1, &VAO_map_tiles);
        glGenBuffers(1, &VBO_map_tiles);
        glGenBuffers(1, &EBO_map_tiles);
        glBindVertexArray(VAO_map_tiles);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_map_tiles);
        glBufferData(GL_ARRAY_BUFFER, map_len_sq*4*3*sizeof(float), &mapTilesVerts[0][0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_map_tiles);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    void prepareMapGrid()
    {

        for(int i=0;i<=map_len;i++)
        {
            mapGridVerts[i][0]={0,i*step,0};
            mapGridVerts[i][1]={step*map_len,i*step,0};
        }
        for(int i=0;i<=map_len;i++)
        {
            mapGridVerts[i+map_len+1][0]={i*step,0,0};
            mapGridVerts[i+map_len+1][1]={i*step,step*map_len,0};
        }


    }
    void prepareMapTiles()
    {
      //  float gap=step/10;
       // gap=0;
       // float step_gap=step-gap;
        for(int i=0;i<map_len;i++)
        {
            for(int j=0;j<map_len;j++)
            {
                mapTilesVerts[i][j][0]={static_cast<float>(i*step),static_cast<float>(j*step),0};
                mapTilesVerts[i][j][1]={static_cast<float>(i*step+step),static_cast<float>(j*step),0};
                mapTilesVerts[i][j][2]={static_cast<float>(i*step+step),static_cast<float>(j*step+step),0};
                mapTilesVerts[i][j][3]={static_cast<float>(i*step),static_cast<float>(j*step+step),0};
            }
        }
    }
    bool prepareText();

    void renderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);

    void renderLoop(ai &ai);

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void glfw_error_callback(int error, const char* description);
    void terminate()
    {
        glDeleteVertexArrays(1, &VAO_map_tiles);
        glDeleteBuffers(1, &VBO_map_tiles);
        glDeleteBuffers(1, &EBO_map_tiles);
        glDeleteVertexArrays(1, &VAO_map_grid);
        glDeleteBuffers(1, &VBO_map_grid);
        glDeleteBuffers(1, &EBO_map_grid);
        glDeleteProgram(shader_simple.ID);
        glfwTerminate();
    }
    void processInput(GLFWwindow *window);

    inline bool init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        return true;
    }

    inline bool createWindow(int screen_w,int screen_h)
    {
        window = glfwCreateWindow(screen_w, screen_h, "RAIC2020 viewer", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetErrorCallback(glfw_error_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }
        //  viewportW=screen_w;
        //  viewportH=screen_h;
        viewportW=3000;
        viewportH=3000;
        viewportX=-1000;
        viewportY=-1480;
        shader_simple.load("simple.vs","simple.fs");
        shader_text.load("text.vs", "text.fs");
        shader_geom.load("my_geom.vs","my_geom.fs","my_geom.gs");
        return true;
    }
    inline void setGlOptions()
    {
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    inline void initImGui()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }
    void terminateImGui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
};





#endif // GR_INIT_H

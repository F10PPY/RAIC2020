#include "vw.h"

void vw::framebuffer_size_callback([[maybe_unused]]GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void vw::scroll_callback([[maybe_unused]]GLFWwindow* window,[[maybe_unused]] double xoffset, double yoffset)
{
    viewportX-=132*yoffset;
    viewportY-=132*yoffset;

    viewportW+=220*yoffset;
    viewportH+=220*yoffset;
    glViewport(viewportX,viewportY,viewportW,viewportH);

    // std::cout<<yoffset<<std::endl;
}
void vw::glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void vw::processInput(GLFWwindow *window)
{
    //    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    //    {
    //        toggle_show_hp=true;
    //    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {

        glfwSetWindowShouldClose(window, true);
        terminateImGui();
        terminate();
        exit(EXIT_SUCCESS);
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    static bool space=false;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        space=true;
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        if(space)
            toggle_pause=!toggle_pause;
        space=false;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        viewportY+=30;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        viewportY-=30;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        viewportX-=30;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        viewportX+=30;
    }
    glViewport(viewportX,viewportY,viewportW,viewportH);


}

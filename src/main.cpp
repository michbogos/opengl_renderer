#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <mesh.h>
#include <glm/gtx/transform.hpp>
#include<memory>

#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraFront = {0, 0, 0};
glm::vec3 cameraPos = {0, 0, 1};
glm::mat4x4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

std::vector<glm::vec3> lights = {{0.0, 0.0, -0.1}};

void setUniforms(Shader shader){
    shader.setUniform(lights, "lights");
    shader.setUniform((int)lights.size(), "lights_size");
    shader.setUniform(cameraPos, "cameraPos");
    shader.setUniform(glm::rotate(glm::translate(glm::mat4(1.0f), {0, 0, 0}), (float)glfwGetTime(), {glfwGetTime(), glfwGetTime(), glfwGetTime()}), "mat");
    shader.setUniform(view, "world");
    shader.setUniform(glm::lookAt(cameraPos,
    cameraPos+cameraFront, 
    glm::vec3(0.0f, 1.0f, 0.0f)), "view");
    shader.setUniform(glm::perspective<float>(3.14/2.0f, (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f), "proj");
}

void setSkyUniforms(Shader shader){
    shader.setUniform(lights, "lights");
    shader.setUniform((int)lights.size(), "lights_size");
    shader.setUniform(cameraPos, "cameraPos");
    shader.setUniform(glm::scale(glm::mat4(1.0f), {100, 100, 100}), "mat");
    shader.setUniform(view, "world");
    shader.setUniform(glm::lookAt({0.0f, 0.0f, 0.0f},
    cameraFront, 
    glm::vec3(0.0f, 1.0f, 0.0f)), "view");
    shader.setUniform(glm::perspective<float>(3.14/2.0f, (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f), "proj");
}

void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id,
   GLenum severity, GLsizei length, const GLchar* message, const void* userParam){
    if(severity == GL_DEBUG_SEVERITY_HIGH){
        std::cout << message << "\n";
    }
   }

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
double lastX;
double lastY;
double mouseYPrev = 300;
double pitch = 0.0;
double yaw = 0.0;

bool firstMouse = true;


void mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenglRenderer", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouseCallback);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(1);

    std::vector<TextureInfo> textures = {{"rocks/aerial_rocks_02_diff_1k.jpg", TextureType::diffuse}, {"rocks/aerial_rocks_02_disp_1k.png", TextureType::diffuse}, {"rocks/aerial_rocks_02_ao_1k.jpg", TextureType::diffuse}, {"rocks/aerial_rocks_02_rough_1k.png", TextureType::specular}, {"rocks/aerial_rocks_02_nor_gl_1k.png", TextureType::normal}};

    Shader light("light.vert", "light.frag", setUniforms);
    Shader sky_shader("sky.vert", "sky.frag", setSkyUniforms);
    Mesh obj("sphere.obj", textures);
    Mesh sky("sphere.obj", {{"sky.png", TextureType::diffuse}});

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugCallback, nullptr);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        double t1 = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        obj.draw(light);
        sky.draw(sky_shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
        double t2 = glfwGetTime();
        glfwSetWindowTitle(window, (std::to_string(1.0/(t2-t1))+" FPS").c_str());
    }
    light.cleanup();
    sky_shader.cleanup();
    obj.cleanup();
    sky.cleanup();

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        cameraPos += cameraFront*0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        cameraPos -= cameraFront*0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        cameraPos -= glm::normalize(glm::cross(cameraFront, {0, 1, 0}))*.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        cameraPos += glm::normalize(glm::cross(cameraFront, {0, 1, 0}))*.1f;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

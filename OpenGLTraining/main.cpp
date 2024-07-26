#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <UtilityInterface.h>
#include <ConfigInterface.h>
#include "GLFWWindow.h"
#include "VertexBuffer.h"
#include "Render.h"

void processInput(GLFWwindow* window);


int main()
{
    hiveWindow::CGLFWWindowConfig WindowConfig;
    hiveConfig::hiveParseConfig("Config.xml", hiveConfig::EConfigType::XML, &WindowConfig);

    std::shared_ptr<hiveWindow::CGLFWWindow> pGLFWWindow = std::make_shared<hiveWindow::CGLFWWindow>();
    if (!pGLFWWindow->readFormXML(WindowConfig))
    {
        HIVE_LOG_FATAL("Failed to read configuration");
        return -1;
    }
    if (!pGLFWWindow->initWindow())
    {
        HIVE_LOG_FATAL("Failed to create GLFWWindow");
        return -1;
    }

    hiveWindow::CAlgorithmConfig AlgorithmConfig;
    auto State = hiveConfig::hiveParseConfig("PerpixelShading.xml", hiveConfig::EConfigType::XML, &AlgorithmConfig);
    const std::string VertShaderPath = AlgorithmConfig.getAttribute<std::string>("shader_perpixel_shading_vs|SHADER_SOURCE_FILE").value();
    const std::string FragShaderPath = AlgorithmConfig.getAttribute<std::string>("shader_perpixel_shading_fs|SHADER_SOURCE_FILE").value();
    std::shared_ptr<hiveWindow::CShader> pShader = std::make_shared<hiveWindow::CShader>(VertShaderPath, FragShaderPath);
    
   GLFWwindow* Window = pGLFWWindow->getMyWindow();
   gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  
   

    std::vector<float> vertices = {
     -0.5f, -0.5f, 0.0f,   0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,// left  bottom
      0.5f, -0.5f, 0.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, 0.0f,// right bottom
     -0.5f, 0.5f, 0.0f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 1.0f,// left top
     -0.5f, 0.5f, 0.0f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 1.0f,// left top
      0.5f, 0.5f, 0.0f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f, 0.0f,// right top
      0.5f, -0.5f, 0.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, 0.0f,// right bottom
    };
    std::vector<int> AttributeLayout = { 3, 3, 3 };

    unsigned int VBO, VAO;
    hiveVertexBuffer::CVertexBuffer VertexBufferInit(vertices, AttributeLayout, GL_STATIC_DRAW, GL_TRIANGLES);

    while (!glfwWindowShouldClose(Window))
    {
        processInput(Window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        pShader->use();
        pShader->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        pShader->setUniform("lightPos", glm::vec3(0.0f, 0.0f, 3.0f));
        pShader->setUniform("viewPos", glm::vec3(0.0f, 0.0f, 3.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)pGLFWWindow->getWidth() / (float)pGLFWWindow->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        pShader->setUniform("projection", projection);
        pShader->setUniform("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        pShader->setUniform("model", model);

        VertexBufferInit.Draw();

        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
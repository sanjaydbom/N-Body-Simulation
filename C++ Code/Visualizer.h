#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Visualizer
{
    public:
        Visualizer(const int width = 800, const int height = 600, const float* bgColor = nullptr, const float* oColor = nullptr, const int m_precision = 50, const int m_num_circles = 1, const std::string title = "My OpenGL Window");
        bool render(const float* centers, const float* radii);
    private:
        void make_circle(const float* center, float* vertices, int* order, const float radius, const int offset);

        GLFWwindow* window;
        unsigned int VBO, VAO, EBO;
        unsigned int shaderProgram;
        const float* backgroundColor;
        int precision;
        int numCircles;
        GLint aspectRatioUniformLocation;
        float aspectRatio;
        float pi = 3.141592653589793;
};

#endif
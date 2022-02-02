#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "src/graphics/include/shader.h"
#include "src/graphics/include/texture_loader.h"

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

float mixValue = 0.2f; // stores how much we're seeing of either textures 

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mixValue += 0.001f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mixValue -= 0.001f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
}

float vertices[] = {
	// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
};

unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
};

int main()
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_WIDTH, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader ourShader("src/shaders/vertexShader.glsl", "src/shaders/fragmentShader.glsl");
	
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO); // We can generate multiple VAOs or buffers at the same time glGenVertexArrays(1, VAOs);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture1 = TextureLoader::loadAndGenerateTexture("C:\\Dev\\Alix_1.1\\textures\\container.jpg");   
	unsigned int texture2 = TextureLoader::loadAndGenerateTexture("C:\\Dev\\Alix_1.1\\textures\\awesomeface.png");
	
	ourShader.use();
	// glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // we can set it manually
	ourShader.setInt("texture1", 0); // or, due to the implementation of shader calss, with shader calass method setInt()
	ourShader.setInt("texture2", 1);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		//rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.setFloat("mixValue", mixValue);

		// transformations
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		ourShader.use();

		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// de-allocate all recources once they served well
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}
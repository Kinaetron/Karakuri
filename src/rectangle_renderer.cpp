#include <string>

#include "shader.h"
#include "matrix.h"
#include "rectangle_renderer.h"

RectangleRenderer::RectangleRenderer(const std::shared_ptr<const GraphicsDevice> graphicsDevice)
{
	std::string vertexShader = R"(
		#version 400 core

		layout (location = 0) in vec2 vertex;
	    layout (location = 1) in vec4 colour;

		out vec4 Colour;

		uniform mat4 matrix;

		void main()
		{
			Colour = colour;
			gl_Position = matrix * vec4(vertex, 0.0, 1.0);
		}
	)";

	std::string fragmentShader = R"(
		#version 400 core

		in vec4 Colour;
		out vec4 colour;

		void main()
		{
			colour = Colour;
		}
	)";

	Matrix<float> projection = Matrix<float>::OrthographicProjection(0, 
		 static_cast<float>(graphicsDevice->WindowWidth()),
		static_cast<float>(graphicsDevice->WindowHeight()), 0.0f, -1.0f, 1.0f);

	shader = new Shader(vertexShader, fragmentShader);

	shader->Use();
	shader->SetMatrix4("matrix", projection);

	float vertices[] =
	{
		// positions // colours 
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // top right
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // top right
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom right
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f  // top left 
	};

	unsigned int indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	unsigned int EBO;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &this->quadVAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(this->quadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RectangleRenderer::Draw(Rectangle destinationRectangle, Colour colour, unsigned short transparancy)
{
	Vector3<float> colourVector = colour.ToVector3();
	float transparancyFloat = transparancy / 255.0f;

	float vertices[] =
	{
		// positions												 // colour 
		destinationRectangle.Right(), destinationRectangle.Top(),    colourVector.X,  colourVector.Y, colourVector.Z, transparancyFloat,	// top right
		destinationRectangle.Right(), destinationRectangle.Bottom(), colourVector.X,  colourVector.Y, colourVector.Z, transparancyFloat,	// bottom right
		destinationRectangle.Left(),  destinationRectangle.Bottom(), colourVector.X,  colourVector.Y, colourVector.Z, transparancyFloat,	// bottom left
		destinationRectangle.Left(),  destinationRectangle.Top(),    colourVector.X,  colourVector.Y, colourVector.Z, transparancyFloat		// top left 
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->Use();

	glBindVertexArray(quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
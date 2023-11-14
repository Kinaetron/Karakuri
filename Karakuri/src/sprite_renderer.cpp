#include <iostream>
#include <glad/glad.h>
#include "../include/sprite_renderer.h"
#include "../include/vector2.h"
#include "../include/vector3.h"
#include "shader.h"

SpriteRenderer::SpriteRenderer(GraphicsDevice& device)
{
	InitalizeRenderData(device);
}

void SpriteRenderer::InitalizeRenderData(GraphicsDevice& device)
{
	Matrix<float> projection =  Matrix<float>::OrthographicProjection(0, static_cast<float>(device.WindowWidth()),
		static_cast<float>(device.WindowHeight()), 0.0f, -1.0f, 1.0f);

	shader = new Shader("shaders/sprite.vert", "shaders/sprite.frag");

	shader->Use();
	shader->SetInteger("image", 0);
	shader->SetMatrix4("projection", projection);
}

void SpriteRenderer::Draw(Texture& texture, Vector2<float> position, Rectangle draw_area, Vector2<float> size, float rotate, Colour colour, Matrix<float> camera)
{
	float left_texture_coordinate = draw_area.Left() / (float)texture.Width();
	float right_texture_coordinate = draw_area.Right() / (float)texture.Width();
	float top_texture_coordinate = 1.0f - draw_area.Top() / (float)texture.Height();
	float bottom_texture_coordinate = 1.0f - draw_area.Bottom() / (float)texture.Height();

	float vertices[] =
	{
		// positions // texture coords
		1.0f, 1.0f, right_texture_coordinate, top_texture_coordinate, // top right
		1.0f, 0.0f, right_texture_coordinate, bottom_texture_coordinate, // bottom right
		0.0f, 0.0f, left_texture_coordinate, bottom_texture_coordinate, // bottom left
		0.0f, 1.0f, left_texture_coordinate, top_texture_coordinate  // top left 
	};

	unsigned int indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int VBO, EBO;

	glGenVertexArrays(1, &this->quadVAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(this->quadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	this->shader->Use();

	Matrix<float> model = Matrix<float>::Identity();

	model = model.Translate(Vector3<float>(position.X, position.Y, 0.0f));

	model = model.Translate((Vector3<float>(size.X, size.Y, 0.0f) * 0.5f));
	model = model.Rotate(rotate);
	model = model.Translate((Vector3<float>(size.X, size.Y, 0.0f) * -0.5f));

	model = model.Scale(Vector3<float>(size.X, size.Y, 1.0f));

	this->shader->SetMatrix4("model", model);

	this->shader->SetMatrix4("camera", camera);

	this->shader->SetVector3f("spriteColor", colour.ToVector3());

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
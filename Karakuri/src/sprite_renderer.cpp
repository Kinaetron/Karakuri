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
	unsigned int VBO;
	float vertices[] = 
	{
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	Matrix<float> projection =  Matrix<float>::OrthographicProjection(0, static_cast<float>(device.WindowWidth()),
		static_cast<float>(device.WindowHeight()), 0.0f, -1.0f, 1.0f);

	shader = new Shader("shaders/sprite.vert", "shaders/sprite.frag");

	shader->Use();
	shader->SetInteger("image", 0);
	shader->SetMatrix4("projection", projection);
}

void SpriteRenderer::Draw(Texture& texture, Vector2<float> position, Vector2<float> size, float rotate, Vector3<float> color)
{
	this->shader->Use();

	Matrix<float> model = Matrix<float>::Identity();

	model.Translate(Vector3<float>(position.X, position.Y, 0.0f));

	model.Translate((Vector3<float>(size.X, size.Y, 0.0f) * 0.5f));
	model.Rotate(rotate);
	model.Translate((Vector3<float>(size.X, size.Y, 0.0f) * -0.5f));

	model.Scale(Vector3<float>(size.X, size.Y, 1.0f));

	this->shader->SetMatrix4("model", model);

	this->shader->SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
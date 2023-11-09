#include <iostream>
#include <glad/glad.h>
#include "../include/sprite_renderer.h"
#include "../include/glm/ext/matrix_clip_space.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
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

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(device.WindowWidth()),
		static_cast<float>(device.WindowHeight()), 0.0f, -1.0f, 1.0f);

	shader = new Shader("shaders/sprite.vert", "shaders/sprite.frag");

	shader->Use();
	shader->SetInteger("image", 0);
	shader->SetMatrix4("projection", projection);
}

void SpriteRenderer::Draw(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
	this->shader->Use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader->SetMatrix4("model", model);

	this->shader->SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
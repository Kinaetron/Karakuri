#include "collision.h"
#include <limits>
#include "../include/glm/gtx/norm.hpp"


glm::vec2 Collision::RectangleIntersectsCircle(Rectangle& rectangle, Circle& ciricle)
{
	glm::vec2 vertices[4] =
	{
		glm::vec2(rectangle.Left(), rectangle.Top()),
		glm::vec2(rectangle.Right(), rectangle.Top()),
		glm::vec2(rectangle.Right(), rectangle.Bottom()),
		glm::vec2(rectangle.Left(), rectangle.Bottom())
	};

	bool isOutside = false;
	glm::vec2 minCurrentVertex = glm::vec2(0, 0);
	glm::vec2 minNextVertex = glm::vec2(0, 0);
	float distanceCircleEdge = std::numeric_limits<float>::lowest();
	float maxProjection = std::numeric_limits<float>::lowest();

	for (int i = 0; i < 4; i++)
	{
		int currentVertex = i;
		int nextVertex = (i + 1) % 4;

		glm::vec2 edge = vertices[nextVertex] - vertices[currentVertex];
		glm::vec2 normal = this->normal(edge);

		glm::vec2 vertexToCircleCentre = ciricle.Position() - vertices[currentVertex];
		float projection = glm::dot(vertexToCircleCentre, normal);

		if (projection > 0.0f && projection > maxProjection)
		{
			maxProjection = projection;
			distanceCircleEdge = projection;
			minCurrentVertex = vertices[currentVertex];
			minNextVertex = vertices[nextVertex];
			isOutside = true;
			break;
		}
		else if (projection > distanceCircleEdge)
		{
			distanceCircleEdge = projection;
			minCurrentVertex = vertices[currentVertex];
			minNextVertex = vertices[nextVertex];
		}
	}


	if (isOutside)
	{
		glm::vec2 v1 = ciricle.Position() - minCurrentVertex;
		glm::vec2 v2 = minNextVertex - minCurrentVertex;

		if (glm::dot(v1, v2) < 0.0f)
		{
			if (glm::length(v1) > ciricle.Radius()) {
				return glm::vec2(0, 0);
			}
			else {
				return glm::normalize(v1) * (ciricle.Radius() - glm::length(v1));
			}
		}
		else
		{
			v1 = ciricle.Position() - minNextVertex;
			v2 = minCurrentVertex - minNextVertex;

			if (glm::dot(v1, v2) < 0)
			{
				if (glm::length(v1) > ciricle.Radius()) {
					return glm::vec2(0, 0);
				}
				else {
					return glm::normalize(v1) * (ciricle.Radius() - glm::length(v1));
				}
			}
			else
			{
				if (distanceCircleEdge > ciricle.Radius()) {
					return glm::vec2(0, 0);
				}
				else
				{
					glm::vec2 normal = this->normal((minNextVertex - minCurrentVertex));
					return normal * (ciricle.Radius() - distanceCircleEdge);
				}
			}
		}
	}

	glm::vec2 normal = this->normal(minNextVertex - minCurrentVertex);
	return normal * (ciricle.Radius() - distanceCircleEdge);
}

glm::vec2 Collision::normal(glm::vec2 vector) {
	return glm::normalize(glm::vec2(vector.y, -vector.x));
}

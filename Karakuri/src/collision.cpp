#include "collision.h"
#include <limits>


Vector2<float> Collision::RectangleIntersectsCircle(Rectangle& rectangle, Circle& ciricle)
{
	Vector2<float> vertices[4] =
	{
		Vector2<float>(rectangle.Left(), rectangle.Top()),
		Vector2<float>(rectangle.Right(), rectangle.Top()),
		Vector2<float>(rectangle.Right(), rectangle.Bottom()),
		Vector2<float>(rectangle.Left(), rectangle.Bottom())
	};

	bool isOutside = false;
	Vector2<float> minCurrentVertex = Vector2<float>::Zero();
	Vector2<float> minNextVertex = Vector2<float>::Zero();
	float distanceCircleEdge = std::numeric_limits<float>::lowest();
	float maxProjection = std::numeric_limits<float>::lowest();

	for (int i = 0; i < 4; i++)
	{
		int currentVertex = i;
		int nextVertex = (i + 1) % 4;

		Vector2<float> edge = vertices[nextVertex] - vertices[currentVertex];
		Vector2<float> normal = edge.Normal();

		Vector2<float> vertexToCircleCentre = ciricle.Position() - vertices[currentVertex];
		float projection = vertexToCircleCentre.Dot(normal);

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
		Vector2<float> v1 = ciricle.Position() - minCurrentVertex;
		Vector2<float> v2 = minNextVertex - minCurrentVertex;

		if (v1.Dot(v2) < 0.0f)
		{
			if (v1.Length() > ciricle.Radius()) {
				return Vector2<float>::Zero();
			}
			else {
				return v1.Normalize() * (ciricle.Radius() - v1.Length());
			}
		}
		else
		{
			v1 = ciricle.Position() - minNextVertex;
			v2 = minCurrentVertex - minNextVertex;

			if (v1.Dot(v2) < 0)
			{
				if (v1.Length() > ciricle.Radius()) {
					return Vector2<float>::Zero();
				}
				else {
					return v1.Normalize() * (ciricle.Radius() - v1.Length());
				}
			}
			else
			{
				if (distanceCircleEdge > ciricle.Radius()) {
					return Vector2<float>::Zero();
				}
				else
				{
					Vector2<float> normal = (minNextVertex - minCurrentVertex).Normal();
					return normal * (ciricle.Radius() - distanceCircleEdge);
				}
			}
		}
	}

	Vector2<float> normal = minNextVertex - minCurrentVertex.Normal();
	return normal * (ciricle.Radius() - distanceCircleEdge);
}

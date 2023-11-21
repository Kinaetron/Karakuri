#include "collision.h"
#include <limits>

Vector2<float> Collision::CirlcleIntersectsCircle(const Circle& circle1, const Circle& circle2)
{
	float radisSum = circle1.Radius() + circle2.Radius();
	Vector2<float> distanceVector = circle1.Position() - circle2.Position();

	float distance = distanceVector.Length();

	if (distance > radisSum) {
		return Vector2<float>::Zero();
	}

	float depth = radisSum - distance;
	Vector2<float> direction = (circle1.Position() - circle2.Position()).Normalize();

	return direction * depth;
}

Vector2<float> Collision::RectangleIntersectRectangle(const Rectangle& rectangle1, const Rectangle& rectangle2)
{
	float halfWidthA = rectangle1.Width() / 2.0f;
	float halfHeightA = rectangle2.Height() / 2.0f;

	float halfWidthB = rectangle2.Width() / 2.0f;
	float halfHeightB = rectangle2.Height() / 2.0f;

	Vector2<float> centreA = Vector2<float>(rectangle1.Left() + halfWidthA, rectangle1.Top() + halfHeightA);
	Vector2<float> centreB = Vector2<float>(rectangle2.Left() + halfWidthB, rectangle2.Top() + halfHeightB);

	float distanceX = centreA.X - centreB.X;
	float distanceY = centreA.Y - centreB.Y;

	float minDistanceX = halfWidthA + halfWidthB;
	float minDistanceY = halfHeightA + halfHeightB;

	if (std::abs(distanceX) >= minDistanceX || std::abs(distanceY) >= minDistanceY) {
		return Vector2<float>::Zero();
	}

	float depthX = distanceX > 0.0 ? minDistanceX - distanceX : -minDistanceX - distanceX;
	float depthY = distanceY > 0.0 ? minDistanceY - distanceY : -minDistanceY - distanceY;

	return Vector2<float>(depthX, depthY);
}

Vector2<float> Collision::RectangleIntersectsCircle(const Circle& ciricle, const Rectangle& rectangle)
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

#ifndef CELL_DATA_H
#define CELL_DATA_H

#include "texture.h"

class CellData
{
public:
	CellData(const CellData& that) = default;
	CellData(CellData&& that) = default;
	CellData& operator=(const CellData& rhs) = default;
	CellData& operator=(CellData&& rhs) = default;
	CellData(Texture&& texture, int duration);
	int Duration() const { return duration; }
	Texture& CellTexture() { return texture; }

private:
	const int duration;
	Texture texture;
};


#endif // !CELL_DATA_H
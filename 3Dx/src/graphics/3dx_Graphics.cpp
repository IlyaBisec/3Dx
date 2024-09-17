#include "../../include/graphics/3dx_Graphics.h"

bool DxGraphics::initialize(HWND hWnd, int width, int height)
{
	if (!initializeDirectX(hWnd, width, height))
		return false;

	return true;
}

bool DxGraphics::initializeDirectX(HWND hWnd, int width, int height)
{
	std::vector<GraphicAdapter> adapters = GraphicAdapterReader::getAdapters();

	return true;
}

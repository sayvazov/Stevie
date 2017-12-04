#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

namespace algorithm
{
	template<typename T> using matrix = std::vector<std::vector<T>>;
	template<typename T> std::unique_ptr<matrix<T>> createBlank(int size);
	template<typename T> std::unique_ptr<matrix<T>> createBlank(int size, T def);
	std::unique_ptr<matrix<float>> createPerlinNoise(int squareSize, int nodeSize, float magnitude, float center = 0);
	ci::Surface surfaceFromMatrix(matrix<float>& input);
	ci::Surface normalSurfaceFromMatrix(matrix<float>& input);

	
}
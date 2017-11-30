#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

namespace algorithm
{
	template<typename T>
	using matrix = std::vector<std::vector<T>>;

	bool addPerlin(std::vector<std::vector<float>>& values, int xDivisions, int yDivisions, float modifier);
	ci::Surface  generatePerlin(int divisions, int stepSize);
	ci::Surface surfaceFromMatrix(matrix<float>& input);
	std::unique_ptr<matrix<float>> createPerlinNoise(int squareSize, int nodeSize, float magnitude);
	std::unique_ptr<matrix<glm::vec3>> createPerlinSurface(int squareSize, int nodeSize, float magnitude);

	template<typename T> std::unique_ptr<matrix<T>> createBlank(int size);
	template<typename T> std::unique_ptr<matrix<T>> createBlank(int size, T def);
}
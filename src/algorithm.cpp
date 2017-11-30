#include "algorithm.h"
#include <glm/gtc/random.hpp>


using namespace algorithm;

namespace {
	float S(float x)
	{
		//return (x*x*x*-2) + (x*x * 3);
		return x;
		/*
		x = 1 / (x - 1.001) - 1 / (x+0.001);
		return glm::exp(x) / (1 + glm::exp(x));
		*/
	}
}

template<typename T>
std::unique_ptr<matrix<T>> algorithm::createBlank(int size)
{
	std::unique_ptr<matrix<T>> result = std::make_unique<matrix<T>>();
	result->resize(size);
	for (int x = 0; x < size; x++)
	{
		(*result)[x].resize(size);
	}
	return result;
}

template<typename T>
std::unique_ptr<matrix<T>> algorithm::createBlank(int size, T def)
{
	std::unique_ptr<matrix<T>> result = std::make_unique<matrix<T>>();
	result->resize(size);
	for (int x = 0; x < size; x++)
	{
		(*result)[x].resize(size);
		std::fill((*result)[x].begin(), (*result)[x].end(), def);
	}
	return result;
}

bool algorithm::createPerlinNoise(matrix<float> & target, int nodeSize, float magnitude)
{
	int squareSize = target.size();
	int height = target[0].size();
	if (squareSize != height)
		return false;
	if (nodeSize > squareSize)
		return false;


	int step = squareSize / nodeSize + 1;
	
	//Generate a random unit length vector for each node
	matrix<glm::vec2> nodes;
	nodes.resize(nodeSize+1);

	for (int x = 0; x <= nodeSize; x++)
	{
		nodes[x].resize(nodeSize+1);
		for (int y = 0; y <= nodeSize; y++)
		{
			nodes[x][y] = glm::circularRand(1.0);
		}
	}

	for (int x = 0; x < squareSize; x++)
	{
		int prevXNode = x / step;
		float xFraction = (float)(x % step) / step;
		for (int y = 0; y < squareSize; y++)
		{

			int prevYNode = y / step;
			float yFraction = (float)(y % step) / step;

			float total = 0;
			glm::vec2 distance(xFraction, yFraction);
			total += glm::dot(distance, nodes[prevXNode][prevYNode])*S(1 - xFraction)*S(1 - yFraction);

			distance = glm::vec2(1 - xFraction, yFraction);
			total += glm::dot(distance, nodes[prevXNode + 1][prevYNode]) * S(xFraction)*S(1 - yFraction);

			distance = glm::vec2(xFraction, 1 - yFraction);
			total += glm::dot(distance, nodes[prevXNode][prevYNode + 1]) * S(1 - xFraction)*S(yFraction);

			distance = glm::vec2(1 - xFraction, 1 - yFraction);
			total += glm::dot(distance, nodes[prevXNode + 1][prevYNode + 1]) * S(xFraction)*S(yFraction);

			target[x][y] += magnitude*total;
		}
	}
	return true;
}

std::unique_ptr<matrix<glm::vec3>> algorithm::createPerlinSurface(int squareSize, int nodeSize, float magnitude)
{
	std::unique_ptr<matrix<glm::vec3>> result = createBlank<glm::vec3>(squareSize);
	std::unique_ptr<matrix<float>> perlin = createBlank<float>(squareSize, 128);
	createPerlinNoise(perlin, nodeSize, magnitude);


	int step = squareSize / nodeSize + 1;

	//Generate a random unit length vector for each node
	matrix<glm::vec2> nodes;
	nodes.resize(nodeSize + 1);

	for (int x = 0; x <= nodeSize; x++)
	{
		nodes[x].resize(nodeSize + 1);
		for (int y = 0; y <= nodeSize; y++)
		{
			nodes[x][y] = glm::circularRand(1.0);
		}
	}

	return result;
}


ci::Surface algorithm::surfaceFromMatrix(matrix<float>& input)
{
	int width = input.size();
	int height = input[0].size();
	ci::Surface result = ci::Surface(width, height, true);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < width; y++)
		{
			ci::ColorA8u pixel(input[x][y], input[x][y], input[x][y], 255);
			result.setPixel(glm::ivec2(x, y), pixel);
		}
	}
	return result;
}


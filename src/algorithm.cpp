#include "algorithm.h"
#include <glm/gtc/random.hpp>


using namespace algorithm;

namespace {
	float S(float x)
	{
		return (x*x*x*-2) + (x*x * 3);
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

inline int whichSection( int sectionSize, int sectionsWithExtraElem, int elemNumber)
{
	int naive = elemNumber / (sectionSize + 1);
	if (naive < sectionsWithExtraElem)
		return naive;
	return (elemNumber - sectionsWithExtraElem) / sectionSize;
}

std::unique_ptr<matrix<float>> algorithm::createPerlinNoise(int squareSize, int numNodes, float magnitude, float center)
{
	std::unique_ptr<matrix<float>> result = algorithm::createBlank(squareSize, center);
	matrix<glm::vec2> nodes = *algorithm::createBlank<glm::vec2>(numNodes+1);
	for (int i = 0; i <= numNodes; i++)
	{
		for (int j = 0; j <= numNodes; j++)
		{
			nodes[i][j] = glm::circularRand(1.0f);
		}
	}
	
	int nodeSize = squareSize / numNodes;
	int nodesWithExtraElem = squareSize % numNodes;
	float distanceBetweenNodes = 1.0 / numNodes;
	float distanceBetweenVerts = 1.0 / squareSize;
	for (int i = 0; i < squareSize; i++)
	{
		int iNode = whichSection(nodeSize, nodesWithExtraElem, i);
		float iFrac = i*distanceBetweenVerts / distanceBetweenNodes - iNode;
		for (int j = 0; j < squareSize; j++)
		{
			int jNode = whichSection(nodeSize, nodesWithExtraElem, j);
			float jFrac = (j*distanceBetweenVerts / distanceBetweenNodes - jNode);

			glm::vec2 distance;
			float total = 0 ;

			if (jFrac > 0.1f && iFrac > 0.1f)
				jFrac *= 1.0001;

			distance = glm::vec2(iFrac, jFrac);
			total += glm::dot(distance, nodes[iNode][jNode]) * S(1-iFrac)*S(1-jFrac);

			distance = glm::vec2(iFrac-1, jFrac);
			total += glm::dot(distance, nodes[iNode+1][jNode]) * S(iFrac)*S(1-jFrac);

			distance = glm::vec2(iFrac, jFrac-1);
			total += glm::dot(distance, nodes[iNode][jNode+1]) * S(1-iFrac)*S(jFrac);

			distance = glm::vec2(iFrac-1, jFrac-1);
			total += glm::dot(distance, nodes[iNode+1][jNode+1]) * S(iFrac)*S(jFrac);

			total = glm::min(glm::max(-1.0f, total), 0.9f);
			result->at(i)[j] += total*magnitude;
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
			int val = (int)input[x][y];
			
			ci::ColorA8u pixel(val, val, val, 255);
			result.setPixel(glm::ivec2(x, y), pixel);
		}
	}
	return result;
}

// Assumes input on 
ci::Surface algorithm::normalSurfaceFromMatrix(matrix<float>& input)
{
	int width = input.size();
	int height = input[0].size();
	ci::Surface result = ci::Surface(width, height, true);
	for (int x = 1; x < width-1; x++)
	{
		for (int y = 1; y < width-1; y++)
		{
			float xPrev = input[x - 1][y];
			float yPrev = input[x][y - 1];
			float val   = input[x][y];
			float xNext = input[x + 1][y];
			float yNext = input[x][y + 1];

			glm::mat3 lin(1, -1, 1, 0, 0, 1, 1, 1, 1);
			glm::mat3 inv = glm::inverse(lin);
			glm::vec3 ySolve = glm::vec3(yPrev, val, yNext) * inv;
			glm::vec3 xSolve = glm::vec3(xPrev, val, xNext) * inv;
			float ySlope = ySolve.y * 128;
			float xSlope = xSolve.y*128;
			glm::vec3 normal(xSlope, ySlope, 1.0);
			glm::vec3 normalNormalized = glm::normalize(normal)*128.0f + 128.0f;


			ci::ColorA8u pixel(normalNormalized.x, normalNormalized.y, normalNormalized.z, 255);
			result.setPixel(glm::ivec2(x, y), pixel);
		}
	}
	return result;
}


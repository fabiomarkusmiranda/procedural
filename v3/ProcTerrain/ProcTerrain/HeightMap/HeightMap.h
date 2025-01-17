#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H



#include "../Util/Vertex.h"
#include "../Util/SimpleSquare.h"
#include "../Shaders/RenderingShader.h"
#include "../Shaders/GenerationShader.h"
#include "../Util/FBO.h"
#include "../Util/VBOSquare.h"


#include <windows.h>
#include "GL/glfw.h"
#include <pthread.h>
#include <iostream>
using namespace std;




class HeightMap{
	

protected:
	Vector3<float> m_relativePosition;
	//Vector3<float> m_globalPosition;
	

	
	char* m_heightMapArray;
	
	//FBO* m_ptrFBO;


	
	float m_geomSize;
	
	short m_textureSize;
	
	short m_numDivisions;


	//
	int m_octaves;
	float m_lacunarity;
	float m_gain;
	float m_offset;
	


public:
	HeightMap(Vector3<float> relativePosition, 
				float geomSize, short numDivisions, short textureSize,
				int octaves, float lacunarity, float gain, float offset);
	~ HeightMap();
	void SwapHeightMap(HeightMap* heightMap);
	void GenerateGPU(GenerationShader* ptrGenerationShader, Vector3<float> globalPosition);
	void GenerateCPU(char* ptrPermArray, Vector3<float> globalPosition);
	void Render(double, RenderingShader*);
	void Delete();
	void TransferToTexture();
	void BeginGeneration();
	void FinishGeneration();
	

	//Statics
	static float ridgedmf(char* ptrPermArray, Vector3<float> position, int octaves, float gain, float lacunarity, float offset);
	static float ridge(float h, float offset);
	static float fade(float t);
	static float noise(char* ptrPermArray, Vector3<float> P);
	static double grad(int hash, float x, float y, float z);
	static float mix(float weight, float a, float b);

	//Threads
	static void* CreateThread(void* ptrThis);

	pthread_mutex_t m_mutex;
	
	bool m_generated;
	bool m_beingGenerated;
	bool m_gpuOrCpu;
	GLuint m_heightMapId;

	

};

struct HeightMapThreadData{
   int  threadId;
   HeightMap *ptrThis;
   char *ptrPermArray;
   Vector3<float> globalPosition;
};

#endif
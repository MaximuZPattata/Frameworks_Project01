#include <cControlGameEngine.h>

#include "pch.h"
#include "GLWF_CallBacks.h"
#include "cMesh.h"
#include "cJsonReader.h"
#include "DetailsFromFile.h"
#include "cModelManipulator.h"
#include "cMap.h"
#include "cFrameRates.h"
#include "sPositionTracker.h"

//---------------------------Global Objects-----------------------------------------------

GLFWwindow* window;
cControlGameEngine gameEngine;
cJsonReader jsonReader;
sCameraDetailsFromFile camDetails;
cModelManipulator modelManipulator;
cGruntEnemyFactory gruntFactory;
cFrameRates frameRate;
cMap map;

std::vector<sPositionTracker*> modelCurrentPositionsList;
std::vector<sAnimationFrames*> animationFrameRateList;
std::vector<sModelDetailsFromFile> modelDetailsList;
std::vector<sLightDetailsFromFile> lightDetailsList;

int main()
{
    int result = 0;

    //--------------------------------Initialize Game Engine----------------------------------------

    window = gameEngine.InitializeGameEngine();

    if (window == NULL)
        exit(EXIT_FAILURE);

    //--------------------------------Loading Models, Lights and initial camera position from Json file---------------------------------------------

    bool jsonresult = jsonReader.ReadScene("SceneDescription.json", modelDetailsList, lightDetailsList, camDetails);

    if (jsonresult)
    {
        std::cout << "File read successfully !" << std::endl;

        modelManipulator.Initialize(&gameEngine, modelDetailsList);
        map.Initialize(modelDetailsList, &modelManipulator, animationFrameRateList, modelCurrentPositionsList);

        //------------------------Loading Initial Camera Position---------------------------------------------

        gameEngine.MoveCameraPosition(camDetails.initialCameraPosition.x, camDetails.initialCameraPosition.y, camDetails.initialCameraPosition.z);
    }
    else
        return -1;
    //-------------------------------Frame loop---------------------------------------------

    double lastTime = glfwGetTime();

    //map.SetEnemyFactory(&gruntFactory);

    while (!glfwWindowShouldClose(window))
    {
        //-------------------Calculate Delta time-------------------------------------------

        double currentTime = glfwGetTime();
        gameEngine.deltaTime = currentTime - lastTime;

        const double LARGEST_DELTA_TIME = 1.0f / 30.0f;

        if (gameEngine.deltaTime > LARGEST_DELTA_TIME)
            gameEngine.deltaTime = LARGEST_DELTA_TIME;

        lastTime = currentTime;
       
        float randomNum = gameEngine.getRandomFloat(1.0, 1.5);

        //-------------------Update frame rate & animations---------------------------------

        frameRate.UpdateFrameRates(animationFrameRateList);

        map.UpdateMap(animationFrameRateList, modelCurrentPositionsList);

        map.SpawnGruntEnemies((float)currentTime, randomNum, animationFrameRateList, modelCurrentPositionsList);

        //---------------------------Run Engine---------------------------------------------

        gameEngine.RunGameEngine(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    exit(EXIT_SUCCESS);

    std::cout << "Window closed !" << std::endl;

    return 0;
}
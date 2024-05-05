#include "GLWF_CallBacks.h"
#include "pch.h"
#include "cControlgameEngine.h"
#include "cPlayer.h"
#include "cMap.h"
#include "eDirection.h"

extern cControlGameEngine gameEngine;
extern cMap map;

float last_shot = 0.0f;

cMesh* controlMeshModel;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    //---------------Controls for Mesh Models----------------------------------------------------------

    if ((mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
    {
        controlMeshModel = gameEngine.GetCurrentModelSelected();

        std::string currentModelName = controlMeshModel->friendlyName;

        if (key == GLFW_KEY_Z && action) // Shift to previous model
        {
            gameEngine.ShiftToPreviousMeshInList();
        }
        if (key == GLFW_KEY_X && action) // Shift to next model
        {
            gameEngine.ShiftToNextMeshInList();
        }
        if (key == GLFW_KEY_B && action) // Change to wireframe mode
        {
            gameEngine.TurnWireframeModeOn(currentModelName);
        }
    }

    //-------------------Controls for Player-----------------------------------------------------------

    if (mods == 0)
    {
        eDirection playerDir;

    //-------------------Movement Controls--------------------------------------
        
        if (key == GLFW_KEY_UP && action)
        {
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            {
                playerDir = UP_LEFT;

                // Diagonally upper left
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
            else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            {
                playerDir = UP_RIGHT;

                // Diagonally upper right
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
            else
            {
                playerDir = UP;
                
                // Go up
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
        }
        if (key == GLFW_KEY_LEFT && action)
        {
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            {
                playerDir = UP_LEFT;

                // Diagonally upper left
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
            else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                playerDir = DOWN_LEFT;

                // Diagonally upper left
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
            else
            {
                playerDir = LEFT;

                // Go left
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
        }
        if (key == GLFW_KEY_RIGHT && action)
        {
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            {
                playerDir = UP_RIGHT;

                // Diagonally upper right
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
            else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                playerDir = DOWN_RIGHT;

                // Diagonally lower right
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
            else
            {
                playerDir = RIGHT;

                // Go right 
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
        }
        if (key == GLFW_KEY_DOWN && action)
        {
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            {
                playerDir = DOWN_LEFT;

                // Diagonally lower left
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
            else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            {
                playerDir = DOWN_RIGHT;

                // Diagonally lower right
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
            else
            {
                playerDir = DOWN;

                // Go down
                map.mThePlayer->PlayerDirectionChange(playerDir);
            }
        }

        //--------------Shooting Controls---------------------------------

        float differenceInTime = glfwGetTime() - last_shot;

        if (differenceInTime > 0.2f)
        {
            if (key == GLFW_KEY_W && action)
            {
                if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                {
                    playerDir = UP_LEFT;

                    // Diagonally upper left
                    map.mThePlayer->Attack(playerDir);
                }
                else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                {
                    playerDir = UP_RIGHT;

                    // Diagonally upper right
                    map.mThePlayer->Attack(playerDir);
                }
                else
                {
                    playerDir = UP;

                    // Go up
                    map.mThePlayer->Attack(playerDir);
                }

                last_shot = glfwGetTime();
            }
            if (key == GLFW_KEY_A && action)
            {
                if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                {
                    playerDir = UP_LEFT;

                    // Diagonally upper left
                    map.mThePlayer->Attack(playerDir);
                }
                else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                {
                    playerDir = DOWN_LEFT;

                    // Diagonally upper left
                    map.mThePlayer->Attack(playerDir);
                }
                else
                {
                    playerDir = LEFT;

                    // Go left
                    map.mThePlayer->Attack(playerDir);
                }

                last_shot = glfwGetTime();
            }
            if (key == GLFW_KEY_D && action)
            {
                if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                {
                    playerDir = UP_RIGHT;

                    // Diagonally upper right
                    map.mThePlayer->Attack(playerDir);
                }
                else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                {
                    playerDir = DOWN_RIGHT;

                    // Diagonally lower right
                    map.mThePlayer->Attack(playerDir);
                }
                else
                {
                    playerDir = RIGHT;

                    // Go right 
                    map.mThePlayer->Attack(playerDir);
                }

                last_shot = glfwGetTime();
            }
            if (key == GLFW_KEY_S && action)
            {
                if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                {
                    playerDir = DOWN_LEFT;

                    // Diagonally lower left
                    map.mThePlayer->Attack(playerDir);
                }
                else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                {
                    playerDir = DOWN_RIGHT;

                    // Diagonally lower right
                    map.mThePlayer->Attack(playerDir);
                }
                else
                {
                    playerDir = DOWN;

                    // Go down
                    map.mThePlayer->Attack(playerDir);
                }

                last_shot = glfwGetTime();
            }
        }
    }

    return;
}
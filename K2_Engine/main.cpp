
#include "Engine.h"
#include "Random.h"
#include <iostream>
#include <map>
#include "Animation.h"
#include "AnimationSystem.h"


extern Camera* camera;
int keyHit = 0;
int action = 0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
       // std::cout << "Hit" << key << std::endl;
        keyHit = key;
        action = action;
        return;
    }
}

float pitch = 0.0f;
float yaw = 0.0f;
float roll = 0.0f;

 

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera->ProcessMouseMovement(xpos, ypos);
    static bool firstMouse = true;
    static float lastX = 0.0f;
    static float lastY = 0.0f;

    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }


    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;

    lastX = (float)xpos;
    lastY = (float)ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;
}

int main(void)
{
    Engine engine;
    if (!engine.Initialize())
    {
        return 1;
    }

    engine.meshManager->LoadTexture("PaletteV1.bmp");
    bool loaded = engine.meshManager->LoadCubeMap("space",
                                    "CubeMaps/TropicalSunnyDayLeft2048.bmp",
                                    "CubeMaps/TropicalSunnyDayRight2048.bmp",
                                    "CubeMaps/TropicalSunnyDayUp2048.bmp",
                                    "CubeMaps/TropicalSunnyDayDown2048.bmp",
                                    "CubeMaps/TropicalSunnyDayFront2048.bmp",
                                    "CubeMaps/TropicalSunnyDayBack2048.bmp",
                                    true);



	camera->SetPosition(glm::vec3(0.0f, 400.0f, 200.0f));
 
    cMesh* skyBoxMesh = engine.LoadMesh("Sphere_1_unit_Radius_UV.ply", "skybox");
    skyBoxMesh->isSkyBox = true;
    skyBoxMesh->setUniformDrawScale(5000.0f);
 
    cMesh* milleniumFalcon = engine.LoadMesh("FalconBody.ply", "milleniumFalcon");
    milleniumFalcon->bUseDebugColours = true;


    cMesh* tieFighter = engine.LoadMesh("Asteroid_3.ply", "tieFighter");
    tieFighter->bUseDebugColours = true;


    cMesh* asteroid1 = engine.LoadMesh("TieFighter.ply", "asteroids");
    asteroid1->bUseDebugColours = true;

    cMesh* asteroid2 = engine.LoadMesh("Asteroid_3.ply", "tieFighter");
    asteroid2->bUseDebugColours = true;


    cMesh* asteroid3 = engine.LoadMesh("Asteroid_3.ply", "tieFighter");
    asteroid3->bUseDebugColours = true;

#pragma region Animation System 1

    AnimationSystem* animSystem = new AnimationSystem();

#pragma region Milleniun Falcon

    // Create a new animation for the Millenium Falcon
    Animation* animMilleniumFalcon = new Animation();
    animMilleniumFalcon->name = "MilleniumFalcon";
    animMilleniumFalcon->mesh = milleniumFalcon;
 
 
    animMilleniumFalcon->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, 20.0f), 0.0, EasingType::SineEaseIn));
    animMilleniumFalcon->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, -1000.0f), 2.0, EasingType::SineEaseIn));
    animMilleniumFalcon->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, -2000.0f), 4.0, EasingType::SineEaseOut));
    animMilleniumFalcon->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, -3000.0f), 6.0, EasingType::SineEaseOut));

    animMilleniumFalcon->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 0.0f), 0.0, EasingType::SineEaseIn));
    animMilleniumFalcon->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 1.6f), 2.0, EasingType::SineEaseIn));
    animMilleniumFalcon->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, -1.6f), 4.0, EasingType::SineEaseInOut));
    animMilleniumFalcon->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 1.6f), 6.0, EasingType::SineEaseOut));

    animMilleniumFalcon->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 0.0, EasingType::SineEaseIn));
    animMilleniumFalcon->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 2.0, EasingType::SineEaseIn));
    animMilleniumFalcon->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 4.0, EasingType::SineEaseInOut));
    animMilleniumFalcon->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 6.0, EasingType::SineEaseOut));

    animSystem->AddAnimation(animMilleniumFalcon);

#pragma endregion

#pragma region Tie Fighter

    // Create a new animation for the Tie Fighter
    Animation* animTieFighter = new Animation();
    animTieFighter->name = "Asteroids";
    animTieFighter->mesh = tieFighter;

    animTieFighter->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, 20.0f), 0.0, EasingType::SineEaseIn));
    animTieFighter->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, 20.0f), 2.0, EasingType::SineEaseIn));
    animTieFighter->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, 20.0f), 4.0, EasingType::SineEaseOut));
    animTieFighter->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, 20.0f), 6.0, EasingType::SineEaseOut));

    animTieFighter->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 0.0f), 0.0, EasingType::SineEaseIn));
    animTieFighter->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 1.6f), 2.0, EasingType::SineEaseIn));
    animTieFighter->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, -1.6f), 4.0, EasingType::SineEaseInOut));
    animTieFighter->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 1.6f), 6.0, EasingType::SineEaseOut));

    animTieFighter->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 0.0, EasingType::SineEaseIn));
    animTieFighter->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 2.0, EasingType::SineEaseIn));
    animTieFighter->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 4.0, EasingType::SineEaseInOut));
    animTieFighter->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 6.0, EasingType::SineEaseOut));

    animSystem->AddAnimation(animTieFighter);

#pragma endregion

#pragma endregion

#pragma region Animation System 2


    AnimationSystem* animSystem2 = new AnimationSystem();

#pragma region Asteroid 1

    // Create a new animation for the first asteroid
    Animation* animAsteroid1 = new Animation();
    animAsteroid1->name = "Asteroid1";
    animAsteroid1->mesh = asteroid1;

    animAsteroid1->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, 20.0f), 0.0, EasingType::SineEaseIn));
    animAsteroid1->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, -1000.0f), 2.0, EasingType::SineEaseOut));
    animAsteroid1->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, -2000.0f), 4.0, EasingType::SineEaseIn));


    animAsteroid1->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 0.0f), 0.0, EasingType::SineEaseIn));
    animAsteroid1->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 1.6f), 2.0, EasingType::SineEaseInOut));
    animAsteroid1->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, -1.6f), 4.0, EasingType::SineEaseInOut));


    animAsteroid1->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 0.0, EasingType::SineEaseIn));
    animAsteroid1->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 2.0, EasingType::SineEaseInOut));
    animAsteroid1->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 4.0, EasingType::SineEaseInOut));


    animSystem2->AddAnimation(animAsteroid1);

#pragma endregion

#pragma region Asterioid 2

    // Create a new animation for the second asteroid
    Animation* animAsteroid2 = new Animation();

    animAsteroid2->name = "Asteroid2";
    animAsteroid2->mesh = asteroid2;

    animAsteroid2->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, 20.0f), 0.0, EasingType::SineEaseIn));
    animAsteroid2->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, -1000.0f), 2.0, EasingType::SineEaseOut));
    animAsteroid2->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, -2000.0f), 4.0, EasingType::SineEaseIn));


    animAsteroid2->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 0.0f), 0.0, EasingType::SineEaseIn));
    animAsteroid2->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 1.6f), 2.0, EasingType::SineEaseInOut));
    animAsteroid2->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, -1.6f), 4.0, EasingType::SineEaseInOut));


    animAsteroid2->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 0.0, EasingType::SineEaseIn));
    animAsteroid2->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 2.0, EasingType::SineEaseInOut));
    animAsteroid2->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 4.0, EasingType::SineEaseInOut));


    animSystem2->AddAnimation(animAsteroid1);


#pragma endregion


#pragma region Asteriod 3
    // Create a new animation for the third asteroid
    Animation* animAsteroid3 = new Animation();

    animAsteroid3->name = "Asteroid3";
    animAsteroid3->mesh = asteroid2;

    animAsteroid3->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, 20.0f), 0.0, EasingType::SineEaseIn));
    animAsteroid3->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, -1000.0f), 2.0, EasingType::SineEaseOut));
    animAsteroid3->positionKeyFrames.push_back(PositionKeyFrame(glm::vec3(0.0f, 0.0f, -2000.0f), 4.0, EasingType::SineEaseIn));


    animAsteroid3->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 0.0f), 0.0, EasingType::SineEaseIn));
    animAsteroid3->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, 1.6f), 2.0, EasingType::SineEaseInOut));
    animAsteroid3->rotationKeyFrames.push_back(RotationKeyFrame(glm::vec3(0.0f, 0.0f, -1.6f), 4.0, EasingType::SineEaseInOut));


    animAsteroid3->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 0.0, EasingType::SineEaseIn));
    animAsteroid3->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 2.0, EasingType::SineEaseInOut));
    animAsteroid3->scaleKeyFrames.push_back(ScaleKeyFrame(glm::vec3(1.0f, 1.0f, 1.0f), 4.0, EasingType::SineEaseInOut));


    animSystem2->AddAnimation(animAsteroid1);

#pragma endregion
 

#pragma endregion
 
 
    unsigned long long frameNumber = 0;
    bool togglePause = false;
    bool reverse = false;

    // Set the callback for key presses
    while (!glfwWindowShouldClose(engine.window))
    {
        engine.Update();      
 
        //glm::vec3 direction = glm::normalize(milleniumFalcon->drawPosition - camera->cameraEye);
        //glm::vec3 followCamera = (milleniumFalcon->drawPosition + 800.0f);
        //camera->cameraTarget = direction;
        //camera->cameraEye = followCamera;
 
        if (keyHit == GLFW_KEY_SPACE)
        {
            togglePause = !togglePause;
            keyHit = 0;
        }

        if (keyHit == GLFW_KEY_1)
        {
            animSystem->animationSpeed = 1.0f;
			keyHit = 0;
		}
        if (keyHit == GLFW_KEY_2)
        {
			animSystem->animationSpeed = 2.0f;
            keyHit = 0;
        }
        if (keyHit == GLFW_KEY_3)
		{
            animSystem->animationSpeed = 3.0f;
            keyHit = 0;
        }
        if (keyHit == GLFW_KEY_4)
        {
            animSystem->animationSpeed = 4.0f;
            keyHit = 0;
        }
        if (keyHit == GLFW_KEY_5)
        {
            animSystem->animationSpeed = 5.0f;
            keyHit = 0;
        }
 
        if (togglePause)
        {
			animSystem->Pause();
            animSystem2->Pause();

		}
        else
        {
			animSystem->Resume();         
			animSystem2->Resume();         
             
            if (keyHit == GLFW_KEY_R)
            {
                reverse = !reverse;
                keyHit = 0;
            }

            if (reverse)
            {
				frameNumber--;
			}
            else
            {
				frameNumber++;
			}

            if (frameNumber > 2000) frameNumber = 0;
            float val = (float)frameNumber / 250.f;

            //animSystem->Update(val);
            //animSystem2->Update(val);
 
            if (keyHit == GLFW_KEY_LEFT)
            {
                // Toggle play for animSystem
                animSystem->Update(val);
            }
            else if (keyHit == GLFW_KEY_RIGHT)
            {
                // Toggle play for animSystem2
                animSystem2->Update(val);
            }
            else
            {
                // Default behavior, update both animation systems
                animSystem->Update(val);
                animSystem2->Update(val);
            }

		}
 
   
    }

    engine.ShutDown();
}

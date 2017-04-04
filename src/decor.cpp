//
// Created by sebastien on 02/04/17.
//

#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/SlopeRenderable.hpp"

#include "../include/dynamics/DynamicSystem.hpp"
#include "../include/dynamics/DampingForceField.hpp"
#include "../include/dynamics/ConstantForceField.hpp"
#include "../include/dynamics/SpringForceField.hpp"
#include "../include/dynamics/EulerExplicitSolver.hpp"

#include "../include/dynamics_rendering/DynamicSystemRenderable.hpp"
#include "../include/dynamics_rendering/ParticleRenderable.hpp"
#include "../include/dynamics_rendering/ParticleListRenderable.hpp"
#include "../include/dynamics_rendering/ConstantForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/SpringForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/SpringListRenderable.hpp"
#include "../include/dynamics_rendering/ControlledForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/QuadRenderable.hpp"

#include "../include/lighting/DirectionalLightRenderable.hpp"
#include "../include/lighting/PointLightRenderable.hpp"
#include "../include/lighting/SpotLightRenderable.hpp"
#include "../include/lighting/LightedCubeRenderable.hpp"
#include "../include/lighting/LightedCylinderRenderable.hpp"
#include "../include/lighting/LightedMeshRenderable.hpp"
#include "../include/lighting/LightedSlopeRenderable.hpp"



void initialize_decor_scene(Viewer &viewer) {
    //Set up a shader and add a 3D frame.
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
                                                                  "../shaders/flatFragment.glsl");
    viewer.addShaderProgram(flatShader);
    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);


   // SlopeRenderablePtr slope = std::make_shared<SlopeRenderable>(flatShader,20,50,20);
   // viewer.addRenderable(slope);

    //Define a transformation
    glm::mat4 parentTransformation, localTransformation;

    viewer.getCamera().setViewMatrix(
    glm::lookAt(glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)));
    //Define a directional light for the whole scene
    glm::vec3 d_direction = glm::normalize(glm::vec3(1 - tan(20),0,-1.0));
    glm::vec3 d_ambient(0.0,0.0,0.0), d_diffuse(0.3,0.3,0.1), d_specular(0.3,0.3,0.1);
    //glm::vec3 d_ambient(0.0,0.0,0.0), d_diffuse(0.0,0.0,0.0), d_specular(0.0,0.0,0.0);
    DirectionalLightPtr directionalLight = std::make_shared<DirectionalLight>(d_direction, d_ambient, d_diffuse, d_specular);
    //Add a renderable to display the light and control it via mouse/key event
    glm::vec3 lightPosition(25,25,10);
    DirectionalLightRenderablePtr directionalLightRenderable = std::make_shared<DirectionalLightRenderable>(flatShader, directionalLight, lightPosition);
    viewer.setDirectionalLight(directionalLight);
    viewer.addRenderable(directionalLightRenderable);

    //Define a point light
    glm::vec3 p_position(0.0,0.0,0.0), p_ambient(0.0,0.0,0.0), p_diffuse(0.0,0.0,0.0), p_specular(0.0,0.0,0.0);
    float p_constant=0.0, p_linear=0.0, p_quadratic=0.0;

    p_position = glm::vec3(-8, 5.0, 5.0);
    p_ambient = glm::vec3(0.0,0.0,0.0);
    p_diffuse = glm::vec3(1.0,0.0,0.0);
    p_specular = glm::vec3(1.0,0.0,0.0);
    p_constant=1.0;
    p_linear=5e-1;
    p_quadratic=0;
    PointLightPtr pointLight1 = std::make_shared<PointLight>(p_position, p_ambient, p_diffuse, p_specular, p_constant, p_linear, p_quadratic);
    PointLightRenderablePtr pointLightRenderable1 = std::make_shared<PointLightRenderable>(flatShader, pointLight1);
//    localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5,0.5,0.5));
//    pointLightRenderable1->setLocalTransform(localTransformation);
    viewer.addPointLight(pointLight1);
    viewer.addRenderable(pointLightRenderable1);

    p_position = glm::vec3(8, 5.0, 5.0);
    p_ambient = glm::vec3(0.0,0.0,0.0);
    p_diffuse = glm::vec3(0.0,0.0,1.0);
    p_specular = glm::vec3(0.0,0.0,1.0);
    p_constant=1.0;
    p_linear=5e-1;
    p_quadratic=0;
    PointLightPtr pointLight2 = std::make_shared<PointLight>(p_position, p_ambient, p_diffuse, p_specular, p_constant, p_linear, p_quadratic);
    PointLightRenderablePtr pointLightRenderable2 = std::make_shared<PointLightRenderable>(flatShader, pointLight2);
//    localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5,0.5,0.5));
//    pointLightRenderable2->setLocalTransform(localTransformation);
    viewer.addPointLight(pointLight2);
    viewer.addRenderable(pointLightRenderable2);

    //Define a spot light
    glm::vec3 s_position(0.0,5.0,-8.0), s_spotDirection = glm::normalize(glm::vec3(0.0,-1.0,1.0));
    //glm::vec3 s_ambient(0.0,0.0,0.0), s_diffuse(0.0,0.0,0.0), s_specular(0.0,0.0,0.0);
    glm::vec3 s_ambient(0.0,0.0,0.0), s_diffuse(0.5,0.5,0.5), s_specular(0.5,0.5,0.5);
    float s_constant=1.0, s_linear=0.0, s_quadratic=0.0;
    float s_cosInnerCutOff = std::cos(glm::radians(20.0f));
    float s_cosOuterCutOff = std::cos(glm::radians(40.0f));
    SpotLightPtr spotLight = std::make_shared<SpotLight>(s_position, s_spotDirection,
                                                         s_ambient, s_diffuse, s_specular,
                                                         s_constant, s_linear, s_quadratic,
                                                         s_cosInnerCutOff, s_cosOuterCutOff);
    SpotLightRenderablePtr spotLightRenderable = std::make_shared<SpotLightRenderable>(flatShader, spotLight);
//    localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5,0.5,0.5));
//    spotLightRenderable->setLocalTransform(localTransformation);
    viewer.addSpotLight(spotLight);
    viewer.addRenderable(spotLightRenderable);

    //Define materials
    glm::vec3 mAmbient(0.0), mDiffuse(0.0), mSpecular(0.0);
    float mShininess=0.0;
    MaterialPtr myMaterial = std::make_shared<Material>(mAmbient, mDiffuse, mSpecular, mShininess);
    MaterialPtr pearl = Material::Pearl();
    MaterialPtr bronze = Material::Bronze();
    MaterialPtr emerald = Material::Emerald();

    //Lighted slope
    LightedSlopeRenderablePtr slope = std::make_shared<LightedSlopeRenderable>(flatShader,20,pearl);
    slope->setMaterial(pearl);
    viewer.addRenderable(slope);


}
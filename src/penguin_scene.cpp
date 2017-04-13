/*
 * penguin_scene.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: ekhalyocthor
 */

#include "../include/Utils.hpp"
#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/ConeRenderable.hpp"
#include "../include/PineRenderable.hpp"
#include "../include/SlopeRenderable.hpp"
#include "../include/BasicTerrainGenerator.hpp"
#include "../include/PenguinLightedRenderable.hpp"
#include "../include/lighting/Lights.hpp"
#include "../include/lighting/DirectionalLightRenderable.hpp"
#include "../include/lighting/PointLightRenderable.hpp"
#include "../include/keyframes/KeyframedConeRenderable.hpp"
#include "../include/texturing/TexturedMeshRenderable.hpp"
#include "../include/lighting/LightedSlopeRenderable.hpp"
#include "../include/dynamics/DynamicSystem.hpp"
#include "../include/dynamics/DampingForceField.hpp"
#include "../include/dynamics/ConstantForceField.hpp"
#include "../include/dynamics/SpringForceField.hpp"
#include "../include/dynamics/EulerExplicitSolver.hpp"
#include "../include/dynamics_rendering/DynamicSystemRenderable.hpp"
#include "../include/dynamics/Particle.hpp"
#include "../include/dynamics_rendering/ConstantForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/ParticleRenderable.hpp"
#include "../include/SnowflakeLightedRenderable.hpp"
#include "../include/SnowballRenderable.hpp"


#include "../include/lighting/LightedConeRenderable.hpp"
#include <glm/gtc/matrix_transform.hpp>

void initialize_penguin_scene(Viewer &viewer) {
    //Set up a shader and add a 3D frame.
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
                                                                  "../shaders/flatFragment.glsl");
    viewer.addShaderProgram(flatShader);
    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);
    ShaderProgramPtr phongShader = std::make_shared<ShaderProgram>("../shaders/phongVertex.glsl",
                                                                   "../shaders/phongFragment.glsl");
    viewer.addShaderProgram(phongShader);

    ShaderProgramPtr texShader
            = std::make_shared<ShaderProgram>("../shaders/textureVertex.glsl",
                                              "../shaders/textureFragment.glsl");
    viewer.addShaderProgram(texShader);

    //Initialize a dynamic system (Solver, Time step, Restitution coefficient)
    DynamicSystemPtr system = std::make_shared<DynamicSystem>(viewer.getCamera(), false);
    EulerExplicitSolverPtr solver = std::make_shared<EulerExplicitSolver>();
    system->setSolver(solver);
    system->setDt(0.01);

    system->setRestitution(1);

    //Create a renderable associated to the dynamic system
    //This renderable is responsible for calling DynamicSystem::computeSimulationStep()in the animate() function
    //It also handles some of the key/mouse events
    DynamicSystemRenderablePtr systemRenderable = std::make_shared<DynamicSystemRenderable>(system);
    viewer.addRenderable(systemRenderable);

    //Define a transformation
    glm::mat4 parentTransformation, localTransformation;
    GeometricTransformation parentGeoTransform, localGeoTransform;

    //Define a directional light for the whole scene
    glm::vec3 d_direction = glm::normalize(glm::vec3(0.0, 0.0, -1.0));
    glm::vec3 d_ambient(0.3, 0.3, 0.3), d_diffuse(0.9, 0.9, 0.9), d_specular(0.5, 0.5, 0.5);
    //glm::vec3 d_ambient(0.0,0.0,0.0), d_diffuse(0.0,0.0,0.0), d_specular(0.0,0.0,0.0);
    DirectionalLightPtr directionalLight = std::make_shared<DirectionalLight>(d_direction,
                                                                              d_ambient, d_diffuse, d_specular);
    //Add a renderable to display the light and control it via mouse/key event
    glm::vec3 lightPosition(0.0, 5.0, 8.0);
    DirectionalLightRenderablePtr directionalLightRenderable = std::make_shared<
            DirectionalLightRenderable>(flatShader, directionalLight, lightPosition);
    localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5, 0.5, 0.5));
    directionalLightRenderable->setLocalTransform(localTransformation);
    viewer.setDirectionalLight(directionalLight);
    viewer.addRenderable(directionalLightRenderable);

    glm::vec3 p_position(0.0, 0.0, 0.0), p_ambient(0.0, 0.0, 0.0), p_diffuse(0.0, 0.0, 0.0),
            p_specular(0.0, 0.0, 0.0);
    float p_constant = 0.0, p_linear = 0.0, p_quadratic = 0.0;

    // add a point light
    p_position = glm::vec3(-2.0, 5.0, 5.0);
    p_ambient = glm::vec3(0.1, 0.1, 0.1);
    p_diffuse = glm::vec3(1.0, 1.0, 1.0);
    p_specular = glm::vec3(1.0, 1.0, 1.0);
    p_constant = 1.0;
    p_linear = 1e-1;
    p_quadratic = 0;
    PointLightPtr pointLight1 = std::make_shared<PointLight>(p_position, p_ambient, p_diffuse,
                                                             p_specular, p_constant, p_linear, p_quadratic);
    PointLightRenderablePtr pointLightRenderable1 = std::make_shared<PointLightRenderable>(
            flatShader, pointLight1);
    localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5, 0.5, 0.5));
    pointLightRenderable1->setLocalTransform(localTransformation);
    viewer.addPointLight(pointLight1);
    viewer.addRenderable(pointLightRenderable1);

    /*
    KeyframedConeRenderablePtr leaves = std::make_shared<KeyframedConeRenderable>(phongShader,
            Material::Emerald(),
            glm::vec4(1, 1, 1, 0), glm::vec4(0, 0.5, 0, 0), glm::vec4(0, 0.5, 0, 0),
            glm::vec4(0, 0, 0, 0), 8, 0.1);

    localGeoTransform = GeometricTransformation(glm::vec3(-1, 0, 0),
            quatAxisAngle(M_PI/2, glm::vec3(1, 0, 0)), glm::vec3(2, 2, 0.5));
    leaves->setLocalTransform(localGeoTransform);
    leaves->shake(2, 2, 0.3);
    viewer.addRenderable(leaves);
    */
//pine
    PineRenderablePtr sapin = std::make_shared<PineRenderable>(phongShader, 5, 1.5);
    sapin->bindTrunk(sapin);
    sapin->setParentTransform(GeometricTransformation(glm::vec3(2.0, 0.0, 0.0)));
    sapin->fell(0, glm::vec3(1, 0, 0), 4);
    viewer.addRenderable(sapin);

//Penguin
    PenguinLightedRenderablePtr Tux = std::make_shared<PenguinLightedRenderable>(texShader, system);
    Tux->bindMembers(Tux);
    Tux->bindForceController(systemRenderable);

    viewer.addRenderable(Tux);
    Tux->walkTux(viewer,texShader,0.0,2);
    Tux->walkTux(viewer,texShader,2.0,2);
    //Tux->jumpTux(viewer,texShader,4.0,1);
    Tux->collisionTux(viewer,texShader,6.0,2,glm::vec3(-0.5,-0.5,0));


    PenguinLightedRenderablePtr otherTux = std::make_shared<PenguinLightedRenderable>(texShader,system);
    otherTux->bindMembers(otherTux);
    otherTux->bindForceController(systemRenderable);
    GeometricTransformation tuxTransform = otherTux->getParentStaticTransform();
    tuxTransform.setTranslation(glm::vec3(0));
    tuxTransform.setOrientation(glm::quat());
    otherTux->setParentTransform(tuxTransform);

    otherTux->updateModelMatrix();
    otherTux->setStatus(PENGUIN_STATUS_SLIDING);
    ParticlePtr tuxParticle = otherTux->getParticle();
    tuxParticle->setFixed(false);
    tuxParticle->setVelocity(glm::vec3(-0.2, 0.8, 0.3));
    viewer.addRenderable(otherTux);

    //slope
    MaterialPtr slopeMaterial = std::make_shared<Material>(glm::vec3(glm::vec4(1.0,1.0,1.0,0.0)),
                                                           glm::vec3(glm::vec4(0.5,0.5,0.5,0.0)),
                                                           glm::vec3(0.0,0.0,0.0), 0.2);
    BasicTerrainGenerator terrain(0.7);
    LightedSlopeRenderablePtr slope = std::make_shared<LightedSlopeRenderable>(phongShader,terrain,slopeMaterial);
    slope->setMaterial(slopeMaterial);
    viewer.addRenderable(slope);
//snow

//    SnowflakeLightedRenderablePtr SF;
//
//    for (int i = -3; i < 3; ++i) {
//        for (int j = 0; j < 5; ++j) {
//        SF = std::make_shared<SnowflakeLightedRenderable>(texShader, glm::vec3(2*i, 2*j, random(5.0f,10.0f)));
//        ParticlePtr sfParticle = SF->getParticle();
//        system->addParticle(sfParticle);
//        HierarchicalRenderable::addChild(systemRenderable, SF);
//        }
//    }
    // this needs to be after the penguin(s) has been created
    ConstantForceFieldPtr gravity = std::make_shared<ConstantForceField>(system->getParticles(), glm::vec3(0, 0, -10));
    system->addForceField(gravity);

    //Initialize another dynamic system for the snow
    DynamicSystemPtr systemSnow = std::make_shared<DynamicSystem>(viewer.getCamera(), true);
    EulerExplicitSolverPtr solverSnow = std::make_shared<EulerExplicitSolver>();
    systemSnow->setSolver(solverSnow);
    systemSnow->setDt(0.01);

    //Create a renderable associated to the dynamic system
    //This renderable is responsible for calling DynamicSystem::computeSimulationStep()in the animate() function
    //It also handles some of the key/mouse events
    DynamicSystemRenderablePtr systemSnowRenderable = std::make_shared<DynamicSystemRenderable>(systemSnow);
    viewer.addRenderable(systemSnowRenderable);
//    SnowballRenderablePtr SF;
//    glm::vec3 pv(0.0, 0.0, 0.0);
//    glm::vec3 px(0.0, 0.0, 0.0);
//    float pm = 0.1, pr = 0.15;
//    ParticlePtr particle;
//    for (int i = -5; i < 5; ++i) {
//        for (int j = 0; j < 10; ++j) {
//            px = glm::vec3(2*i, 2*j, random(5.0f,10.0f));
//            particle = std::make_shared<Particle>(px, pv, pm, pr);
//            SF = std::make_shared<SnowballRenderable>(flatShader,particle);
//            systemSnow->addParticle(particle);
//            HierarchicalRenderable::addChild(systemSnowRenderable, SF);
//        }
//    }
    Tux->generateSnow(viewer, flatShader, systemSnow, systemSnowRenderable);

    ConstantForceFieldPtr gravityForceField = std::make_shared<ConstantForceField>(systemSnow->getParticles(), glm::vec3{0,0,-10} );
    DampingForceFieldPtr frottement = std::make_shared<DampingForceField>(systemSnow->getParticles(), 0.5 );
    systemSnow->addForceField(gravityForceField);
    systemSnow->addForceField(frottement);


    viewer.getCamera().setViewMatrix(
            glm::lookAt(glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)));
    viewer.startAnimation();
}



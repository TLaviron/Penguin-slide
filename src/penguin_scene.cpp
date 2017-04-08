/*
 * penguin_scene.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: ekhalyocthor
 */

#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/ConeRenderable.hpp"
#include "../include/PineRenderable.hpp"
#include "../include/SlopeRenderable.hpp"
#include "../include/BasicTerrainGenerator.hpp"
#include "../include/lighting/Lights.hpp"
#include "../include/lighting/DirectionalLightRenderable.hpp"
#include "../include/lighting/PointLightRenderable.hpp"
#include "../include/keyframes/KeyframedConeRenderable.hpp"
#include "../include/texturing/TexturedMeshRenderable.hpp"
#include "../include/lighting/LightedSlopeRenderable.hpp"

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

    KeyframedConeRenderablePtr leaves = std::make_shared<KeyframedConeRenderable>(phongShader,
            Material::Emerald(),
            glm::vec4(1, 1, 1, 0), glm::vec4(0, 0.5, 0, 0), glm::vec4(0, 0.5, 0, 0),
            glm::vec4(0, 0, 0, 0), 8, 0.1);

    localGeoTransform = GeometricTransformation(glm::vec3(-1, 0, 0),
            glm::quat(glm::vec3(0, 0, 0)), glm::vec3(2, 2, 0.5));
    leaves->setLocalTransform(localGeoTransform);
    leaves->shake(2, 2, 0.3);
    viewer.addRenderable(leaves);

    PineRenderablePtr sapin = std::make_shared<PineRenderable>(phongShader, 5, 1.5);
    sapin->bindTrunk(sapin);
    glm::mat4 translationM = glm::translate(glm::mat4(1.0), glm::vec3(2.0, 0.0, 0.0));
    sapin->setParentTransform(translationM);

    //TEST
    ShaderProgramPtr texShader
            = std::make_shared<ShaderProgram>("../shaders/textureVertex.glsl",
                                              "../shaders/textureFragment.glsl");
    viewer.addShaderProgram(texShader);

    MaterialPtr pearl = Material::Pearl();

    TexturedMeshRenderablePtr TuxBody =
            std::make_shared<TexturedMeshRenderable>(
                    texShader, "../tux/TuxBody.obj", "../tux/TuxBody.png");
    TuxBody->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(0, 4.5, 2.35));
    parentTransformation = glm::rotate( parentTransformation, float(M_PI_2), glm::vec3(1,0,0));
    parentTransformation = glm::rotate( parentTransformation, float(M_PI_2), glm::vec3(0,1,0));
    parentTransformation = glm::scale( parentTransformation, glm::vec3(2,2,2));
    TuxBody->setParentTransform( parentTransformation );
    viewer.addRenderable(TuxBody);

    TexturedMeshRenderablePtr TuxRF =
            std::make_shared<TexturedMeshRenderable>(
                    texShader, "../tux/RightFoot.obj", "../tux/RightFoot.png");
    TuxRF->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(0.8, 4.2, 1.0));
    parentTransformation = glm::rotate( parentTransformation, float(M_PI_2), glm::vec3(1,0,0));
    parentTransformation = glm::rotate( parentTransformation, float(M_PI_2), glm::vec3(0,1,0));
    parentTransformation = glm::scale( parentTransformation, glm::vec3(2,2,2));
    TuxRF->setParentTransform( parentTransformation );
    viewer.addRenderable(TuxRF);

    TexturedMeshRenderablePtr TuxLF =
            std::make_shared<TexturedMeshRenderable>(
                    texShader, "../tux/LeftFoot.obj", "../tux/leftFoot.png");
    TuxLF->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(-0.7, 4.2, 1.0));
    parentTransformation = glm::rotate( parentTransformation, float(M_PI_2), glm::vec3(1,0,0));
    parentTransformation = glm::rotate( parentTransformation, float(M_PI_2), glm::vec3(0,1,0));
    parentTransformation = glm::scale( parentTransformation, glm::vec3(2,2,2));
    TuxLF->setParentTransform( parentTransformation );
    viewer.addRenderable(TuxLF);

    TexturedMeshRenderablePtr TuxLH =
            std::make_shared<TexturedMeshRenderable>(
                    texShader, "../tux/LeftHand.obj", "../tux/LeftHand.png");
    TuxLH->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(-1.03, 4, 2.3));
    parentTransformation = glm::rotate( parentTransformation, float(M_PI_2), glm::vec3(1,0,0));
    parentTransformation = glm::rotate( parentTransformation, float(M_PI_2), glm::vec3(0,1,0));
    parentTransformation = glm::scale( parentTransformation, glm::vec3(2,2,2));
    TuxLH->setParentTransform( parentTransformation );
    viewer.addRenderable(TuxLH);

    TexturedMeshRenderablePtr TuxRH =
            std::make_shared<TexturedMeshRenderable>(
                    texShader, "../tux/RightHand.obj", "../tux/RightHand.png");
    TuxRH->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(1.09, 4, 2.3));
    parentTransformation = glm::rotate( parentTransformation, float(M_PI_2), glm::vec3(1,0,0));
    parentTransformation = glm::rotate( parentTransformation, float(M_PI_2), glm::vec3(0,1,0));
    parentTransformation = glm::scale( parentTransformation, glm::vec3(2,2,2));
    TuxRH->setParentTransform( parentTransformation );
    viewer.addRenderable(TuxRH);
    MaterialPtr slopeMaterial = std::make_shared<Material>(glm::vec3(glm::vec4(1.0,1.0,1.0,0.0)),
                                                           glm::vec3(glm::vec4(0.5,0.5,0.5,0.0)),
                                                           glm::vec3(0.0,0.0,0.0), 0.2);
    BasicTerrainGenerator terrain(0.7);
    LightedSlopeRenderablePtr slope = std::make_shared<LightedSlopeRenderable>(phongShader,terrain,slopeMaterial);
    slope->setMaterial(slopeMaterial);
    viewer.addRenderable(slope);


    viewer.addRenderable(sapin);
    viewer.getCamera().setViewMatrix(
            glm::lookAt(glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)));
    viewer.startAnimation();
    viewer.setAnimationLoop(true, 5);


}



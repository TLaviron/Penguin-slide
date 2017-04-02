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
#include <glm/gtc/matrix_transform.hpp>

void initialize_penguin_scene(Viewer &viewer) {
    //Set up a shader and add a 3D frame.
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
            "../shaders/flatFragment.glsl");
    viewer.addShaderProgram(flatShader);
    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);

    ConeRenderablePtr leaves = std::make_shared<ConeRenderable>(flatShader,
            glm::vec4(1, 1, 1, 0), glm::vec4(0, 0.5, 0, 0), glm::vec4(0, 0.5, 0, 0),
            glm::vec4(0, 0, 0, 0), 9, 0.1);
    //?
    viewer.addRenderable(leaves);

    PineRenderablePtr sapin = std::make_shared<PineRenderable>(flatShader, 5, 0);
    sapin->bindTrunk(sapin);
    glm::mat4 translationM = glm::translate(glm::mat4(1.0), glm::vec3(2.0, 0.0, 0.0));
    sapin->setParentTransform(translationM);

    viewer.addRenderable(sapin);

}



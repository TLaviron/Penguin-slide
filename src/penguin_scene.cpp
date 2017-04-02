/*
 * penguin_scene.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: ekhalyocthor
 */

#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/ConeRenderable.hpp"

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
    viewer.addRenderable(leaves);


}



//
// Created by sebastien on 02/04/17.
//

#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/SlopeRenderable.hpp"
#include "../include/BasicTerrainGenerator.hpp"
#include "../teachers/CubeRenderable.hpp"
#include "../teachers/IndexedCubeRenderable.hpp"



void initialize_decor_scene(Viewer &viewer) {
    //Set up a shader and add a 3D frame.
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
                                                                  "../shaders/flatFragment.glsl");
    viewer.addShaderProgram(flatShader);
    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);

    BasicTerrainGenerator terrain(0.75);
    SlopeRenderablePtr slope = std::make_shared<SlopeRenderable>(flatShader,20,terrain);
    viewer.addRenderable(slope);

}
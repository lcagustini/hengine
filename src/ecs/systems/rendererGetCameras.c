#include <ecs/systems.h>

static void setupCamera(struct transformComponent *transform, struct cameraComponent *camera, struct meshRenderData *renderData) {
	renderData->uniforms[renderData->uniformsLength++] = (struct uniformRenderData) {
		.type = RENDERER_UNIFORM_MATRIX_4,
		.location = renderData->shader.viewLoc,
		.count = 1,
		.data.matrix = camera->viewMat
	};

	renderData->uniforms[renderData->uniformsLength++] = (struct uniformRenderData) {
		.type = RENDERER_UNIFORM_MATRIX_4,
		.location = renderData->shader.projectionLoc,
		.count = 1,
		.data.matrix = camera->projectionMat
	};

	renderData->uniforms[renderData->uniformsLength++] = (struct uniformRenderData) {
		.type = RENDERER_UNIFORM_VECTOR_3,
		.location = renderData->shader.cameraPosLoc,
		.count = 1,
		.data.vector3 = transform->position
	};
}

void rendererGetCameras(struct systemRunData data) {
    struct transformComponent *transforms = GET_SYSTEM_COMPONENTS(data, 0, 0);
    struct cameraComponent *cameras = GET_SYSTEM_COMPONENTS(data, 0, 1);
    struct rendererDataComponent *rendererDatas = GET_SYSTEM_COMPONENTS(data, 0, 2);

    for (int i = 0; i < GET_SYSTEM_COMPONENTS_LENGTH(data, 0); i++) {
        struct transformComponent *transform = &transforms[i];
        struct cameraComponent *camera = &cameras[i];
        struct rendererDataComponent *rendererData = &rendererDatas[i];

        for (int j = 0; j < rendererData->opaqueMeshesLength; j++) {
			struct meshRenderData *renderData = &rendererData->opaqueMeshes[j];
			setupCamera(transform, camera, renderData);
        }

        for (int j = 0; j < rendererData->transparentMeshesLength; j++) {
			struct meshRenderData *renderData = &rendererData->transparentMeshes[j];
			setupCamera(transform, camera, renderData);
        }
    }
}
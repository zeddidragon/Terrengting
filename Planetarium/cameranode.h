#include "encapsulationnode.h"
#include "orientationnode.h"
#include "camera.h"

class CameraNode : public EncapsulationNode {
public:
	CameraNode(OrientationNode* node, Camera* camera);

	virtual void Update(float secondsPassed) override;

protected:
	Camera* _camera;
};
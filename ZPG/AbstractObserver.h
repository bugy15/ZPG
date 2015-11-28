// The Abstract Observer
#pragma once

class Camera; //dopredna deklarace (z duvodu krizoveho odkazu)
class Light;

class AbstractObserver
{
public:
	virtual void updateCamera(Camera *camera) = 0;
	virtual void updateLight(Light * light) = 0;
};

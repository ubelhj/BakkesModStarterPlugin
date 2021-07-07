#include "pch.h"
#include "CoolPlugin.h"


BAKKESMOD_PLUGIN(CoolPlugin, "Cool Plugin", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void CoolPlugin::onLoad()
{
	_globalCvarManager = cvarManager;
	
	cvarManager->log("Hello I'm CoolPlugin B)");
	cvarManager->registerNotifier("CoolerBallOnTop", [this](std::vector<std::string> args) {
		ballOnTop();
	}, "", PERMISSION_ALL);
}

void CoolPlugin::onUnload() {
	cvarManager->log("I was too cool for this world B'(");
}

void CoolPlugin::ballOnTop() {
	if (!gameWrapper->IsInFreeplay()) { return; }
	ServerWrapper server = gameWrapper->GetCurrentGameState();
	if (!server) { return; }

	BallWrapper ball = server.GetBall();
	if (!ball) { return; }
	CarWrapper car = gameWrapper->GetLocalCar();
	if (!car) { return; }

	Vector carVelocity = car.GetVelocity();
	ball.SetVelocity(carVelocity);

	Vector carLocation = car.GetLocation();
	float ballRadius = ball.GetRadius();
	ball.SetLocation(carLocation + Vector{ 0, 0, ballRadius * 2 });
}
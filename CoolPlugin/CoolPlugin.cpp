#include "pch.h"
#include "CoolPlugin.h"


BAKKESMOD_PLUGIN(CoolPlugin, "Cool Plugin", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
bool coolEnabled = false;

void CoolPlugin::onLoad()
{
	_globalCvarManager = cvarManager;
	
	cvarManager->log("Hello I'm CoolPlugin B)");
	cvarManager->registerNotifier("CoolerBallOnTop", [this](std::vector<std::string> args) {
		ballOnTop();
	}, "", PERMISSION_ALL);

	cvarManager->registerCvar("cool_enabled", "0", "Enable Cool", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			coolEnabled = cvar.getBoolValue();
			});

	gameWrapper->LoadToastTexture("cool", gameWrapper->GetDataFolder() / "cool.png");

	cvarManager->registerNotifier("cool_toast", [this](std::vector<std::string> args) {
		gameWrapper->Toast("Whoa you're cool", "Super cool", "cool", 5.0, ToastType_Warning);
		}, "", PERMISSION_ALL);

	cvarManager->registerCvar("cool_distance", "200.0", "Distance to place the ball above");

	cvarManager->registerCvar("cool_color", "#FFFFFF", "color of overlay");

	gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
		Render(canvas);
	});

	cvarManager->registerCvar("cool_x_location", "0", "set x location of the overlay");
	cvarManager->registerCvar("cool_y_location", "0", "set y location of the overlay");
}

void CoolPlugin::onUnload() {
	cvarManager->log("I was too cool for this world B'(");
}

void CoolPlugin::ballOnTop() {
	if (!gameWrapper->IsInFreeplay()) { return; }
	ServerWrapper server = gameWrapper->GetCurrentGameState();
	if (!server) { return; }

	if (!coolEnabled) { return; }

	CVarWrapper distanceCVar = cvarManager->getCvar("cool_distance");
	if (!distanceCVar) { return; }
	float distance = distanceCVar.getFloatValue();
		 
	BallWrapper ball = server.GetBall();
	if (!ball) { return; }
	CarWrapper car = gameWrapper->GetLocalCar();
	if (!car) { return; }

	Vector carVelocity = car.GetVelocity();
	ball.SetVelocity(carVelocity);

	Vector carLocation = car.GetLocation();
	float ballRadius = ball.GetRadius();
	ball.SetLocation(carLocation + Vector{ 0, 0, distance });
}

// in a .cpp file 
void CoolPlugin::Render(CanvasWrapper canvas) {
	CVarWrapper textColorVar = cvarManager->getCvar("cool_color");
	if (!textColorVar) {
		return;
	}
	LinearColor textColor = textColorVar.getColorValue();
	canvas.SetColor(textColor);

	CVarWrapper xLocCvar = cvarManager->getCvar("cool_x_location");
	if (!xLocCvar) { return; }
	float xLoc = xLocCvar.getFloatValue();

	CVarWrapper yLocCvar = cvarManager->getCvar("cool_y_location");
	if (!yLocCvar) { return; }
	float yLoc = yLocCvar.getFloatValue();

	canvas.SetPosition(Vector2F{ xLoc, yLoc });

	// says hi
	// draws from the last set position
	// the two floats are text x and y scale
	// the false turns off the drop shadow
	canvas.DrawString("Hi Cool Dude", 2.0, 2.0, false);
}
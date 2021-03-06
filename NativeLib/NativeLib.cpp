#include "CommonLib.h"
#include "Oblast.h"
#include "GameManager.h"
#include "CameraController.h"
#include "ResetCameraButton.h"
#include "Piece.h"
#include "SmartLabel.h"
#include "Player.h"
#include "DataLoader.h"
#include "MainCurrency.h"
#include "Bot.h"
#include "FlyingMoney.h"
#include "UpgradeButton.h"
#include "ProfileButton.h"
#include "LevelPurchase.h"
#include "TutorialWindow.h"
#include "ResetButtons.h"
#include "Volume.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);

	register_class<Oblast>();
	register_class<GameManager>();
	register_class<CameraController>();
	register_class<ResetCameraButton>();
	register_class<Piece>();
	register_class<SmartLabel>();
	register_class<Player>();
	register_class<DataLoader>();
	register_class<MainCurrency>();
	register_class<Bot>();
	register_class<FlyingMoney>();
	register_class<UpgradeButton>();
	register_class<ProfileButton>();
	register_class <LevelPurchase>();
	register_class<TutorialWindow>();
	register_class <ResetButtons>();
	register_class <Volume>();
}
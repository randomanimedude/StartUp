#pragma once

#include <Area2D.hpp>
#include <InputEventMouseButton.hpp>
#include <GlobalConstants.hpp>
#include <Sprite.hpp>
#include <MeshInstance2D.hpp>
#include <Texture.hpp>
#include <CollisionPolygon2D.hpp>
#include <SceneTree.hpp>
#include <vector>
#include <ResourceLoader.hpp>
#include <PackedScene.hpp>
#include <AnimationPlayer.hpp>

#include "ResetCameraButton.h"
#include "CommonLib.h"
#include "GameManager.h"
#include "Piece.h"
#include "DataLoader.h"
#include "MainCurrency.h"
#include "LevelPurchase.h"

class GameManager;
class Piece;

class Oblast :
    public Area2D
{
	GODOT_CLASS(Oblast, Area2D);

public:
	static void _register_methods();
	void _init();

	static Oblast* GetSingleton();

	void _ready();
	void _physics_process();
	void _input_event(Node* viewport, InputEventMouseButton* event, int shape_idx);
	void ChangeColorTo(Color color, float force);
	Vector2 GetSize();
	void Hide();
	void Show();
	void ShowPieces();
	void HidePieces();
	void RegisterPiece(Piece* piece);
	void UpdateSituation();
	void SelectPiece(Piece* piece);
	void UnselectPiece();
	bool IsCompleted();
	void Open();
	vector<Piece*> GetPieces() { return pieces; }
	Piece* GetSelectedPiece();

private:
	MeshInstance2D* mainSprite;
	//Sprite* border;
	CollisionPolygon2D* collisionShape;
	GameManager* gameManager;
	Node2D* piecesCombined = nullptr;
	Piece* selectedPiece = nullptr;
	ResourceLoader* resourceLoader = ResourceLoader::get_singleton();

	float colorChangeForce = 0;

	Color def = Color(255, 255, 255, 255)/255.0;
	Color blue = Color(97, 168, 239, 255)/255.0;
	Color borderColor = Color(47, 220, 188, 255) / 255.0;
	Color currentColor = def;
	Color storedColor = def;

	State state = Visible;

	vector<Piece*> pieces;

	int MainCurrency;
	AnimationPlayer* LockAnimation;
	Sprite* LockSprite;
	static inline Oblast* instance;
public:
	bool IsOpen;
	int LevelNumber;
	int LevelPrice;
};


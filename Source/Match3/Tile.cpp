// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

#include "Grid.h"
#include "PaperSpriteComponent.h"

void ATile::Initialize(AGrid* grid, FVector boardPosition, int tileType)
{
	_grid = grid;
	_boardPosition = boardPosition;
	_type = tileType;

	SetTileSprite(tileType);
}

void ATile::SetTileSprite(int tileType)
{
	switch (tileType)
	{
	case 0:
		GetRenderComponent()->SetSprite(CheeseSprite);
		break;
	case 1:
		GetRenderComponent()->SetSprite(DoughSprite);
		break;
	case 2:
		GetRenderComponent()->SetSprite(HamSprite);
		break;
	case 3:
		GetRenderComponent()->SetSprite(MushroomSprite);
		break;
	case 4:
		GetRenderComponent()->SetSprite(TomatoSprite);
		break;
	}
}

void ATile::OnTileClicked()
{
	_grid->OnTileClicked(this);
}

void ATile::MoveTile(FVector newLocation)
{
	SetActorLocation(newLocation);
}

void ATile::Select()
{
	GetRenderComponent()->SetSpriteColor(FLinearColor::Gray);
}

void ATile::Deselect()
{
	GetRenderComponent()->SetSpriteColor(FLinearColor::White);
}

int ATile::GetType()
{
	return _type;
}

void ATile::SetNewBoardPosition(FVector newBoardPosition)
{
	_boardPosition = newBoardPosition;
}

FVector ATile::GetBoardPosition()
{
	return _boardPosition;
}

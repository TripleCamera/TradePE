#include "mcpe.h"

void Player::openTradeScreen(Villager*) {}

void LocalPlayer::openTradeScreen(Villager *v)
{ getMinecraft() -> getScreenChooser() -> pushTradeScreen(this, v); }

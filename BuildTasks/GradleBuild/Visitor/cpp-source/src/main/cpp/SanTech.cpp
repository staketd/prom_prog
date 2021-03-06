//
// Created by Pavel Akhtyamov on 2019-04-24.
//

#include "SanTech.h"
#include "Kitchen.h"
#include "LivingRoom.h"
#include "BathRoom.h"
#include "Home.h"

void SanTech::visit(Kitchen *kitchen) {
  kitchen->wall.material = "sink";
}

void SanTech::visit(LivingRoom *living_room) {

}

void SanTech::visit(BathRoom *bath_room) {
  bath_room->wall.material = "bath";
}
void SanTech::visit(Home *home) {
  home->bath_room_.Accept(this);
  home->kitchen_.Accept(this);
}

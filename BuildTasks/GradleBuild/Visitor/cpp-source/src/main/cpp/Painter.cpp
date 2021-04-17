//
// Created by Pavel Akhtyamov on 2019-04-23.
//

#include "Painter.h"
#include "Kitchen.h"
#include "LivingRoom.h"
#include "BathRoom.h"
#include "Home.h"

void Painter::visit(Kitchen *kitchen) {
  Paint(&(kitchen->ceiling), "white");
}

void Painter::visit(LivingRoom *living_room) {
  Paint(&(living_room->ceiling), "brown");
  Paint(&(living_room->floor), "red");
  Paint(&(living_room->wall), "orange");
}

void Painter::visit(BathRoom *bath_room) {
  Paint(&(bath_room->ceiling), "blue");
}

void Painter::Paint(Surface *surface, std::string color) {
  surface->material = "paint";
  surface->color = color;
}

void Painter::visit(Home *home) {
  home->kitchen_.Accept(this);
  home->living_room_.Accept(this);
  home->bath_room_.Accept(this);
}

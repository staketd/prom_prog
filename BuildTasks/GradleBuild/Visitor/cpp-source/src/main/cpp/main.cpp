//
// Created by Pavel Akhtyamov on 2019-04-23.
//

#include "BathRoom.h"
#include "Kitchen.h"
#include "LivingRoom.h"
#include "Tiler.h"
#include "Painter.h"
#include "Windower.h"
#include "SanTech.h"

#include "Home.h"

int main() {
  Home home;

  SanTech sanTech;
  Tiler tiler;

  home.Accept(&sanTech);
  home.Accept(&tiler);
}
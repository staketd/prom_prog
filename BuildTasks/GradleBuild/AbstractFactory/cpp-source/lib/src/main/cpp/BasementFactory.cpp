//
// Created by Pavel Akhtyamov on 2019-02-25.
//

#include <BasementFactory.h>
#include <BasementHardRoom.h>
#include <BasementNormalRoom.h>


std::shared_ptr<NormalRoom> BasementFactory::CreateNormalRoom() {
  return std::make_shared<BasementNormalRoom>();
}

std::shared_ptr<HardRoom> BasementFactory::CreateHardRoom() {
  return std::make_shared<BasementHardRoom>();
}

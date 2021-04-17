project(Command)

set(SOURCES main.cpp commands/Command.cpp src/main/headers/Command.h commands/CreateSoupCommand.cpp src/main/headers/CreateSoupCommand.h Waiter.cpp src/main/headers/Waiter.h cookery/Cook.cpp src/main/headers/Cook.h cookery/CookPool.cpp src/main/headers/CookPool.h src/main/headers/Dish.h cookery/Barman.cpp src/main/headers/Barman.h commands/CreateCocktailCommand.cpp src/main/headers/CreateCocktailCommand.h)
add_executable(Command main.cpp ${SOURCES})

target_link_libraries(Command Threads::Threads)
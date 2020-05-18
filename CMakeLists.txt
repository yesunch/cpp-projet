cmake_minimum_required(VERSION 3.10)
project(bestioles)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(bestioles src/main.cpp src/Aquarium.cpp include/Aquarium.h src/Milieu.cpp include/Milieu.h src/Bestiole.cpp include/Bestiole.h src/Espece.cpp include/Espece.h src/GenerateurAleatoire.cpp include/GenerateurAleatoire.h src/ObservationBestiole.cpp include/ObservationBestiole.h src/Collision.cpp include/Collision.h src/factory/PopulationFactory.cpp include/factory/PopulationFactory.h src/factory/PopParComportementFactory.cpp include/factory/PopParComportementFactory.h src/comportement/Comportement.cpp include/comportement/Comportement.h src/comportement/ComportementGregaire.cpp include/comportement/ComportementGregaire.h src/Util.cpp include/Util.h src/Locomotion.cpp include/Locomotion.h src/Protection.cpp include/Protection.h src/Dissimulation.cpp include/Dissimulation.h src/accessoire/Nageoires.cpp include/accessoire/Nageoires.h src/accessoire/Carapace.cpp include/accessoire/Carapace.h src/accessoire/Camouflage.cpp include/accessoire/Camouflage.h src/capteur/Capteur.cpp include/capteur/Capteur.h src/capteur/Yeux.cpp include/capteur/Yeux.h src/capteur/Oreilles.cpp include/capteur/Oreilles.h src/capteur/OreillesEtYeux.cpp include/capteur/OreillesEtYeux.h src/comportement/ComportementPeureux.cpp include/comportement/ComportementPeureux.h src/comportement/ComportementKamikaze.cpp include/comportement/ComportementKamikaze.h src/comportement/ComportementPrevoyant.cpp include/comportement/ComportementPrevoyant.h src/comportement/ComportementPersonnaliteMultiples.cpp include/comportement/ComportementPersonnaliteMultiples.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(bestioles ${SFML_LIBRARIES})
endif ()

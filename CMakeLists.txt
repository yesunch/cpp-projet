cmake_minimum_required(VERSION 3.10)
project(bestioles)

set(CMAKE_CXX_STANDARD 14)

add_executable(bestioles main.cpp Aquarium.cpp Aquarium.h Milieu.cpp Milieu.h Bestiole.cpp Bestiole.h Espece.cpp Espece.h GenerateurAleatoire.cpp GenerateurAleatoire.h ObservationBestiole.cpp ObservationBestiole.h Collision.cpp Collision.h PopulationFactory.cpp PopulationFactory.h PopParComportementFactory.cpp PopParComportementFactory.h Comportement.cpp Comportement.h ComportementGregaire.cpp ComportementGregaire.h Util.cpp Util.h Locomotion.cpp Locomotion.h Protection.cpp Protection.h Dissimulation.cpp Dissimulation.h Nageoires.cpp Nageoires.h Carapace.cpp Carapace.h Camouflage.cpp Camouflage.h Capteur.cpp Capteur.h Yeux.cpp Yeux.h Oreilles.cpp Oreilles.h OreillesEtYeux.cpp OreillesEtYeux.h ComportementPeureux.cpp ComportementPeureux.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(bestioles ${SFML_LIBRARIES})
endif ()

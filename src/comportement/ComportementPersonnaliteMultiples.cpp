
#include <cassert>

#include "../../include/comportement/ComportementPersonnaliteMultiples.h"
#include "../../include/GenerateurAleatoire.h"

ComportementPersonnaliteMultiples::ComportementPersonnaliteMultiples(
    std::vector<Comportement::Ptr> comportements)
  : comportements{ std::move(comportements) }
  , currentComportement{ this->comportements.front().get() } // get first comportement in comportement container
  , timeOut{ sf::seconds(DUREE_COMPORTEMENT) }
{
    assert(!this->comportements.empty());
}

Comportement::Ptr
ComportementPersonnaliteMultiples::cloner()
{
    std::vector<Comportement::Ptr> clonesComportements;
    std::transform(comportements.cbegin(),
                   comportements.cend(),
                   std::back_inserter(clonesComportements),
                   [](Comportement::Ptr const& compPtr) { return compPtr->cloner(); });

    return std::make_unique<ComportementPersonnaliteMultiples>(std::move(clonesComportements));
}

sf::Color
ComportementPersonnaliteMultiples::getColor() const
{
    return currentComportement->getColor();
}

const char*
ComportementPersonnaliteMultiples::getName() const
{
    return "personnalités multiples";
}

void
ComportementPersonnaliteMultiples::update(const std::vector<ObservationBestiole>& obsBestioles,
                                          Bestiole& moiMeme,
                                          sf::Time timeStep)
{
    if (timeOut > sf::Time::Zero)
    {
        timeOut -= timeStep;
        currentComportement->update(obsBestioles, moiMeme, timeStep);
        return;
    }

    auto& genAlea = GenerateurAleatoire::getSingleton();
    auto nextComportementIndex = genAlea.uniformInt<size_t>(0, comportements.size() - 1);

    currentComportement = comportements[nextComportementIndex].get(); // get a random comportement
    timeOut = sf::seconds(DUREE_COMPORTEMENT); // change its comportement each 5.0f
}
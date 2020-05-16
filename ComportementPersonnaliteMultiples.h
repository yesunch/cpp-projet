//
// Created by quentin on 15/05/2020.
//

#ifndef BESTIOLES_COMPORTEMENTPERSONNALITEMULTIPLES_H
#define BESTIOLES_COMPORTEMENTPERSONNALITEMULTIPLES_H

#include "Comportement.h"

class ComportementPersonnaliteMultiples : public Comportement
{
  public:
    static constexpr auto DUREE_COMPORTEMENT = 5.0f;

    explicit ComportementPersonnaliteMultiples(std::vector<Comportement::Ptr> comportements);
    Ptr cloner() override;

    sf::Color getColor() const override;
    const char* getName() const override;

    void update(std::vector<ObservationBestiole> const& obsBestioles,
                Bestiole& moiMeme,
                sf::Time timeStep) override;

  private:
    std::vector<Comportement::Ptr> comportements;
    Comportement* currentComportement;

    sf::Time timeOut;
};

#endif // BESTIOLES_COMPORTEMENTPERSONNALITEMULTIPLES_H

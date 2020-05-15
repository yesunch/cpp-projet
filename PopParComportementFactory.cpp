//
// Created by quentin on 14/05/2020.
//

#include "PopParComportementFactory.h"
#include "Camouflage.h"
#include "Carapace.h"
#include "GenerateurAleatoire.h"
#include "Nageoires.h"
#include "Oreilles.h"
#include "OreillesEtYeux.h"
#include "Util.h"

PopParComportementFactory::PopParComportementFactory(float alphaMin,
                                                     float alphaMax,

                                                     float deltaOmin,
                                                     float deltaOmax,
                                                     float deltaYmin,
                                                     float deltaYmax,

                                                     float gammaOmin,
                                                     float gammaOmax,
                                                     float gammaYmin,
                                                     float gammaYmax,

                                                     float nuMax,
                                                     float omegaMax,
                                                     float etaMax,

                                                     float phiMin,
                                                     float phiMax)
  : alphaMin{ alphaMin }
  , alphaMax{ alphaMax }
  , deltaOmin{ deltaOmin }
  , deltaOmax{ deltaOmax }
  , deltaYmin{ deltaYmin }
  , deltaYmax{ deltaYmax }
  , gammaOmin{ gammaOmin }
  , gammaOmax{ gammaOmax }
  , gammaYmin{ gammaYmin }
  , gammaYmax{ gammaYmax }
  , nuMax{ nuMax }
  , omegaMax{ omegaMax }
  , etaMax{ etaMax }
  , phiMin{ phiMin }
  , phiMax{ phiMax }
{
}

void
PopParComportementFactory::addComportement(Comportement::Ptr comp, unsigned int effectif)
{
    effectifParComp.emplace_back(comp->cloner(), effectif);
}

std::vector<Bestiole>
PopParComportementFactory::creerPopulation(sf::FloatRect bords)
{
    auto& genAlea = GenerateurAleatoire::getSingleton();

    std::vector<Bestiole> population;
    for (auto const& effectifPourComp : effectifParComp)
    {
        std::generate_n(std::back_inserter(population), effectifPourComp.second, [&]() {
            Bestiole nouvelleBestiole{ nextBestioleId++,
                                       especeAleatoire(),
                                       effectifPourComp.first->cloner() };
            nouvelleBestiole.setPosition(genAlea.uniformPoint(bords));
            nouvelleBestiole.setRotation(genAlea.uniformRotation());
            return std::move(nouvelleBestiole);
        });
    }

    return std::move(population);
}

Bestiole
PopParComportementFactory::creerBestiole(sf::FloatRect bords)
{
    std::vector<unsigned int> effectifs;
    std::transform(effectifParComp.cbegin(),
                   effectifParComp.cend(),
                   std::back_inserter(effectifs),
                   [](auto const& effPourComp) { return effPourComp.second; });

    auto& genAlea = GenerateurAleatoire::getSingleton();
    auto randomCompIndex = genAlea.discrete(effectifs.cbegin(), effectifs.cend());

    auto comportement = effectifParComp[randomCompIndex].first->cloner();

    Bestiole nouvelleBestiole{ nextBestioleId++, especeAleatoire(), std::move(comportement) };
    nouvelleBestiole.setPosition(genAlea.uniformPoint(bords));
    nouvelleBestiole.setRotation(genAlea.uniformRotation());
    return std::move(nouvelleBestiole);
}

Bestiole
PopParComportementFactory::clonerBestiole(const Bestiole& bestiole)
{
    Bestiole clone{ nextBestioleId++, bestiole.clonerEspece(), bestiole.clonerComportement() };
    clone.setPosition(bestiole.getPosition());
    return std::move(clone);
}

Espece
PopParComportementFactory::especeAleatoire() const
{
    Espece espece;

    auto& genAlea = GenerateurAleatoire::getSingleton();

    bool ajouterOreilles = genAlea.uniformBernoulli();
    bool ajouterYeux = genAlea.uniformBernoulli();
    bool ajouterNageoires = genAlea.uniformBernoulli();
    bool ajouterCarapace = genAlea.uniformBernoulli();
    bool ajouterCamouflage = genAlea.uniformBernoulli();

    auto deltaO = genAlea.uniformReal(deltaOmin, deltaOmax);
    auto gammaO = genAlea.uniformReal(gammaOmin, gammaOmax);
    auto alpha = genAlea.uniformReal(alphaMin, alphaMax);
    auto deltaY = genAlea.uniformReal(deltaYmin, deltaYmax);
    auto gammaY = genAlea.uniformReal(gammaYmin, gammaYmax);

    auto nu = genAlea.uniformReal(1.0f, nuMax);
    auto omega = genAlea.uniformReal(1.0f, omegaMax);
    auto eta = 1.0f + (omega - 1.0f) / (omegaMax - 1.0f) * (etaMax - 1.0f);

    auto phi = genAlea.uniformReal(phiMin, phiMax);

    Oreilles oreilles{ deltaO, gammaO };
    Yeux yeux{ alpha, deltaY, gammaY };
    if (ajouterOreilles && ajouterYeux)
    {
        espece.capteur = std::make_unique<OreillesEtYeux>(std::move(oreilles), std::move(yeux));
    }
    else if (ajouterOreilles)
    {
        espece.capteur = std::make_unique<Oreilles>(std::move(oreilles));
    }
    else if (ajouterYeux)
    {
        espece.capteur = std::make_unique<Yeux>(std::move(yeux));
    }

    if (ajouterNageoires)
    {
        espece.locomotion = std::make_unique<Nageoires>(nu);
    }
    if (ajouterCarapace)
    {
        espece.protection = std::make_unique<Carapace>(omega, eta);
    }
    if (ajouterCamouflage)
    {
        espece.dissimulation = std::make_unique<Camouflage>(phi);
    }

    return std::move(espece);
}
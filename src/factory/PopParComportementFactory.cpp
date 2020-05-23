
#include "../../include/factory/PopParComportementFactory.h"
#include "../../include/accessoire/Camouflage.h"
#include "../../include/accessoire/Carapace.h"
#include "../../include/GenerateurAleatoire.h"
#include "../../include/accessoire/Nageoires.h"
#include "../../include/capteur/Oreilles.h"
#include "../../include/capteur/OreillesEtYeux.h"
#include "../../include/Util.h"

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
    // effectifs contains five 1
    auto& genAlea = GenerateurAleatoire::getSingleton();
    // generate an random integer during the range [0,5[
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
    auto& genAlea = GenerateurAleatoire::getSingleton();

    Bestiole clone{ nextBestioleId++, bestiole.clonerEspece(), bestiole.clonerComportement() };

    auto const orientationBestiole = bestiole.getOrientation();
    auto const orientationClone =
        Util::rotate(orientationBestiole, 0.1f * genAlea.uniformReal(-M_PI, M_PI));
    clone.setPosition(bestiole.getPosition() -
                      1.25f * orientationClone * bestiole.getShape().getLocalBounds().width);
    clone.setOrientation(orientationClone);
    return std::move(clone);
}

Espece
PopParComportementFactory::especeAleatoire() const
{
    Espece espece;

    auto& genAlea = GenerateurAleatoire::getSingleton();

    espece.longueur = genAlea.uniformReal(15.0f, 25.0f);
    espece.epaisseur = espece.longueur * genAlea.uniformReal(0.5f, 0.75f);
    espece.dureeDeVie = sf::seconds(genAlea.uniformReal(15.0f, 45.0f));

    enum TypeCapteur
    {
        OREILLES,
        YEUX,
        OREILLES_ET_YEUX
    };

    int typeCapteur = genAlea.uniformInt(0, 2);

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
    switch (typeCapteur)
    {
        case OREILLES:
            espece.capteur = std::make_unique<Oreilles>(std::move(oreilles));
            break;

        case YEUX:
            espece.capteur = std::make_unique<Oreilles>(std::move(oreilles));
            break;

        case OREILLES_ET_YEUX:
            espece.capteur = std::make_unique<OreillesEtYeux>(std::move(oreilles), std::move(yeux));
            break;

        default:
            throw std::runtime_error{ "Unhandled case" };
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
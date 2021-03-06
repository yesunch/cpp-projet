
#include "../../include/comportement/ComportementPrevoyant.h"
#include "../../include/Bestiole.h"
#include "../../include/Util.h"

Comportement::Ptr
ComportementPrevoyant::cloner()
{
    return std::make_unique<ComportementPrevoyant>(*this);
}

sf::Color
ComportementPrevoyant::getColor() const
{
    return sf::Color::Cyan;
}

const char*
ComportementPrevoyant::getName() const
{
    return "prévoyant";
}

void
ComportementPrevoyant::update(const std::vector<ObservationBestiole>& obsBestioles,
                              Bestiole& moiMeme,
                              sf::Time timeStep)
{
    auto bestioleIt = obsBestioles.cbegin();
    // if there is no obsBestioles
    if (bestioleIt == obsBestioles.cend())
    {
        return;
    }

    auto const currentPos = moiMeme.getPosition();
    auto const currentOrientation = moiMeme.getOrientation();
    auto const futurePos = currentPos + moiMeme.getVelocity();

    sf::Vector2f futureClosestBestiolePos;
    auto futureClosestBestioleDist = std::numeric_limits<float>::max();
    auto futureClosestBestiole = bestioleIt;
    // find nearest bestiole
    for (; bestioleIt != obsBestioles.cend(); ++bestioleIt)
    {
        auto const bestioleFuturePos = bestioleIt->ellipse.getPosition() + bestioleIt->velocity;
        auto const bestioleFutureDist = Util::distance(futurePos, bestioleFuturePos);

        if (bestioleFutureDist < futureClosestBestioleDist)
        {
            futureClosestBestiolePos = bestioleFuturePos;
            futureClosestBestioleDist = bestioleFutureDist;
            futureClosestBestiole = bestioleIt;
        }
    }
    // turn current bestiole's back towards the predicted position of the predicted nearest bestiole
    auto const angleAwayFutureClosestBestiole =
        Util::angle(currentOrientation, currentPos - futureClosestBestiolePos);
    moiMeme.rotate(angleAwayFutureClosestBestiole * timeStep.asSeconds());
}
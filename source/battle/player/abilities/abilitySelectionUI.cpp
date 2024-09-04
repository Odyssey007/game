#include "../header/battle/player/abilities/abilitySelectionUI.h"

AbilitySelectionUI::AbilitySelectionUI() {
    sf::Vector2f size(300.0f, 420.0f);
    for (size_t i = 0; i < 3; i++) {
        sf::RectangleShape card;
        card.setSize(size);
        // card.setOrigin(sf::Vector2f(size.x/2.0f, size.y/2.0f));
        //
        card.setFillColor(sf::Color::Blue);

        abilityCards.push_back(card);
    }

    sf::Vector2f btnSize(175.0f, 35.0f);
    confirmBtn.setSize(btnSize);
    confirmBtn.setOrigin(sf::Vector2f(btnSize.x/2.0f, btnSize.y/2.0f));
}

void AbilitySelectionUI::update(uint8_t curLvl, uint8_t& lastLvl, GameState& state) {
    if (lastLvl < curLvl) {
        lastLvl = curLvl;
        state = LEVEL_UP_MENU;
    }
}

void AbilitySelectionUI::confirmAbility() {
    
}

void AbilitySelectionUI::spawnCards(const sf::FloatRect& screenBounds) {
    float totalWidth = 0.0f;
    float spacing = 50.0f;

    for (const auto& card : abilityCards) {
        totalWidth += card.getSize().x + spacing;
    }
    totalWidth -= spacing;

    float startX = screenBounds.left + (screenBounds.width - totalWidth)/2.0f;
    float currentY = screenBounds.top + screenBounds.height/2.0f;

    float currentX = startX;
    for (auto& card : abilityCards) {
        card.setPosition(currentX, currentY - card.getSize().y/2.0f - 50.0f);
        currentX += card.getSize().x + spacing;
    }

    confirmBtn.setPosition(
        screenBounds.left + screenBounds.width/2.0f,
        currentY + abilityCards[0].getSize().y/2.0f + 50.0f
    );
}

void AbilitySelectionUI::render(sf::RenderWindow& window) const {
    for (const auto& card : abilityCards) {
        window.draw(card);
    }

    window.draw(confirmBtn);
}
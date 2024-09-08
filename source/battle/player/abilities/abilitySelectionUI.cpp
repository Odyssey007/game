#include "../header/battle/player/abilities/abilitySelectionUI.h"

AbilitySelectionUI::AbilitySelectionUI() {
    picked = false;
    //
    sf::Vector2f size(300.0f, 420.0f);
    for (size_t i = 0; i < 3; i++) {
        sf::RectangleShape card;
        card.setSize(size);
        // card.setOrigin(sf::Vector2f(size.x/2.0f, size.y/2.0f));
        //
        card.setFillColor(sf::Color::Blue);
        card.setOutlineColor(sf::Color::Red);
        card.setOutlineThickness(0.0f);
        abilityCards.push_back(card);
    }
    //
    sf::Vector2f btnSize(175.0f, 35.0f);
    confirmBtn.setSize(btnSize);
    confirmBtn.setFillColor(sf::Color::Magenta);
    confirmBtn.setOrigin(sf::Vector2f(btnSize.x/2.0f, btnSize.y/2.0f));
    //
    font.loadFromFile("assets/fonts/munro.ttf");
    confirmText.setString("Confirm");
    confirmText.setFont(font);
    confirmText.setCharacterSize(20);
    confirmText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = confirmText.getLocalBounds();
    confirmText.setOrigin(textBounds.width/2.0f, textBounds.height/2.0f);
}

void AbilitySelectionUI::update(uint8_t curLvl, uint8_t& lastLvl, GameState& state) {
    if (lastLvl < curLvl) {
        lastLvl = curLvl;
        state = LEVEL_UP_MENU;
    }
}

//?not clearing when writing on top
void AbilitySelectionUI::confirmAbility(sf::Mouse::Button button, const sf::Vector2f& mousePos, GameState& state) {
    if (button == sf::Mouse::Left) {
        for (auto& card : abilityCards) {
            if (card.getGlobalBounds().contains(mousePos)) {
                if (selectedAbility != &card) { //only go if new card
                    //reset old
                    if (selectedAbility) {
                        selectedAbility->setFillColor(sf::Color::Blue);
                    }
                    //new card
                    selectedAbility = &card;
                    selectedAbility->setFillColor(sf::Color::Red);
                    picked = true;
                }
                break;
            }
        }
        if (picked && confirmBtn.getGlobalBounds().contains(mousePos)) {
            state = PLAYING;
            //TODO SAVE WHICH ONE PICKED
            //reset what is selected
            selectedAbility->setFillColor(sf::Color::Blue);
            selectedAbility = nullptr;
        } 
    }
}

void AbilitySelectionUI::spawnCards(const sf::FloatRect& screenBounds) {
    picked = false;
    //ability cards----
    float totalWidth = 0.0f;
    float spacing = 50.0f;
    for (const auto& card : abilityCards) {
        totalWidth += card.getSize().x + spacing;
    }
    totalWidth -= spacing; //calc combined size
    //positions
    float startX = screenBounds.left + (screenBounds.width - totalWidth)/2.0f;
    float currentY = screenBounds.top + screenBounds.height/2.0f;
    float currentX = startX;
    for (auto& card : abilityCards) {
        card.setPosition(currentX, currentY - card.getSize().y/2.0f - 50.0f);
        currentX += card.getSize().x + spacing;
    }
    //confirmBtn----
    confirmBtn.setPosition(
        screenBounds.left + screenBounds.width/2.0f,
        currentY + abilityCards[0].getSize().y/2.0f + 50.0f
    );
    sf::Vector2f btnPos = confirmBtn.getPosition(); btnPos.y = btnPos.y - 5.0f;
    confirmText.setPosition(btnPos);
}

void AbilitySelectionUI::render(sf::RenderWindow& window) const {
    for (const auto& card : abilityCards) {
        window.draw(card);
    }
    window.draw(confirmBtn);
    window.draw(confirmText);
}
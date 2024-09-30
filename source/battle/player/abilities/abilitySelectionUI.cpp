#include "../header/battle/player/abilities/abilitySelectionUI.h"

const uint8_t NUM_ABILITIES = 9;
const uint8_t NUM_CARDS = 2;

AbilitySelectionUI::AbilitySelectionUI() {
    picked = false;
    //
    sf::Vector2f size(300.0f, 420.0f);
    for (size_t i = 0; i < NUM_CARDS; i++) {
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
    //
    for (uint8_t i = 0; i < NUM_ABILITIES; ++i) {
        availableAbilities.push_back(i);
        writeDescription(i);
    }
}

void AbilitySelectionUI::writeDescription(uint8_t ability) {
    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = title.getLocalBounds();
    title.setOrigin(textBounds.width/2.0f, textBounds.height/2.0f);
    //
    sf::Text description;
    description.setFont(font);
    description.setCharacterSize(15);
    description.setFillColor(sf::Color::White);
    textBounds = description.getLocalBounds();
    description.setOrigin(textBounds.width/2.0f, textBounds.height/2.0f);
    switch (ability) {
        case 0:
            title.setString("Atomic Bullet");
            description.setString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB");
            break;
        case 1:
            title.setString("Energy Barrier");
            description.setString("EB");
            break;
        case 2:
            title.setString("Piercing Shots");
            description.setString("PS");
            break;
        case 3:
            title.setString("Increase Max Health");
            description.setString("MH");
            break;
        case 4:
            title.setString("Increase Health Regeneration");
            description.setString("HR");
            break;
        case 5:
            title.setString("Increase Movement Speed");
            description.setString("MS");
            break;
        case 6:
            title.setString("Heal");
            description.setString("H");
            break;
        case 7:
            title.setString("Increase Damage");
            description.setString("D");
            break;
        case 8:
            title.setString("Reduce Ability Cooldown");
            description.setString("AC");
            break;
    }
    abilityDescription.push_back(std::make_pair(title, description));
}

int AbilitySelectionUI::generateAbility() {
    if (availableAbilities.empty()) return -1;
    //
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0 , availableAbilities.size() - 1);
    int randomIndex = dist(gen);
    //
    int ability = availableAbilities[randomIndex];
    if (randomIndex < 3) {
        availableAbilities.erase(availableAbilities.begin() + randomIndex);
    }
    //
    return ability;
}

void AbilitySelectionUI::update(uint8_t curLvl, uint8_t& lastLvl, GameState& state) {    
    if (lastLvl < curLvl) {
        lastLvl = curLvl;
        state = LEVEL_UP_MENU;
        //
        while (givenAbilities.size() < NUM_CARDS) {
            givenAbilities.push_back(generateAbility());
        }
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
            //
            givenAbilities.clear();
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
    for (size_t i = 0; i < NUM_CARDS; i++) {
        abilityCards[i].setPosition(currentX, currentY - abilityCards[i].getSize().y/2.0f - 50.0f);
        currentX += abilityCards[i].getSize().x + spacing;
        //
        abilityDescription[givenAbilities[i]].first.setPosition(abilityCards[i].getPosition());
        sf::Vector2f betterPos = abilityDescription[givenAbilities[i]].first.getPosition();
        betterPos.x = abilityCards[i].getPosition().x + 
                    (abilityCards[i].getGlobalBounds().width / 2.0f) - 
                    (abilityDescription[givenAbilities[i]].first.getGlobalBounds().width / 2.0f);
        abilityDescription[givenAbilities[i]].first.setPosition(betterPos);
        //--
        abilityDescription[givenAbilities[i]].second.setPosition(abilityCards[i].getPosition());
        sf::Vector2f cardCenter = abilityCards[i].getPosition();
        cardCenter.x += abilityCards[i].getGlobalBounds().width/2.0f;
        sf::FloatRect textBound = abilityDescription[givenAbilities[i]].second.getGlobalBounds();
        betterPos.x = cardCenter.x - (textBound.width/2.0f);
        betterPos.y = cardCenter.y + 75.0f;
        abilityDescription[givenAbilities[i]].second.setPosition(betterPos);
        wrapText(abilityDescription[givenAbilities[i]].second, abilityCards[i].getGlobalBounds().width-10.0f);
    }
    //confirmBtn----
    confirmBtn.setPosition(
        screenBounds.left + screenBounds.width/2.0f,
        currentY + abilityCards[0].getSize().y/2.0f + 50.0f
    );
    sf::Vector2f btnPos = confirmBtn.getPosition(); btnPos.y = btnPos.y - 5.0f;
    confirmText.setPosition(btnPos);
}

//!don't work
void AbilitySelectionUI::wrapText(sf::Text& text, float maxWidth) {
    std::string writing = text.getString().toAnsiString();
    std::istringstream iss(writing);
    std::string word;
    std::string wrappedText;
    float spaceWidth = text.getFont()->getGlyph(' ', text.getCharacterSize(), false).advance;
    float currentLineWidth = 0;

    while (iss >> word) {
        text.setString(word);
        float wordWidth = text.getGlobalBounds().width + spaceWidth;  // include space in width

        // Check if adding this word exceeds the max width
        if (currentLineWidth + wordWidth > maxWidth) {
            // Start a new line unless it's the very first word
            if (!wrappedText.empty()) {
                wrappedText += "\n";
                currentLineWidth = 0;  // Reset current line width
            }
        }

        // Append the word to the result
        wrappedText += word + " ";
        currentLineWidth += wordWidth; // Update current line width
    }

    text.setString(wrappedText);  // Set the final string with wrapped text
}

 
void AbilitySelectionUI::render(sf::RenderWindow& window) const {
    for (size_t i = 0; i < NUM_CARDS; i++) {
        window.draw(abilityCards[i]);
        window.draw(abilityDescription[givenAbilities[i]].first);
        window.draw(abilityDescription[givenAbilities[i]].second);
    }
    window.draw(confirmBtn);
    window.draw(confirmText);
}
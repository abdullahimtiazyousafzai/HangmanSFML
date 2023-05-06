/*developed by M.Abdullah 2022323
 on April 6,2023
and M.Younas 2022456
copyright belongs to M.Abdullah
this project is for presentation only.
This project is not for sale or any other commercial use.
 */
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include <vector>

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(1080,820), "Hangman Game");

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(1080,820));
    background.setFillColor(sf::Color::White);

    sf::SoundBuffer winbuffer;
    if (!winbuffer.loadFromFile("F:/HangmanSFML/cheer.wav"))
        return -1;

    sf::SoundBuffer losebuffer;
    if (!losebuffer.loadFromFile("F:/HangmanSFML/death.wav"))
        return -1;

    sf::Sound winSound;
    winSound.setBuffer(winbuffer);

    sf::Sound loseSound;
    loseSound.setBuffer(losebuffer);
    // Set up the font
    sf::Font font;
    if (!font.loadFromFile("F:/CLionProjects/SnakeGameSFML/Lindelof-Font.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    // Set up the text for the word to guess
    sf::Text wordText("", font, 50);
    wordText.setPosition(100, 200);
    wordText.setFillColor(sf::Color::Black);

    // Set up the text for the letters guessed
    sf::Text guessedText("", font, 50);
    guessedText.setPosition(100, 400);
    guessedText.setFillColor(sf::Color::Black);

    sf::Text wintext;
    sf::Text losetext;
    sf::Text pressEsc;
    sf::Texture hangmanwin;
    if(!hangmanwin.loadFromFile("F:/HangmanSFML/hangmanpictures2/hangmanwin.png"))
    {
        std::cerr << "Failed to load hangmanwin.png" << std::endl;
        return 1;
    }
    sf::Sprite hangmanwinsprite;



    // Set up the hangman images
    std::vector<sf::Texture> hangmanImages(7);
    for (int i = 0; i < 7; ++i)
    {
        std::string filename = "F:/HangmanSFML/hangmanpictures2/hangman" + std::to_string(i) + ".png";
        if (!hangmanImages[i].loadFromFile(filename))
        {
            std::cerr << "Failed to load " << filename << std::endl;
            return 1;
        }
    }

    // Set up the sprite for the current hangman image
    sf::Sprite hangmanSprite(hangmanImages[0]);
    hangmanSprite.setPosition(500, 50);
    hangmanSprite.setScale(0.5, 0.5);

    // Set up the list of words to guess
    std::vector<std::string> words = {"hello", "world", "hangman", "computer", "science",
                                      "programming","language", "president", "america",
                                      "system", "telephone", "random", "congress",
                                      "burger", "water", "crystal", "keyboard",
                                      "laptop", "desktop", "mouse", "chair",
                                      "table", "window", "glass", "bottle",
                                      "cable", "charger", "charge"};

    // Choose a random word to guess
    std::srand(std::time(nullptr));
    if (words.empty()) {
        std::cerr << "No words in the list!" << std::endl;
        return 1;
    }
    std::string word = words[std::rand() % words.size()];

    // Set up the list of letters guessed
    std::vector<char> guessedLetters;

    // The number of incorrect guesses made so far
    int numIncorrectGuesses = 0;

    // The main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
            else if (event.type == sf::Event::TextEntered)
            {
                // Only process letters
                if ((event.text.unicode >= 'a') && (event.text.unicode <= 'z'))
                {
                    char letter = static_cast<char>(event.text.unicode);
                    // Check if the letter has already been guessed
                    auto it = std::find(guessedLetters.begin(), guessedLetters.end(), letter);
                    if (it == guessedLetters.end())
                    {
                        guessedLetters.push_back(letter);

                        // Check if the letter is in the word
                        bool foundLetter = false;
                        for (char c : word)
                        {
                            if (c == letter)
                            {
                                foundLetter = true;
                                break;
                            }
                        }

                        if (foundLetter)
                        {
                            // Update the word text
                            std::string displayedWord = "";
                            for (char c : word)
                            {
                                if (std::find(guessedLetters.begin(), guessedLetters.end(), c) != guessedLetters.end())
                                {
                                    displayedWord += c;
                                }
                                else
                                {
                                    displayedWord += "_";
                                }
                            }
                            wordText.setString(displayedWord);

                            // Check if the player has won
                            if (displayedWord.find("_") == std::string::npos)
                            {
                                winSound.play();
                                hangmanwinsprite.setTexture(hangmanwin);
                                hangmanwinsprite.setPosition(500, 50);
                                hangmanwinsprite.setScale(0.5, 0.5);
                                wintext.setString("You win!");
                                wintext.setFont(font);
                                wintext.setCharacterSize(100);
                                wintext.setFillColor(sf::Color::Black);
                                wintext.setPosition(100, 500);
                                pressEsc.setString("Press Esc to exit");
                                pressEsc.setFont(font);
                                pressEsc.setCharacterSize(50);
                                pressEsc.setFillColor(sf::Color::Black);
                                pressEsc.setPosition(100, 700);
                            }
                        }
                        else
                        {
                            // Update the number of incorrect guesses
                            numIncorrectGuesses++;
                            hangmanSprite.setTexture(hangmanImages[numIncorrectGuesses]);
                            if (numIncorrectGuesses == 6)
                            {
                                loseSound.play();
                                losetext.setString("You Lose! The word was\n " + word + ".");
                                losetext.setFont(font);
                                losetext.setCharacterSize(60);
                                losetext.setFillColor(sf::Color::Black);
                                losetext.setPosition(100, 500);
                                pressEsc.setString("Press Esc to exit");
                                pressEsc.setString("Press Esc to exit");
                                pressEsc.setFont(font);
                                pressEsc.setCharacterSize(50);
                                pressEsc.setFillColor(sf::Color::Black);
                                pressEsc.setPosition(100, 700);
                            }
                        }

                        // Update the guessed text
                        std::string guessedString = "Guessed: ";
                        for (char c : guessedLetters)
                        {
                            guessedString += c;
                            guessedString += " ";
                        }
                        guessedText.setString(guessedString);
                    }
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw the background
        window.draw(background);

        // Draw the word text and guessed text
        window.draw(wordText);
        window.draw(guessedText);

        // Draw the hangman image
        window.draw(hangmanSprite);
        window.draw(hangmanwinsprite);
        window.draw(wintext);
        window.draw(losetext);
        window.draw(pressEsc);

        // Display the window
        window.display();
    }

    return 0;
}

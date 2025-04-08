#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(sf::Vector2f size, sf::Vector2f position) : sf::RectangleShape(size) {
        setPosition(position);
    }

    // Set speed and rotation
    void setSpeed(float horizontalSpeed, float verticalSpeed, float rotation = 0.f) {
        verticalSpeed_ = verticalSpeed;
        horizontalSpeed_ = horizontalSpeed;
        rotation_ = rotation;
    }

    // Animate the rectangle (move and rotate)
    void animate(const sf::Time& elapsed) {
        move({ horizontalSpeed_ * elapsed.asSeconds(), verticalSpeed_ * elapsed.asSeconds() });
        rotate(rotation_ * elapsed.asSeconds());
        bounce();
    }

    // Set boundaries for the rectangle to stay within
    void setBounds(float topBound, float leftBound, float rightBound, float bottomBound) {
        topBound_ = topBound;
        bottomBound_ = bottomBound;
        leftBound_ = leftBound;
        rightBound_ = rightBound;
    }

    // Move the rectangle in a direction based on key press
    void moveInDirection(const sf::Time& elapsed, const sf::Keyboard::Key& key) {
        std::cout << "Key pressed: " << key << std::endl;

        if (key == sf::Keyboard::W && getPosition().y > topBound_) {
            move({ 0, -std::abs(verticalSpeed_ * elapsed.asSeconds()) });
        }
        else if (key == sf::Keyboard::S && getPosition().y + getSize().y < bottomBound_) {
            move({ 0, std::abs(verticalSpeed_ * elapsed.asSeconds()) });
        }
        if (key == sf::Keyboard::A && getPosition().x > leftBound_) {
            std::cout << "A pressed, moving left!" << std::endl;
            move({ -std::abs(horizontalSpeed_ * elapsed.asSeconds()), 0 });
        }
        if (key == sf::Keyboard::D && getPosition().x + getSize().x < rightBound_) {
            std::cout << "D pressed, moving right!" << std::endl;
            move({ horizontalSpeed_ * elapsed.asSeconds(), 0 });
        }
    }

    // Check if the rectangle is clicked
    bool isClicked(const sf::Vector2i& mouse_position) const {
        float rectX = getPosition().x;
        float rectY = getPosition().y;
        float rectWidth = getSize().x;
        float rectHeight = getSize().y;

        // Check if the mouse click is within the bounds of the rectangle
        return mouse_position.x >= rectX && mouse_position.x <= rectX + rectWidth &&
               mouse_position.y >= rectY && mouse_position.y <= rectY + rectHeight;
    }

    void setClicked(bool clicked) { clicked_ = clicked; }

private:
    float verticalSpeed_ = 0;
    float horizontalSpeed_ = 0;
    float topBound_ = 0;
    float bottomBound_ = 0;
    float leftBound_ = 0;
    float rightBound_ = 0;
    bool clicked_ = false;
    float rotation_ = 0.f;

    // Handle bouncing if the rectangle reaches the bounds
    void bounce() {
        if (getPosition().x < leftBound_) {
            horizontalSpeed_ = std::abs(horizontalSpeed_);
        }
        else if (getPosition().x + getSize().x > rightBound_) {
            horizontalSpeed_ = -std::abs(horizontalSpeed_);
        }
        if (getPosition().y < topBound_) {
            verticalSpeed_ = std::abs(verticalSpeed_);
        }
        else if (getPosition().y + getSize().y > bottomBound_) {
            verticalSpeed_ = -std::abs(verticalSpeed_);
        }
    }
};

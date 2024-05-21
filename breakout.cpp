#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

// Brick class
class Brick {
public:
    sf::RectangleShape shape;
    bool destroyed{false};

    Brick(float x, float y) {
        shape.setPosition(x, y);
        shape.setSize({70.f, 20.f});
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(35.f, 10.f);
    }
};

// Ball class
class Ball {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity{-5.f, -5.f};

    Ball(float x, float y) {
        shape.setPosition(x, y);
        shape.setRadius(15.f);
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(15.f, 15.f);
    }

    void update() {
        shape.move(velocity);

        if (left() < 0)
            velocity.x = 5.f;
        else if (right() > 800)
            velocity.x = -5.f;

        if (top() < 0)
            velocity.y = 5.f;
        else if (bottom() > 600)
            velocity.y = -5.f;
    }

    float x() const { return shape.getPosition().x; }
    float y() const { return shape.getPosition().y; }
    float left() const { return x() - shape.getRadius(); }
    float right() const { return x() + shape.getRadius(); }
    float top() const { return y() - shape.getRadius(); }
    float bottom() const { return y() + shape.getRadius(); }
};

// Paddle class
class Paddle {
public:
    sf::RectangleShape shape;

    Paddle(float x, float y) {
        shape.setPosition(x, y);
        shape.setSize({120.f, 20.f});
        shape.setFillColor(sf::Color::Cyan);
        shape.setOrigin(60.f, 10.f);
    }

    void update() {
        shape.move(velocity);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0)
            velocity.x = -8.f;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < 800)
            velocity.x = 8.f;
        else
            velocity.x = 0;
    }

    float x() const { return shape.getPosition().x; }
    float y() const { return shape.getPosition().y; }
    float left() const { return x() - shape.getSize().x / 2.f; }
    float right() const { return x() + shape.getSize().x / 2.f; }
    float top() const { return y() - shape.getSize().y / 2.f; }
    float bottom() const { return y() + shape.getSize().y / 2.f; }

private:
    sf::Vector2f velocity;
};

template <class T1, class T2>
bool isIntersecting(T1 &mA, T2 &mB) {
    return mA.right() >= mB.left() && mA.left() <= mB.right() && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle &mPaddle, Ball &mBall) {
    if (!isIntersecting(mPaddle, mBall)) return;

    mBall.velocity.y = -mBall.velocity.y;
    if (mBall.x() < mPaddle.x()) mBall.velocity.x = -5.f;
    else mBall.velocity.x = 5.f;
}

void testCollision(Brick &mBrick, Ball &mBall) {
    if (!isIntersecting(mBrick, mBall)) return;

    mBrick.destroyed = true;

    float overlapLeft{mBall.right() - mBrick.left()};
    float overlapRight{mBrick.right() - mBall.left()};
    float overlapTop{mBall.bottom() - mBrick.top()};
    float overlapBottom{mBrick.bottom() - mBall.top()};

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

    if (abs(minOverlapX) < abs(minOverlapY))
        mBall.velocity.x = ballFromLeft ? -5.f : 5.f;
    else
        mBall.velocity.y = ballFromTop ? -5.f : 5.f;
}

int main() {
    sf::RenderWindow window{{800, 600}, "Breakout"};
    window.setFramerateLimit(60);

    Ball ball{400, 300};
    Paddle paddle{400, 550};

    std::vector<Brick> bricks;

    for (int iX{0}; iX < 11; ++iX)
        for (int iY{0}; iY < 5; ++iY)
            bricks.emplace_back((iX + 1) * 70, (iY + 2) * 20);

    while (true) {
        window.clear(sf::Color::Black);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) break;

        ball.update();
        paddle.update();
        testCollision(paddle, ball);

        for (auto &brick : bricks) testCollision(brick, ball);
        bricks.erase(std::remove_if(std::begin(bricks), std::end(bricks), [](const Brick &mBrick) { return mBrick.destroyed; }), std::end(bricks));

        window.draw(paddle.shape);
        window.draw(ball.shape);
        for (auto &brick : bricks) window.draw(brick.shape);

        window.display();
    }

    return 0;
}

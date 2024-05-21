import pygame
import random

# Initialize Pygame
pygame.init()

# Set up display
width, height = 800, 600
window = pygame.display.set_mode((width, height))
pygame.display.set_caption('Breakout')

# Set up colors
black = (0, 0, 0)
white = (255, 255, 255)
colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0), (255, 165, 0)]

# Paddle
paddle = pygame.Rect(width // 2 - 60, height - 30, 120, 20)
paddle_speed = 10

# Ball
ball = pygame.Rect(width // 2 - 15, height // 2 - 15, 30, 30)
ball_speed = [random.choice((5, -5)), random.choice((5, -5))]

# Bricks
brick_rows = 5
brick_cols = 11
brick_width = 70
brick_height = 20
bricks = [pygame.Rect(col * brick_width + 10, row * brick_height + 40, brick_width - 2, brick_height - 2) for row in range(brick_rows) for col in range(brick_cols)]

# Main game loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] and paddle.left > 0:
        paddle.left -= paddle_speed
    if keys[pygame.K_RIGHT] and paddle.right < width:
        paddle.right += paddle_speed

    ball.left += ball_speed[0]
    ball.top += ball_speed[1]

    if ball.left <= 0 or ball.right >= width:
        ball_speed[0] = -ball_speed[0]
    if ball.top <= 0 or ball.colliderect(paddle):
        ball_speed[1] = -ball_speed[1]

    for brick in bricks[:]:
        if ball.colliderect(brick):
            bricks.remove(brick)
            ball_speed[1] = -ball_speed[1]

    if ball.top >= height:
        running = False

    window.fill(black)
    pygame.draw.rect(window, white, paddle)
    pygame.draw.ellipse(window, white, ball)

    for brick in bricks:
        pygame.draw.rect(window, colors[bricks.index(brick) % len(colors)], brick)

    pygame.display.flip()
    pygame.time.delay(30)

pygame.quit()

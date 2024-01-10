import pygame
import random

WIDTH, HEIGHT = 450, 450


pygame.init()


screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Brownian Motion')  
clock = pygame.time.Clock()

class Particle:
    def __init__(self, x, y, size):
        self.x = x
        self.y = y
        self.size = size
        self.dx = random.uniform(-4, 4)
        self.dy = random.uniform(-4, 4)

    def move(self):
        self.x += self.dx
        self.y += self.dy

        if self.x <= 0 or self.x >= WIDTH:
            self.dx = -self.dx
        if self.y <= 0 or self.y >= HEIGHT:
            self.dy = -self.dy

    def draw(self, screen):
        pygame.draw.circle(screen, (0, 0, 255), (int(self.x), int(self.y)), 12)

particle = Particle(WIDTH // 2, HEIGHT // 2, 5)

run = True

while run:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False

    screen.fill((255, 255, 255))
    particle.move()
    particle.draw(screen)
    pygame.display.flip()
    clock.tick(60)

pygame.quit()

from __future__ import annotations
import random
import matplotlib.pyplot as plt
import numpy as np
import pygame
from scipy import constants
from scipy import integrate

EARTH_MASS: float = 5.972e24
MOON_MASS: float = 7.34767309e22
PLANETARY_DISTANCE: float = 384400000.

WIN_WIDTH: int = 640
WIN_HEIGHT: int = 640

COLOR_WHITE = (255, 255, 255)
COLOR_BLACK = (0, 0, 0)


class HeavenlyBody(pygame.sprite.Sprite):
    def __init__(self, name: str, mass: float, color: tuple[int, int, int] = COLOR_WHITE, radius: float = 0, img_file: str = None) -> None:
        pygame.sprite.Sprite.__init__(self, )

        self.name = name
        self.mass = mass
        self.radius: float = radius
        self.position: np.ndarray = np.zeros((2,), dtype=np.float64)
        self.velocity: np.ndarray = np.zeros((2,), dtype=np.float64)
        self.integrator: integrate.ode = integrate.ode(self.integrate)
        self.position_history: np.ndarray = np.array(())
        self.image: pygame.surface.Surface
        self.rect: pygame.rect.Rect

        self.integrator.set_integrator('dop853')
        self.integrator.set_initial_value(np.concatenate(
            [self.position, self.velocity], axis=None))

        if img_file:
            self.image = pygame.image.load(img_file)
        else:
            self.image = pygame.Surface([radius * 2, radius * 2])
            self.image.fill(COLOR_BLACK)
            pygame.draw.circle(self.image, color,
                               (radius, radius), radius, radius)

        self.rect = self.image.get_rect()

    def set_position(self, new_position: np.ndarray) -> None:
        self.position = new_position.astype(np.float64)
        self.integrator.y[:2] = new_position.astype(np.float64)

    def set_velocity(self, new_velocity: np.ndarray) -> None:
        self.velocity = new_velocity.astype(np.float64)
        self.integrator.y[2:] = new_velocity.astype(np.float64)

    def integrate(self, d_time: float, y: np.ndarray, force: np.ndarray) -> np.ndarray:
        # print(d_time, y)
        self.velocity += d_time * force / self.mass
        self.position += d_time * self.velocity
        return np.concatenate([
            self.position,
            self.velocity
        ], axis=None)

    def update_motion(self, d_time: float, objects: dict[str, HeavenlyBody]) -> None:
        force: np.ndarray = self.calculate_force(d_time, objects)
        self.integrator.set_f_params(force)
        self.integrator.integrate(d_time)
        print(f'Stuff: {self.integrator.integrate(d_time)} | Pos: {self.integrator.y[:2]} | Vel: {self.integrator.y[2:]}')
        
        # self.position = self.integrator.y[:2]
        # self.velocity = self.integrator.y[2:]

    def calculate_force(self, d_time: float, objects: dict[str, HeavenlyBody]) -> np.ndarray:
        force: np.ndarray = np.zeros((2,))
        obj_name: str
        obj: HeavenlyBody
        displacement: np.ndarray
        normal: np.ndarray

        for obj_name in objects:
            if obj_name == self.name:
                continue

            obj = objects[obj_name]

            displacement = obj.position - self.position
            normal = np.linalg.norm(displacement)
            force += (displacement / normal) * constants.G * \
                self.mass * obj.mass / (normal ** 2)

            self.position_history = np.append(self.position_history, normal)

        return force


class Universe:
    def __init__(self) -> None:
        self.width: float = 2.6 * PLANETARY_DISTANCE
        self.height: float = 2.6 * PLANETARY_DISTANCE
        self.d_time: float = 10.0
        self.objects: dict[str, HeavenlyBody] = {}
        self.object_group: pygame.sprite.Group = pygame.sprite.Group()

    def add_body(self, body: HeavenlyBody) -> None:
        self.objects[body.name] = body
        self.object_group.add(body)

    def display(self, position: np.ndarray) -> np.ndarray:
        return np.array([
            int((position[0] + 1.3 * PLANETARY_DISTANCE)
                * WIN_WIDTH // self.width),
            int((position[1] + 1.3 * PLANETARY_DISTANCE)
                * WIN_HEIGHT // self.height),
        ])

    def update(self) -> None:
        obj_name: str
        obj: HeavenlyBody
        position: np.ndarray

        for obj_name in self.objects:
            obj = self.objects[obj_name]
            obj.update_motion(self.d_time, self.objects)

            position = self.display(obj.position)
            obj.rect.x, obj.rect.y = position[0] - \
                obj.radius, position[1] - obj.radius

        self.object_group.update()

    def draw(self, screen: pygame.surface.Surface) -> None:
        self.object_group.draw(screen)


def main() -> None:
    earth: HeavenlyBody = HeavenlyBody(
        'earth', EARTH_MASS, radius=32, img_file='earth-northpole.jpg')
    moon: HeavenlyBody = HeavenlyBody('moon', MOON_MASS, COLOR_WHITE, 10)
    universe: Universe = Universe()
    current_frame: int = 0
    total_fps = 1000000
    iterations_per_frame: int = 50
    screen: pygame.surface.Surface
    event: pygame.event.Event

    random.seed(0)
    pygame.init()

    earth.set_position(np.zeros((2,)))
    moon.set_position(np.array([int(PLANETARY_DISTANCE), 0]))
    moon.set_velocity(np.array([0, random.choice([100, 1000])]))

    universe.add_body(earth)
    universe.add_body(moon)

    screen = pygame.display.set_mode((WIN_WIDTH, WIN_HEIGHT))
    pygame.display.set_caption('Heavenly Bodies')

    while pygame.get_init() and current_frame < total_fps:
        universe.update()
        if current_frame % iterations_per_frame == 0:
            screen.fill(COLOR_BLACK)
            universe.draw(screen)
            pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_q):
                pygame.quit()

        current_frame += 1

    plt.figure(1)
    plt.plot(earth.position_history)
    plt.xlabel('Frame')
    plt.ylabel('Distance')
    plt.title('Distance Between Earth and Moon')
    plt.show()


if __name__ == '__main__':
    main()
